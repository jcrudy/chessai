
template<typename T>
int convert_to_binary(T *input, int input_size, uint64_t *output, int output_size, int stride){
	// input_size is in bits (of output--input representation is irrelevant), output_size is in 64 bit chunks
	// must have input_size == output_size * 64
	// Checks that sizes match.  Returns 0 for success, 1 for failure due to size mismatch.
	std::bitset<64> tmp;
	int idx;
	if(input_size != 64 * output_size){
		return 1;
	}
	for(int i=0;i<input_size;i+=64){
		tmp = std::bitset<64>();
		for(int j=0;j<64;j++){
			idx = i + j;
			if(idx>=64 * output_size){
				break;
			}
			tmp[j] = input[stride * idx] > 0?1:0;
		}
		output[i/64] = tmp.to_ullong();
	}
	return 0;
}

template<typename T>
int convert_from_binary(uint64_t *input, int input_size, T *output, int output_size, int stride){
	std::bitset<64> tmp;
	int idx;
	if(output_size != 64 * input_size){
		return 1;
	}
	for(int i=0;i<input_size;i++){
		tmp = std::bitset<64>(input[i]);
		for(int j=0;j<64;j++){
			output[stride * (64*i + j)] = tmp[j]?1:-1;
		}
	}
	return 0;
}

int binary_sum(uint64_t *x, int size){
	int total_bits = 0;
	for(int i=0;i<size;i++){
		printf("%s", std::bitset<64>(x[i]).to_string().c_str());
		printf(" %d ", __builtin_popcountll(x[i]));
		total_bits += __builtin_popcountll(x[i]);
	}
	printf("\n");
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
			std::bitset<64> tmp;
			printf("set_weights\n");
			printf("rows = %d, cols=%d\n", rows, cols);
			for(int i=0;i<cols;i++){
				convert_to_binary(&(float_weights[i]), 64*rows, weights[i], rows, cols);
			}
//
//
//			for(int i=0;i<cols;i++){
//				for(int j=0;j<64*rows;j+=64){
//					tmp = std::bitset<64>();
//					for(int k=0;k<64;k++){
//						// column i, row j+k
//						tmp[k] = (float_weights[i + (j + k) * cols] > 0)?1:0;
//					}
//					// Set column i, rows j:(j+64)
//					weights[i][j / 64] = tmp.to_ullong();
//				}
//			}
//			printf("completed set_weights\n");
		}

		template<typename T>
		void get_weights(T *float_weights){

		}

		void apply(uint64_t *input, uint64_t *output){
			uint64_t tmp;
			std::bitset<64> outtmp;
			int colsum;
			int anticolsum;
			int thresh = 64 * rows;
			for(int i=0;i<cols;i+=64){
				for(int k=0;k<64;k++){
					// col i+k
					outtmp[k] = binary_tanh_dot(weights[i+k], input, rows);
					printf("%d", outtmp[k]?1:0);
				}
				printf(" %d ", __builtin_popcountll(outtmp.to_ullong()));
				printf("Setting output[%d]\n", i/64);
				output[i / 64] = outtmp.to_ullong();
			}
			printf("\n");


//				for(int j=0;j<64;j++){
//					colsum = 0;
//					anticolsum = 0;
//					for(int row=0;row<rows;row++){
//						tmp = ~(weights[i][row] ^ input[i]);
//						colsum += __builtin_popcountll(tmp);
//						anticolsum += (64 - colsum);
//						// One of the following will happen by the last iteration,
//						// but may happen as soon as halfway through, allowing an early stop.
//						if(anticolsum >= thresh){
//							outtmp[j] = 0;
//							break;
//						}else if(colsum > thresh){
//							outtmp[j] = 1;
//							break;
//						}
//					}
//				}
//				output[i / 64] = outtmp.to_ullong();
//			}
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


//			layer = layers[0];
//			layer->apply(input, tmp1);
//			printf("num_layers = %d\n", num_layers);
//			for(int i=1;i<num_layers;i++){
//				layer = layers[i];
//				printf("Call apply\n");
//				layer->apply(tmp1, tmp2);
//				if(i<num_layers){
//					for(int k=0;k<(layer->cols)/64;k++){
//						tmp1[k] = tmp2[k];
//					}
//				}
//			}
//
//			int total = 0;
//			if(num_layers%2){
//				for(int k=0;k<final_size/64;k++){
//
//				}
//			}else{
//
//			}
//
//			for(int i=0;i<final_size/64;i++){
//				printf("popcount = %d\n", __builtin_popcountll(tmp2[i]));
//				total += __builtin_popcountll(tmp2[i]);
//			}
//			printf("total = %d\n", total);
//			printf("final_size = %d\n", final_size);
//			return 2*total - final_size;
		}
	private:
		XNorLayer **layers;
		uint64_t *tmp1;
		uint64_t *tmp2;
};
