//#include "mc_scverify.h"
#include "convolution.h"

int main() {
    ac_fixed<IMAGE_W, IMAGE_I, true> images[160*120*3];
    ac_fixed<OUT_W, OUT_I, true> conv_out[160*120*3];
    
    //load_file("../db/100-normalized-images-fixW8I2.out", images);
    //load_file("../db/100-labels.out", labels);

    //Convolution conv_relu(kernels, biases, 64, 24, 3, 24);

    //conv_relu.apply(image, conv_out);
   
    return 0;
}
