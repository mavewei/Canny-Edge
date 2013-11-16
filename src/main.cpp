/* 
 * File:   main.cpp
 * Author: mavewei
 *
 * Created on October 30, 2013, 10:54 AM
 */

 #include "main.h"

// void magXY(short int *deltaX, short int *deltaY, short int **magnitude) {
//     int pos, sq1, sq2;
//     (*magnitude) = (short *) calloc(HEIGHT*WIDTH, sizeof (short));
//     for (int i = 0, pos = 0; i < HEIGHT; i++) {
//         for (int j = 0; j < WIDTH; j++, pos++) {
//             sq1 = (int) deltaX[pos] * (int) deltaX[pos];
//             sq2 = (int) deltaY[pos] * (int) deltaY[pos];
//             (*magnitude)[pos] = (short) (0.5 + sqrt((float) sq1 + (float) sq2));
//         }
//     }
// }

// double angleRad(double x, double y) {
//     double xu, yu, ang;
//     xu = fabs(x);
//     yu = fabs(y);
//     if ((xu == 0) && (yu == 0))
//         return (0);
//     ang = atan(yu / xu);
//     if (x >= 0) {
//         if (y >= 0)
//             return (ang);
//         else
//             return (2 * M_PI - ang);
//     } else {
//         if (y >= 0)
//             return (M_PI - ang);
//         else
//             return (M_PI + ang);
//     }
// }

// void radianDir(short int *deltaX, short int *deltaY, float **radiansImg, int xdirtag, int ydirtag) {
//     int pos;
//     float *dirim;
//     double dx, dy;
//     dirim = (float *) calloc(HEIGHT*WIDTH, sizeof (float));
//     *radiansImg = dirim;
//     for (int i = 0, pos = 0; i < HEIGHT; i++) {
//         for (int j = 0; j < WIDTH; j++, pos++) {
//             dx = (double) deltaX[pos];
//             dy = (double) deltaY[pos];
//             if (xdirtag == 1)
//                 dx = -dx;
//             if (ydirtag == -1)
//                 dy = -dy;
//             dirim[pos] = (float) angleRad(dx, dy);
//         }
//     }
// }

// void derrXY(short int *gsmoothImage, short int **deltaX, short int **deltaY) {
//     int pos;
//     (*deltaX) = (short *) calloc(HEIGHT*WIDTH, sizeof (short));
//     (*deltaY) = (short *) calloc(HEIGHT*WIDTH, sizeof (short));
//     if (VERBOSE)
//         printf("   Computing the X-direction derivative.\n");
//     for (int i = 0; i < HEIGHT; i++) {
//         pos = i * WIDTH;
//         (*deltaX)[pos] = gsmoothImage[pos + 1] - gsmoothImage[pos];
//         pos++;
//         for (int j = 1; j < (WIDTH - 1); j++, pos++) {
//             (*deltaX)[pos] = gsmoothImage[pos] - gsmoothImage[pos - 1];
//         }
//         (*deltaX)[pos] = gsmoothImage[pos] - gsmoothImage[pos - 1];
//     }
//     if (VERBOSE)
//         printf("   Computing the Y-direction derivative.\n");
//     for (int j = 0; j < WIDTH; j++) {
//         pos = j;
//         (*deltaY)[pos] = gsmoothImage[pos + WIDTH] - gsmoothImage[pos];
//         pos += WIDTH;
//         for (int i = 1; i < (HEIGHT - 1); i++, pos += WIDTH) {
//             (*deltaY)[pos] = gsmoothImage[pos + WIDTH] - gsmoothImage[pos - WIDTH];
//         }
//         (*deltaY)[pos] = gsmoothImage[pos] - gsmoothImage[pos - WIDTH];
//     }
// }

// void nonMaxSup(short *mag, short *gradX, short *gradY, unsigned char *result) {
//     unsigned char *resultrowptr, *resultptr;
//     short *magrowptr, *magptr, *gxrowptr, *gxptr, *gyrowptr, *gyptr;
//     short z1, z2, m00, gx, gy;
//     int rowcount, colcount, count;
//     float mag1, mag2, xperp, yperp;

