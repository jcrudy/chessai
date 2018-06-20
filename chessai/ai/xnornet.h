#ifndef XNORNET_H
#define XNORNET_H

#include <boost/dynamic_bitset.hpp>

typedef boost::dynamic_bitset<> bitset_type;

template<typename T>
int convert_to_binary(T *input, int input_size, bitset_type &output, int stride){
	// input_size is in bits (of output--input representation is irrelevant), output_size is in 64 bit chunks
	// must have input_size == output_size * 64
	// Checks that sizes match.  Returns 0 for success, 1 for failure due to size mismatch.
	if(output.size() < input_size){
		return 1;
	}
	for (bitset_type::size_type i=0;i<input_size;i++){
		output[i] = input[stride * i] > 0?1:0;
	}
	return 0;
//
//	int idx;
//	if(input_size != 64 * output_size){
//		return 1;
//	}
//	for(int i=0;i<input_size;i+=64){
//		tmp = 0;
//		for(int j=0;j<64;j++){
//			idx = i + j;
//			if(idx>=64 * output_size){
//				break;
//			}
//			if(input[stride * idx] > 0){
//				tmp |= (one << j);
//			}
////			tmp[j] |= input[stride * idx] > 0?1:0;
//		}
//		output[i/64] = tmp;
//	}
//	return 0;
}

template<typename T>
int convert_from_binary(bitset_type &input, T *output, int output_size, int stride){
	if(input.size() > output_size){
		return 1;
	}
	for(bitset_type::size_type i=0;i<input.size();i++){
		output[stride * i] = input[i]?1:-1;
	}
	return 0;

//	uint64_t tmp;
//	const uint64_t one = 1;
//	int idx;
//	if(output_size != 64 * input_size){
//		return 1;
//	}
//	for(int i=0;i<input_size;i++){
//		tmp = input[i];
//		for(int j=0;j<64;j++){
//			output[stride * (64*i + j)] = (tmp & (one<<j))?1:-1;
//		}
//	}
//	return 0;
}

int binary_sum(bitset_type x){
	int size = (int) x.size();
	int total_bits = (int) x.count();
	return total_bits - (size - total_bits);
//	int total_bits = 0;
//	for(int i=0;i<size;i++){
//		total_bits += __builtin_popcountll(x[i]);
//	}
//	return total_bits - (64*size - total_bits);
}

int binary_tanh_dot(bitset_type &x, bitset_type &y, bitset_type &tmp){
	bitset_type::size_type size = x.size();
	int thresh = size / 2;
	tmp = x;
	tmp ^= y;
	bitset_type::size_type count = tmp.count();
	if(count >= (size - count)){
		return 0;
	}else{
		return 1;
	}
//	if(tmp.count() <= thresh){
//		return 0;
//	}else{
//		return 1;
//	}

//	int sum = 0;
//	int antisum = 0;
//	int subsum;
//	uint64_t tmp;
//	int thresh = 32 * size;
//	for(int i=0;i<size;i++){
//		tmp = ~(x[i] ^ y[i]);
//		subsum = __builtin_popcountll(tmp);
//		sum += subsum;
//		antisum += (64 - subsum);
//
//		// One of the following must happen by the final iteration
//		if(antisum>=thresh){
//			return 0;
//		}
//		if(sum>thresh){
//			return 1;
//		}
//	}
}

int binary_tanh_dot(bitset_type &x, bitset_type &y){
	bitset_type tmp = bitset_type(x.size());
	return binary_tanh_dot(x, y, tmp);
}

class XNorLayer{
	public:
		int input_size;
		int output_size;
		bitset_type * output;
		XNorLayer(int input_size, int output_size){
			this->input_size = input_size;
			this->output_size = output_size;
			weights = new bitset_type*[output_size];
			for(int i=0;i<output_size;i++){
				weights[i] = new bitset_type(input_size);
			}
			tmp = new bitset_type(input_size);
			output = new bitset_type(output_size);
		}
		~XNorLayer(){
			for(int i=0;i<output_size;i++){
				delete weights[i];
			}
			delete weights;
			delete tmp;
			delete output;
		}
		template<typename T>
		void set_weights(T *t_weights){
			// Assume row-major ordering of float_weights
			for(int i=0;i<output_size;i++){
				convert_to_binary<T>(&(t_weights[i]), input_size, *weights[i], output_size);
			}
		}
		void apply(bitset_type &input, bitset_type &output){
			for(int i=0;i<output_size;i++){
				output[i] = binary_tanh_dot(input, *weights[i], *tmp);
			}
		}
		void apply(bitset_type &input){
			this->apply(input, *output);
		}
	private:
		bitset_type *tmp;
		bitset_type **weights;
};

//class XNorLayer{
//	public:
//		int rows;
//		int cols;
//		XNorLayer(int input_size, int output_size){
//			this->rows = input_size / 64;
//			this->cols = output_size;
//			weights = new uint64_t*[cols];
//			for(int i=0;i<output_size;i++){
//				weights[i] = new uint64_t[rows];
//			}
//		}
//		~XNorLayer(){
//			for(int i=0;i<cols;i++){
//				delete weights[i];
//			}
//			delete weights;
//		}
//		template<typename T>
//		void set_weights(T *float_weights){
//			// Assume rows and cols divisible by 64
//			// Assume row-major ordering of float_weights
//			for(int i=0;i<cols;i++){
//				convert_to_binary<T>(&(float_weights[i]), 64*rows, weights[i], rows, cols);
//			}
//		}
//
//		void apply(uint64_t *input, uint64_t *output){
//			uint64_t outtmp;
//			const uint64_t one = 1;
//			int colsum;
//			int anticolsum;
//			int thresh = 64 * rows;
//			for(int i=0;i<cols;i+=64){
//				outtmp = 0;
//				for(int k=0;k<64;k++){
//					// col i+k
//					if(binary_tanh_dot(weights[i+k], input, rows)){
//						outtmp |= (one<<k);
//					}
//				}
//				output[i / 64] = outtmp;
//			}
//		}
//	private:
//		uint64_t ** weights;
//};


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
			tmp1 = new bitset_type(max_size);
			tmp2 = new bitset_type(max_size);
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

		int apply(bitset_type &input){
			XNorLayer *layer;
			bitset_type *layer_in;
			bitset_type *layer_out;
			for(int i=0;i<num_layers;i++){
				layer = layers[i];
				if(i==0){
					layer_in = &input;
					layer_out = layer->output;
				}else{
					layer_in = layer_out;
					layer_out = layer->output;
				}
				layer->apply(*layer_in, *layer_out);
			}
			return binary_sum(*layer_out);

		}
	private:
		XNorLayer **layers;
		bitset_type *tmp1;
		bitset_type *tmp2;
};

#endif
