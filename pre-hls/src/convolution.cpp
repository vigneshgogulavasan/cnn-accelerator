#include "convolution.h"
#include <iostream>

Convolution::Convolution(const float *kernel,
                         const float* bias,
	int kernel_size,
	int number_of_kernels,
	int input_size,
	int stride,
	int input_depth,
	int zero_padding)
:	kernel(kernel),
        bias(bias),
	kernel_size(kernel_size),
	number_of_kernels(number_of_kernels),
	input_size(input_size),
	stride(stride),
	input_depth(input_depth),
	zero_padding(zero_padding)
{
   	output_size = ((input_size - kernel_size + 2 * zero_padding) / stride) + 1;
        std::cout << "output_size: " << output_size << "\n";

}

Convolution::~Convolution()
{
}

void Convolution::conv_layer(float input[], float output[]) {

///// Zero padding /////

/***** VERY QUESTIONABLE DECLARATION *****/
	float pad_input[(input_size+2*zero_padding)*(input_size+2*zero_padding)*input_depth];
///////////////////////////////////////////

	for ( int d = 0; d < input_depth; d++) { // depth
		for ( int r = 0; r < input_size+2*zero_padding; r++) { // row
			for ( int c = 0; c < input_size+2*zero_padding; c++) { // column
				if (r < zero_padding || r >= input_size+zero_padding) pad_input[d*(input_size+2*zero_padding)*(input_size+2*zero_padding) + r*(input_size+2*zero_padding) + c] = 0;
				else if (c < zero_padding || c >= input_size+zero_padding) pad_input[d*(input_size+2*zero_padding)*(input_size+2*zero_padding) + r*(input_size+2*zero_padding) + c] = 0;
				else pad_input[d*(input_size+2*zero_padding)*(input_size+2*zero_padding) + r*(input_size+2*zero_padding) + c] = input[d*input_size*input_size + (r-zero_padding)*input_size + (c-zero_padding)];
			}
		}
	}
        /*
	// FOR DEBUG PURPOSE //
	std::cout << "zero pad input" << '\n';
	for ( int d = 0; d < input_depth; d++) { // depth
		for ( int r = 0; r < input_size+2*zero_padding; r++) { // row
			for ( int c = 0; c < input_size+2*zero_padding; c++) { // column
				std::cout << pad_input[d*(input_size+2*zero_padding)*(input_size+2*zero_padding) + r*(input_size+2*zero_padding) + c] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
        */
	///////////////////////
///// end of zero padding /////

/* ------------------------------- */

///// Convolution calculation /////

	// output[ouput_size][output_size][number_of_kernels]

	int o_r = 0; // output row index
	int o_c = 0; // output column index
	int o_d = 0; // output depth index

	for (int i = 0; i < number_of_kernels; i++) { // kernel canals
		for (int j = 0; j <= input_size+2*zero_padding-kernel_size; j+=stride) { // vertical slide of convolution second
			for (int k = 0; k <= input_size+2*zero_padding-kernel_size; k+=stride) { // horizontal slide of convolution first
				output[o_d*output_size*output_size + o_r*output_size + o_c] = 0;
				/////// begin conv op ////////
				for (int l = 0; l < input_depth; l++){ // operation with kernel depth last
					for (int m = 0; m < kernel_size; m++) { // operation with kernel height second
						for (int n = 0; n < kernel_size; n++) { // operation with kernel width first
							output[o_d*output_size*output_size + o_r*output_size + o_c] += pad_input[l*(input_size+2*zero_padding)*(input_size+2*zero_padding) + (j+m)*(input_size+2*zero_padding) + (k+n)]*kernel[l*kernel_size*kernel_size + m*kernel_size + n];
						}
				 	}
				} 
				output[o_d*output_size*output_size + o_r*output_size + o_c] += bias[i]; // adding bias
				// RELU
				if (output[o_d*output_size*output_size + o_r*output_size + o_c] < 0) output[o_d*output_size*output_size + o_r*output_size + o_c] = 0;
				////// end of conv op ///////
				o_c+=1;
			}
			o_c = 0;
			o_r+=1;
		}
		o_c = 0;
		o_r = 0;
		o_d+=1;
	}

///// end of calculation /////

}