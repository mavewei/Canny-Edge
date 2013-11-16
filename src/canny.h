/* 
 * File:   canny.h
 * Author: mavewei
 *
 * Created on October 31, 2013, 5:28 PM
 */

 #ifndef __CANNY_H__
 #define __CANNY_H__

 void canny(unsigned char *readImage, unsigned char **writeImage, float gauSigma, float edgeT, float backT, char *composedFilename);
 void radianDir(short int *deltaX, short int *deltaY, float **radiansImg, int xdirtag, int ydirtag);
 double angleRad(double x, double y);
 void magXY(short int *deltaX, short int *deltaY, short int **magnitude);
 void derrXY(short int *gsmoothImage, short int **deltaX, short int **deltaY);

 #endif