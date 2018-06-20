
template<typename T>
int convert_to_binary(T *input, int input_size, uint64_t *output, int output_size, int stride){
	// input_size is in bits (of output--input representation is irrelevant), output_size is in 64 bit chunks
	// must have input_size == output_size * 64
	// Checks that sizes match.  Returns 0 for success, 1 for failure due to size mismatch.
	uint64_t tmp;
	int idx;
	if(input_size != 64 * output_size){
		return 1;
	}
	for(int i=0;i<input_size;i+=64){
		tmp = 0;
		for(int j=0;j<64;j++){
			idx = i + j;
			if(idx>=64 * output_size){
				break;
			}
			if(input[stride * idx] > 0){
				tmp |= (1 << j);
			}
//			tmp[j] |= input[stride * idx] > 0?1:0;
		}
		output[i/64] = tmp;
	}
	return 0;
}

template<typename T>
int convert_from_binary(uint64_t *input, int input_size, T *output, int output_size, int stride){
	uint64_t tmp;
	int idx;
	if(output_size != 64 * input_size){
		return 1;
	}
	for(int i=0;i<input_size;i++){
		tmp = input[i];
		for(int j=0;j<64;j++){
			output[stride * (64*i + j)] = (tmp & (1<<j))?1:-1;
		}
	}
	return 0;
}

int binary_sum(uint64_t *x, int size){
	int total_bits = 0;
	for(int i=0;i<size;i++){
		total_bits += __builtin_popcountll(x[i]);
	}
	return total_bits - (64*size - total_bits);
}

int binary_tanh_dot(uint64_t *x, uint64_t *y, int size){
	int sum = 0;
	int antisum = 0;
	int subsum;
	uint64_t tmp;
	int thresh = 32 * size;
	for(int i=0;i<size;i++){
		tmp = ~(x[i] ^ y[i]);
		subsum = __builtin_popcountll(tmp);
		sum += subsum;
		antisum += (64 - subsum);

		// One of the following must happen by the final iteration
		if(antisum>=thresh){
			return 0;
		}
		if(sum>thresh){
			return 1;
		}
	}
}

class XNorLayer{
	public:
		int rows;
		int cols;
		XNorLayer(int input_size, int output_size){
			this->rows = input_size / 64;
			this->cols = output_size;
			weights = new uint64_t*[cols];
			for(int i=0;i<output_size;i++){
				weights[i] = new uint64_t[rows];
			}
		}
		~XNorLayer(){
			for(int i=0;i<cols;i++){
				delete weights[i];
			}
			delete weights;
		}
		template<typename T>
		void set_weights(T *float_weights){
			// Assume rows and cols divisible by 64
			// Assume row-major ordering of float_weights
			for(int i=0;i<cols;i++){
				convert_to_binary(&(float_weights[i]), 64*rows, weights[i], rows, cols);
			}
		}

		void apply(uint64_t *input, uint64_t *output){
			uint64_t outtmp;
			int colsum;
			int anticolsum;
			int thresh = 64 * rows;
			for(int i=0;i<cols;i+=64){
				outtmp = 0;
				for(int k=0;k<64;k++){
					// col i+k
					if(binary_tanh_dot(weights[i+k], input, rows)){
						outtmp |= (1<<k);
					}
				}
				output[i / 64] = outtmp;
			}
		}
	private:
		uint64_t ** weights;
};

class XNorEvaluator{
	public:
		int num_layers;
		int input_size;
		int final_size;
		int max_size;
		XNorEvaluator(int *layer_sizes, int num_layers, int input_size){
			// All layer sizes and input_size must be divisible by 64
			this->input_size = input_size;
			this->num_layers = num_layers;
			int current_size = input_size;
			max_size = current_size;
			layers = new XNorLayer*[num_layers];
			for(int i=0;i<num_layers;i++){
				layers[i] = new XNorLayer(current_size, layer_sizes[i]);
				current_size = layer_sizes[i];
				if(current_size > max_size){
					max_size = current_size;
				}
			}
			final_size = current_size;
			tmp1 = new uint64_t[max_size / 64];
			tmp2 = new uint64_t[max_size / 64];
		}

		~XNorEvaluator(){
			delete tmp1;
			delete tmp2;
			for(int i=0;i<num_layers;i++){
				delete layers[i];
			}
			delete layers;
		}

		template<typename T>
		void set_weights(int layer, T *weights){
			layers[layer]->set_weights<T>(weights);
		}

		int apply(uint64_t *input){
			XNorLayer *layer;
			uint64_t *layer_in;
			uint64_t *layer_out;
			for(int i=0;i<num_layers;i++){
				if(i==0){
					layer_in = input;
					layer_out = tmp1;
				}else if(i%2){
					layer_in = tmp1;
					layer_out = tmp2;
				}else{
					layer_in = tmp2;
					layer_out = tmp1;
				}
				layer = layers[i];
				layer->apply(layer_in, layer_out);
			}
			return binary_sum(layer_out, (layer->cols) / 64);

		}
	private:
		XNorLayer **layers;
		uint64_t *tmp1;
		uint64_t *tmp2;
};