//     for (count = 0, resultrowptr = result, resultptr = result + WIDTH * (HEIGHT - 1);
//         count < WIDTH; resultptr++, resultrowptr++, count++) {
//         *resultrowptr = *resultptr = (unsigned char) 0;
// }
// for (count = 0, resultptr = result, resultrowptr = result + WIDTH - 1;
//     count < HEIGHT; count++, resultptr += WIDTH, resultrowptr += WIDTH) {
//     *resultptr = *resultrowptr = (unsigned char) 0;
// }
// for (rowcount = 1, magrowptr = mag + WIDTH + 1, gxrowptr = gradX + WIDTH + 1,
//     gyrowptr = gradY + WIDTH + 1, resultrowptr = result + WIDTH + 1;
//     rowcount < HEIGHT - 2; rowcount++, magrowptr += WIDTH, gyrowptr += WIDTH, gxrowptr += WIDTH, resultrowptr += WIDTH) {
//     for (colcount = 1, magptr = magrowptr, gxptr = gxrowptr, gyptr = gyrowptr, resultptr = resultrowptr;
//         colcount < WIDTH - 2; colcount++, magptr++, gxptr++, gyptr++, resultptr++) {
//         m00 = *magptr;

//     if (m00 == 0) {
//         *resultptr = (unsigned char) NOEDGE;
//     } else {
//         xperp = -(gx = *gxptr) / ((float) m00);
//         yperp = (gy = *gyptr) / ((float) m00);
//     }
//     if (gx >= 0) {
//         if (gy >= 0) {
//             if (gx >= gy) {
//                         /* 111 */
//                         /* Left point */
//                 z1 = *(magptr - 1);
//                 z2 = *(magptr - WIDTH - 1);
//                 mag1 = (m00 - z1) * xperp + (z2 - z1) * yperp;
//                         /* Right point */
//                 z1 = *(magptr + 1);
//                 z2 = *(magptr + WIDTH + 1);
//                 mag2 = (m00 - z1) * xperp + (z2 - z1) * yperp;
//             } else {
//                         /* 110 */
//                         /* Left point */
//                 z1 = *(magptr - WIDTH);
//                 z2 = *(magptr - WIDTH - 1);
//                 mag1 = (z1 - z2) * xperp + (z1 - m00) * yperp;
//                         /* Right point */
//                 z1 = *(magptr + WIDTH);
//                 z2 = *(magptr + WIDTH + 1);
//                 mag2 = (z1 - z2) * xperp + (z1 - m00) * yperp;
//             }
//         } else {
//             if (gx >= -gy) {
//                         /* 101 */
//                         /* Left point */
//                 z1 = *(magptr - 1);
//                 z2 = *(magptr + WIDTH - 1);
//                 mag1 = (m00 - z1) * xperp + (z1 - z2) * yperp;
//                         /* Right point */
//                 z1 = *(magptr + 1);
//                 z2 = *(magptr - WIDTH + 1);
//                 mag2 = (m00 - z1) * xperp + (z1 - z2) * yperp;
//             } else {
//                         /* 100 */
//                         /* Left point */
//                 z1 = *(magptr + WIDTH);
//                 z2 = *(magptr + WIDTH - 1);
//                 mag1 = (z1 - z2) * xperp + (m00 - z1) * yperp;
//                         /* Right point */
//                 z1 = *(magptr - WIDTH);
//                 z2 = *(magptr - WIDTH + 1);
//                 mag2 = (z1 - z2) * xperp + (m00 - z1) * yperp;
//             }
//         }
//     } else {
//         if ((gy = *gyptr) >= 0) {
//             if (-gx >= gy) {
//                         /* 011 */
//                         /* Left point */
//                 z1 = *(magptr + 1);
//                 z2 = *(magptr - WIDTH + 1);
//                 mag1 = (z1 - m00) * xperp + (z2 - z1) * yperp;
//                         /* Right point */
//                 z1 = *(magptr - 1);
//                 z2 = *(magptr + WIDTH - 1);
//                 mag2 = (z1 - m00) * xperp + (z2 - z1) * yperp;
//             } else {
//                         /* 010 */
//                         /* Left point */
//                 z1 = *(magptr - WIDTH);
//                 z2 = *(magptr - WIDTH + 1);
//                 mag1 = (z2 - z1) * xperp + (z1 - m00) * yperp;
//                         /* Right point */
//                 z1 = *(magptr + WIDTH);
//                 z2 = *(magptr + WIDTH - 1);
//                 mag2 = (z2 - z1) * xperp + (z1 - m00) * yperp;
//             }
//         } else {
//             if (-gx > -gy) {
//                         /* 001 */
//                         /* Left point */
//                 z1 = *(magptr + 1);
//                 z2 = *(magptr + WIDTH + 1);
//                 mag1 = (z1 - m00) * xperp + (z1 - z2) * yperp;
//                         /* Right point */
//                 z1 = *(magptr - 1);
//                 z2 = *(magptr - WIDTH - 1);
//                 mag2 = (z1 - m00) * xperp + (z1 - z2) * yperp;
//             } else {
//                         /* 000 */
//                         /* Left point */
//                 z1 = *(magptr + WIDTH);
//                 z2 = *(magptr + WIDTH + 1);
//                 mag1 = (z2 - z1) * xperp + (m00 - z1) * yperp;
//                         /* Right point */
//                 z1 = *(magptr - WIDTH);
//                 z2 = *(magptr - WIDTH - 1);
//                 mag2 = (z2 - z1) * xperp + (m00 - z1) * yperp;
//             }
//         }
//     }

