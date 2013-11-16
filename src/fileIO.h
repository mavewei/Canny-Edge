/* 
 * File:   fileIO.h
 * Author: mavewei
 *
 * Created on October 31, 2013, 5:28 PM
 */

 #ifndef __FILEIO_H__
 #define __FILEIO_H__

 int readImage(char *inputFile, unsigned char **readimage, int height, int width);
 int writeImagePGM(char *filename, int height, int width, unsigned char *image);

 #endif