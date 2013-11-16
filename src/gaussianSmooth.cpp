/* 
 * File:   gaussianSmooth.cpp
 * Author: mavewei
 *
 * Created on October 31, 2013, 5:28 PM
 */

 #include "main.h"

 void gaussianSmooth(unsigned char *readImage, short int **gsmoothImage, float sigma) {
    int center, windowsSize;
    float x, dot, fx, sum = 0.0;
    float *kernel, *tmpBuf;
    
    tmpBuf = (float *) calloc(HEIGHT * WIDTH, sizeof (float));    
    (*gsmoothImage) = (short int *) calloc(HEIGHT*WIDTH, sizeof (short int));
    
    if (VERBOSE) printf("   Computing the gaussian smoothing kernel.\n");
    windowsSize = 1 + 2 * ceil(2.5 * sigma);
    center = windowsSize / 2;

    if (VERBOSE) printf("      The kernel has %d elements.\n", windowsSize);
    kernel = (float *) calloc((windowsSize), sizeof (float));    
    for (int i = 0; i < windowsSize; i++) {
        x = (float) (i - center);
        fx = pow(2.71828, -0.5 * x * x / (sigma * sigma)) / (sigma * sqrt(6.2831853));
        kernel[i] = fx;
        sum += fx;
    }
    for (int i = 0; i < windowsSize; i++) {
        kernel[i] /= sum;
    }
    
    if (VERBOSE) {
        for (int i = 0; i < windowsSize; i++) {
            printf("Gaussian filter coefficients are: kernel[%d]: %f\n", i, kernel[i]);
        }
    }

    if (VERBOSE) printf("   Bluring the image in the X-direction.\n");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            dot = 0.0;
            sum = 0.0;
            for (int jj = (-center); jj <= center; jj++) {
                if (((j + jj) >= 0) && ((j + jj) < WIDTH)) {
                    dot += (float) readImage[i * WIDTH + (j + jj)] * kernel[center + jj];
                    sum += kernel[center + jj];
                }
            }
            tmpBuf[i * WIDTH + j] = dot / sum;
        }
    }

    if (VERBOSE) printf("   Bluring the image in the Y-direction.\n");
    for (int j = 0; j < WIDTH; j++) {
        for (int i = 0; i < HEIGHT; i++) {
            sum = 0.0;
            dot = 0.0;
            for (int ii = (-center); ii <= center; ii++) {
                if (((i + ii) >= 0) && ((i + ii) < HEIGHT)) {
                    dot += tmpBuf[(i + ii) * WIDTH + j] * kernel[center + ii];
                    sum += kernel[center + ii];
                }
            }
            (*gsmoothImage)[i * WIDTH + j] = (short int) (dot * BLURFACTOR / sum + 0.5);
        }
    }

    free(tmpBuf);
    free(kernel);
}