//     if ((mag1 > 0.0) || (mag2 > 0.0)) {
//         *resultptr = (unsigned char) NOEDGE;
//     } else {
//         if (mag2 == 0.0)
//             *resultptr = (unsigned char) NOEDGE;
//         else
//             *resultptr = (unsigned char) POSSIBLE_EDGE;
//     }
// }
// }
// }

// void follow_edges(unsigned char *edgemapptr, short *edgemagptr, short lowval, int cols) {
//     short *tempmagptr;
//     unsigned char *tempmapptr;
//     int i;
//     float thethresh;
//     int x[8] = {1, 1, 0, -1, -1, -1, 0, 1},
//     y[8] = {0, 1, 1, 1, 0, -1, -1, -1};

//     for (i = 0; i < 8; i++) {
//         tempmapptr = edgemapptr - y[i] * cols + x[i];
//         tempmagptr = edgemagptr - y[i] * cols + x[i];

//         if ((*tempmapptr == POSSIBLE_EDGE) && (*tempmagptr > lowval)) {
//             *tempmapptr = (unsigned char) EDGE;
//             follow_edges(tempmapptr, tempmagptr, lowval, cols);
//         }
//     }
// }

// void applyHysteresis(short int *mag, unsigned char *nms, float tlow, float thigh, unsigned char *edge) {
//     int r, c, pos, numedges, lowcount, highcount;
//     int lowthreshold, highthreshold, i, hist[32768], rr, cc;
//     short int maximum_mag, sumpix;

//     for (r = 0, pos = 0; r < HEIGHT; r++) {
//         for (c = 0; c < WIDTH; c++, pos++) {
//             if (nms[pos] == POSSIBLE_EDGE) edge[pos] = POSSIBLE_EDGE;
//             else edge[pos] = NOEDGE;
//         }
//     }

//     for (r = 0, pos = 0; r < HEIGHT; r++, pos += WIDTH) {
//         edge[pos] = NOEDGE;
//         edge[pos + WIDTH - 1] = NOEDGE;
//     }
//     pos = (HEIGHT - 1) * WIDTH;
//     for (c = 0; c < WIDTH; c++, pos++) {
//         edge[c] = NOEDGE;
//         edge[pos] = NOEDGE;
//     }
//     for (r = 0; r < 32768; r++) hist[r] = 0;
//         for (r = 0, pos = 0; r < HEIGHT; r++) {
//             for (c = 0; c < WIDTH; c++, pos++) {
//                 if (edge[pos] == POSSIBLE_EDGE) hist[mag[pos]]++;
//             }
//         }

//         for (r = 1, numedges = 0; r < 32768; r++) {
//             if (hist[r] != 0) maximum_mag = r;
//             numedges += hist[r];
//         }

//         highcount = (int) (numedges * thigh + 0.5);

//         r = 1;
//         numedges = hist[1];
//         while ((r < (maximum_mag - 1)) && (numedges < highcount)) {
//             r++;
//             numedges += hist[r];
//         }
//         highthreshold = r;
//         lowthreshold = (int) (highthreshold * tlow + 0.5);

