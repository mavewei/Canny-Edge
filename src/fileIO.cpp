/* 
 * File:   fileIO.cpp
 * Author: mavewei
 *
 * Created on October 31, 2013, 5:28 PM
 */

 #include "main.h"

 int readImage(char *inputFile, unsigned char **readimage, int height, int width) {
    FILE *fp;
    if ((fp = fopen(inputFile, "rb")) == NULL) {
        fprintf(stderr, "***Error: Reading image file [%s] terminated unexpected!\n", inputFile);
        return -1;
    }
    (*readimage) = (unsigned char *) malloc(height * width);
    fread((*readimage), HEIGHT, WIDTH, fp);
    fclose(fp);
    return 0;
}

int writeImagePGM(char *filename, int height, int width, unsigned char *image) {
    FILE *fp;
    if((fp = fopen(filename, "wb")) == NULL) {
        fprintf(stderr, "***Error: Writing image file [%s] terminated unexpected!\n", filename);
        return -1;
    }
    fprintf(fp, "P5\n\n%d %d 255\n", height, width);
    fwrite(image, sizeof(unsigned char), height * width, fp);
    fclose(fp);
    return 0;
}