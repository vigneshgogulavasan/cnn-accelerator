/* convolution.cpp
 * Convolution and ReLU layer implementation.
 */

#include "math.h"
#include "convolution.h"
#include "kernel.h"

#pragma hls_design top
void apply_conv(in_t conv_in[DATA_SIZE],
                out_t conv_out[DATA_SIZE_OUT]) {

    in_t *input = conv_in;
    out_t *output = conv_out;
    temp_t temp = 0;
    int o_r = 0; // output row index
    int o_c = 0; // output column index
    int o_d = 0; // output depth index

    in_t pad_input[(INPUT_SIZE_X+2*ZERO_PADDING)*(INPUT_SIZE_Y+2*ZERO_PADDING)*INPUT_DEPTH];

PAD:for (int d = 0; d < INPUT_DEPTH; d++) { // depth
        for (int r = 0; r < INPUT_SIZE_Y+2*ZERO_PADDING; r++) { // row
            for (int c = 0; c < INPUT_SIZE_X+2*ZERO_PADDING; c++) { // column
	      if (r < ZERO_PADDING || r >= INPUT_SIZE_Y+ZERO_PADDING) {
		pad_input[d*(INPUT_SIZE_X+2*ZERO_PADDING)*(INPUT_SIZE_Y+2*ZERO_PADDING) + r*(INPUT_SIZE_X+2*ZERO_PADDING) + c] = 0;
	      }
	      else if (c < ZERO_PADDING || c >= INPUT_SIZE_X+ZERO_PADDING) {
		pad_input[d*(INPUT_SIZE_X+2*ZERO_PADDING)*(INPUT_SIZE_Y+2*ZERO_PADDING) + r*(INPUT_SIZE_X+2*ZERO_PADDING) + c] = 0;
	      }
	      else {
		pad_input[d*(INPUT_SIZE_X+2*ZERO_PADDING)*(INPUT_SIZE_Y+2*ZERO_PADDING) + r*(INPUT_SIZE_X+2*ZERO_PADDING) + c] = input[d*INPUT_SIZE_X*INPUT_SIZE_Y + (r-ZERO_PADDING)*INPUT_SIZE_X + (c-ZERO_PADDING)];
	      }
            }
        }
    }

CONV_NB_K:for (int i = 0; i < NB_KERNELS; i++) { // kernel canals
        CONV_V_SLIDE:for (int j = 0; j <= INPUT_SIZE_Y+2*ZERO_PADDING-KERNEL_SIZE; j+=STRIDE) { // vertical slide of convolution second
            CONV_H_SLIDE:for (int k = 0; k <= INPUT_SIZE_X+2*ZERO_PADDING-KERNEL_SIZE; k+=STRIDE) { // horizontal slide of convolution first
	        temp = 0;
                CONV_K_D:for (int l = 0; l < INPUT_DEPTH; l++){ // operation with kernel depth last
                    CONV_K_H:for (int m = 0; m < KERNEL_SIZE; m++) { // operation with kernel height second
                        CONV_K_W:for (int n = 0; n < KERNEL_SIZE; n++) { // operation with kernel width first
		            temp = temp + pad_input[l*(INPUT_SIZE_X+2*ZERO_PADDING)*(INPUT_SIZE_Y+2*ZERO_PADDING) + (j+m)*(INPUT_SIZE_X+2*ZERO_PADDING) + (k+n)]*kernel[i*KERNEL_SIZE*KERNEL_SIZE*INPUT_DEPTH + l*KERNEL_SIZE*KERNEL_SIZE + m*KERNEL_SIZE + n];
                        }
                    }
                }
                temp = temp + bias[i];
                if (temp < 0) {
                    temp = 0;
                } else if (temp > 255) {
                    temp = 255;
                }
                output[o_d + 4*o_r*OUTPUT_SIZE_X + 4*o_c] = temp;
                o_c+=1;
            }
            o_c = 0;
            o_r+=1;
        }
        o_c = 0;
        o_r = 0;
        o_d+=1;
    }
}