//         if (VERBOSE) {
//             printf("The input low and high fractions of %f and %f computed to\n",
//                 tlow, thigh);
//             printf("magnitude of the gradient threshold values of: %d %d\n",
//                 lowthreshold, highthreshold);
//         }

//         for (r = 0, pos = 0; r < HEIGHT; r++) {
//             for (c = 0; c < WIDTH; c++, pos++) {
//                 if ((edge[pos] == POSSIBLE_EDGE) && (mag[pos] >= highthreshold)) {
//                     edge[pos] = EDGE;
//                     follow_edges((edge + pos), (mag + pos), lowthreshold, WIDTH);
//                 }
//             }
//         }

//         for (r = 0, pos = 0; r < HEIGHT; r++) {
//             for (c = 0; c < WIDTH; c++, pos++) if (edge[pos] != EDGE) edge[pos] = NOEDGE;
//         }
// }

// void canny(unsigned char *readImage, unsigned char **writeImage, float gauSigma, float edgeT, float backT, char *composedFilename) {
//     float *radiansImg;
//     short int *gsmoothImage, *deltaX, *deltaY, *magnitude;
//     unsigned char *nms;
//     FILE *fp;

//     if (VERBOSE)
//         printf("Gaussian smoothing ...\n");
//     gaussianSmooth(readImage, &gsmoothImage, gauSigma);

//     if (VERBOSE)
//         printf("Computing the X and Y first derivaties.\n");
//     derrXY(gsmoothImage, &deltaX, &deltaY);

//     radianDir(deltaX, deltaY, &radiansImg, -1, -1);
// //    fp = fopen(composedFilename, "wb");
// //    fwrite(radiansImg, sizeof (float), HEIGHT*WIDTH, fp);
// //
// //    fclose(fp);
// //    free(radiansImg);

//     if (VERBOSE)
//         printf("Computing the magnitude of the gradient.\n");
//     magXY(deltaX, deltaY, &magnitude);

//     if (VERBOSE)
//         printf("Doing the non-maximal suppression.\n");

//     nms = (unsigned char *) calloc(HEIGHT*WIDTH, sizeof (unsigned char));

//     nonMaxSup(magnitude, deltaX, deltaY, nms);
//     if (VERBOSE)
//         printf("Doing hysteresis thresholding.\n");
//     (*writeImage) = (unsigned char *) calloc(HEIGHT*WIDTH, sizeof (unsigned char));
//     applyHysteresis(magnitude, nms, edgeT, backT, *writeImage);

//     free(gsmoothImage);
//     free(deltaX);
//     free(deltaY);
//     free(magnitude);
//     free(nms);
// }

/*
 * 
 */
 int main(int argc, char** argv) {

    float sigma, edgeThrw, backThrw;
    char *inputFilename = NULL;
    char composedFilename[128];
    // char outputFilename[128];
    unsigned char *inputImage, *outputImage;

    if (argc != 5) {
        fprintf(stderr, "\n<USAGE>: %s [image-file-name] sigma edgeIntsty backIntsty\n", argv[0]);
        fprintf(stderr, "\n      image-file-name: An input image file.\n");
        fprintf(stderr, "      sigma: Standard deviation of gaussian.\n");
        fprintf(stderr, "      edgeIntsty: Fraction of the high edge strength (0.0~1.0)\n");
        fprintf(stderr, "      backIntsty: Fraction of the distribution of non-zero edge (0.0~1.0)\n\n");
        exit(1);
    }

    inputFilename = argv[1];
    sigma = atof(argv[2]);
    edgeThrw = atof(argv[3]);
    backThrw = atof(argv[4]);

    if (VERBOSE)
        printf("\nStep 1: Reading the image %s\n", inputFilename);
    if (readImage(inputFilename, &inputImage, HEIGHT, WIDTH) != 0) {
        fprintf(stderr, "***TERMINATED: Critical error found!\n\n");
        exit(1);
    }

    if (VERBOSE)
        printf("Step 2: Starting perform Canny edge detection.\n\n");
    sprintf(composedFilename, "Canny.film");

    canny(inputImage, &outputImage, sigma, edgeThrw, backThrw, composedFilename);
    sprintf(composedFilename, "canny.pgm");
    if (VERBOSE)
        printf("Writing the edge iname in the file %s.\n", composedFilename);
    writeImagePGM(composedFilename, HEIGHT, WIDTH, outputImage);

    return 0;
}

