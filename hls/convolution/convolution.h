#ifndef _CONVOLUTION_H_
#define _CONVOLUTION_H_

#include "ac_fixed.h"
#include "ac_int.h"

#define NB_KERNELS 3
#define INPUT_SIZE_X 160
#define INPUT_SIZE_Y 120
#define INPUT_DEPTH 3
#define OUTPUT_SIZE_X 160
#define OUTPUT_SIZE_Y 120 
#define KERNEL_SIZE 3
#define STRIDE 1
#define ZERO_PADDING 1

#define IMAGE_W 8
#define IMAGE_I 8
#define IN_W 8
#define IN_I 2
#define OUT_W 9
#define OUT_I 3
#define KERNEL_W 9
#define KERNEL_I 3
#define INT_W 8

class Convolution {
private:
    const ac_fixed<KERNEL_W, KERNEL_I, true> *kernel;
    const ac_fixed<KERNEL_W, KERNEL_I, true> *bias;
    //const ac_int<INT_W,false> number_of_kernels;
    //const ac_int<INT_W,false> input_size;
    //const ac_int<INT_W,false> input_depth;
    //const ac_int<INT_W,false> output_size; 
    //output_size = ((input_size - KERNEL_SIZE + 2 * ZERO_PADDING) / STRIDE) + 1;

public:
	Convolution(const ac_fixed<KERNEL_W, KERNEL_I, true> *kernel,
                    const ac_fixed<KERNEL_W, KERNEL_I, true> *bias
                    //const ac_int<INT_W,false> number_of_kernels,
                    //const ac_int<INT_W,false> input_size,
                    //const ac_int<INT_W,false> input_depth,
		    //const ac_int<INT_W,false> output_size
		    );
	~Convolution();

        void apply(ac_fixed<IN_W, IN_I, false> input[], ac_fixed<OUT_W, OUT_I, false> output[]);

};

#endif /* _CONVOLUTION_H_ */
