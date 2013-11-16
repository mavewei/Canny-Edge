/* 
 * File:   canny.cpp
 * Author: mavewei
 *
 * Created on October 31, 2013, 5:28 PM
 */ 

 #include "main.h"

 void canny(unsigned char *readImage, unsigned char **writeImage, float gauSigma, float edgeT, float backT, char *composedFilename) {
 	float *radiansImg;
 	short int *gsmoothImage, *deltaX, *deltaY, *magnitude;
 	unsigned char *nms;
 	// FILE *fp;

 	(*writeImage) = (unsigned char *) calloc(HEIGHT*WIDTH, sizeof (unsigned char));

 	if (VERBOSE) printf("Gaussian smoothing ...\n");
 	gaussianSmooth(readImage, &gsmoothImage, gauSigma);

 	if (VERBOSE) printf("Computing the X and Y first derivaties.\n");
 	derrXY(gsmoothImage, &deltaX, &deltaY);

 	radianDir(deltaX, deltaY, &radiansImg, -1, -1);

 	if (VERBOSE) printf("Computing the magnitude of the gradient.\n");
 	magXY(deltaX, deltaY, &magnitude);

 	if (VERBOSE) printf("Doing the non-maximal suppression.\n");
 	nms = (unsigned char *) calloc(HEIGHT*WIDTH, sizeof (unsigned char));
 	nonMaxSup(magnitude, deltaX, deltaY, nms);

 	if (VERBOSE) printf("Doing hysteresis thresholding.\n");
 	applyHysteresis(magnitude, nms, edgeT, backT, *writeImage);

 	free(gsmoothImage);
 	free(deltaX);
 	free(deltaY);
 	free(magnitude);
 	free(nms);
 }

 void radianDir(short int *deltaX, short int *deltaY, float **radiansImg, int xdirtag, int ydirtag) {
 	// int pos;
 	float *dirim;
 	double dx, dy;
 	dirim = (float *) calloc(HEIGHT*WIDTH, sizeof (float));

 	*radiansImg = dirim;
 	for (int i = 0, pos = 0; i < HEIGHT; i++) {
 		for (int j = 0; j < WIDTH; j++, pos++) {
 			dx = (double) deltaX[pos];
 			dy = (double) deltaY[pos];
 			if (xdirtag == 1)
 				dx = -dx;
 			if (ydirtag == -1)
 				dy = -dy;
 			dirim[pos] = (float) angleRad(dx, dy);
 		}
 	}
 }

 double angleRad(double x, double y) {
 	double xu, yu, ang;

 	xu = fabs(x);
 	yu = fabs(y);

 	if ((xu == 0) && (yu == 0))
 		return (0);

 	ang = atan(yu / xu);
 	
 	if (x >= 0) {
 		if (y >= 0)
 			return (ang);
 		else
 			return (2 * M_PI - ang);
 	} else {
 		if (y >= 0)
 			return (M_PI - ang);
 		else
 			return (M_PI + ang);
 	}
 }

 void magXY(short int *deltaX, short int *deltaY, short int **magnitude) {
 	// int pos; 
 	int sq1, sq2;

 	(*magnitude) = (short *) calloc(HEIGHT*WIDTH, sizeof (short));

 	for (int i = 0, pos = 0; i < HEIGHT; i++) {
 		for (int j = 0; j < WIDTH; j++, pos++) {
 			sq1 = (int) deltaX[pos] * (int) deltaX[pos];
 			sq2 = (int) deltaY[pos] * (int) deltaY[pos];
 			(*magnitude)[pos] = (short) (0.5 + sqrt((float) sq1 + (float) sq2));
 		}
 	}
 }

 void derrXY(short int *gsmoothImage, short int **deltaX, short int **deltaY) {
 	int pos;

 	(*deltaX) = (short *) calloc(HEIGHT*WIDTH, sizeof (short));
 	(*deltaY) = (short *) calloc(HEIGHT*WIDTH, sizeof (short));

 	if (VERBOSE) printf("   Computing the X-direction derivative.\n");
 	for (int i = 0; i < HEIGHT; i++) {
 		pos = i * WIDTH;
 		(*deltaX)[pos] = gsmoothImage[pos + 1] - gsmoothImage[pos];
 		pos++;

 		for (int j = 1; j < (WIDTH - 1); j++, pos++) {
 			(*deltaX)[pos] = gsmoothImage[pos] - gsmoothImage[pos - 1];
 		}
 		(*deltaX)[pos] = gsmoothImage[pos] - gsmoothImage[pos - 1];
 	}

 	if (VERBOSE) printf("   Computing the Y-direction derivative.\n");
 	for (int j = 0; j < WIDTH; j++) {
 		pos = j;
 		(*deltaY)[pos] = gsmoothImage[pos + WIDTH] - gsmoothImage[pos];
 		pos += WIDTH;
 		for (int i = 1; i < (HEIGHT - 1); i++, pos += WIDTH) {
 			(*deltaY)[pos] = gsmoothImage[pos + WIDTH] - gsmoothImage[pos - WIDTH];
 		}
 		(*deltaY)[pos] = gsmoothImage[pos] - gsmoothImage[pos - WIDTH];
 	}
 }