/* 
 * File:   hysteresis.cpp
 * Author: mavewei
 *
 * Created on October 31, 2013, 5:28 PM
 */

 #include "main.h"

 void follow_edges(unsigned char *edgemapptr, short *edgemagptr, short lowval, int cols) {
    short *tempmagptr;
    unsigned char *tempmapptr;
    int i, x[8] = {1, 1, 0, -1, -1, -1, 0, 1}, y[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    for (i = 0; i < 8; i++) {
        tempmapptr = edgemapptr - y[i] * cols + x[i];
        tempmagptr = edgemagptr - y[i] * cols + x[i];

        if ((*tempmapptr == POSSIBLE_EDGE) && (*tempmagptr > lowval)) {
            *tempmapptr = (unsigned char) EDGE;
            follow_edges(tempmapptr, tempmagptr, lowval, cols);
        }
    }
}

void applyHysteresis(short int *mag, unsigned char *nms, float tlow, float thigh, unsigned char *edge) {
    int r, c, pos, numedges, highcount;
    int lowthreshold, highthreshold, hist[32768];
    short int maximum_mag;

    for (r = 0, pos = 0; r < HEIGHT; r++) {
        for (c = 0; c < WIDTH; c++, pos++) {
            if (nms[pos] == POSSIBLE_EDGE)
                edge[pos] = POSSIBLE_EDGE;
            else edge[pos] = NOEDGE;
        }
    }

    for (r = 0, pos = 0; r < HEIGHT; r++, pos += WIDTH) {
        edge[pos] = NOEDGE;
        edge[pos + WIDTH - 1] = NOEDGE;
    }

    pos = (HEIGHT - 1) * WIDTH;
    for (c = 0; c < WIDTH; c++, pos++) {
        edge[c] = NOEDGE;
        edge[pos] = NOEDGE;
    }

    for (r = 0; r < 32768; r++) {
        hist[r] = 0;
    }

    for (r = 0, pos = 0; r < HEIGHT; r++) {
        for (c = 0; c < WIDTH; c++, pos++) {
            if (edge[pos] == POSSIBLE_EDGE) hist[mag[pos]]++;
        }
    }

    for (r = 1, numedges = 0; r < 32768; r++) {
        if (hist[r] != 0) maximum_mag = r;
        numedges += hist[r];
    }

    highcount = (int) (numedges * thigh + 0.5);
    r = 1;
    numedges = hist[1];
    while ((r < (maximum_mag - 1)) && (numedges < highcount)) {
        r++;
        numedges += hist[r];
    }

    highthreshold = r;
    lowthreshold = (int) (highthreshold * tlow + 0.5);

    if (VERBOSE) {
        printf("The input low and high fractions of %f and %f computed to\n", tlow, thigh);
        printf("magnitude of the gradient threshold values of: %d %d\n", lowthreshold, highthreshold);
    }

    for (r = 0, pos = 0; r < HEIGHT; r++) {
        for (c = 0; c < WIDTH; c++, pos++) {
            if ((edge[pos] == POSSIBLE_EDGE) && (mag[pos] >= highthreshold)) {
                edge[pos] = EDGE;
                follow_edges((edge + pos), (mag + pos), lowthreshold, WIDTH);
            }
        }
    }

    for (r = 0, pos = 0; r < HEIGHT; r++) {
        for (c = 0; c < WIDTH; c++, pos++) if (edge[pos] != EDGE) edge[pos] = NOEDGE;
    }
}

void nonMaxSup(short *mag, short *gradX, short *gradY, unsigned char *result) {
    unsigned char *resultrowptr, *resultptr;
    short *magrowptr, *magptr, *gxrowptr, *gxptr, *gyrowptr, *gyptr;
    short z1, z2, m00, gx, gy;
    int rowcount, colcount, count;
    float mag1, mag2, xperp, yperp;

    for (count = 0, resultrowptr = result, resultptr = result + WIDTH * (HEIGHT - 1); count < WIDTH; resultptr++, resultrowptr++, count++) {
        *resultrowptr = *resultptr = (unsigned char) 0;
    }

    for (count = 0, resultptr = result, resultrowptr = result + WIDTH - 1; count < HEIGHT; count++, resultptr += WIDTH, resultrowptr += WIDTH) {
        *resultptr = *resultrowptr = (unsigned char) 0;
    }

    for (rowcount = 1, magrowptr = mag + WIDTH + 1, gxrowptr = gradX + WIDTH + 1, gyrowptr = gradY + WIDTH + 1, resultrowptr = result + WIDTH + 1; rowcount < HEIGHT - 2; rowcount++, magrowptr += WIDTH, gyrowptr += WIDTH, gxrowptr += WIDTH, resultrowptr += WIDTH) {
        for (colcount = 1, magptr = magrowptr, gxptr = gxrowptr, gyptr = gyrowptr, resultptr = resultrowptr; colcount < WIDTH - 2; colcount++, magptr++, gxptr++, gyptr++, resultptr++) {
            m00 = *magptr;

            if (m00 == 0) {
                *resultptr = (unsigned char) NOEDGE;
            } else {
                xperp = -(gx = *gxptr) / ((float) m00);
                yperp = (gy = *gyptr) / ((float) m00);
            }

            if (gx >= 0) {
                if (gy >= 0) {
                    if (gx >= gy) {
                        /* 111 */
                        /* Left point */
                        z1 = *(magptr - 1);
                        z2 = *(magptr - WIDTH - 1);
                        mag1 = (m00 - z1) * xperp + (z2 - z1) * yperp;
                        /* Right point */
                        z1 = *(magptr + 1);
                        z2 = *(magptr + WIDTH + 1);
                        mag2 = (m00 - z1) * xperp + (z2 - z1) * yperp;
                    } else {
                        /* 110 */
                        /* Left point */
                        z1 = *(magptr - WIDTH);
                        z2 = *(magptr - WIDTH - 1);
                        mag1 = (z1 - z2) * xperp + (z1 - m00) * yperp;
                        /* Right point */
                        z1 = *(magptr + WIDTH);
                        z2 = *(magptr + WIDTH + 1);
                        mag2 = (z1 - z2) * xperp + (z1 - m00) * yperp;
                    }
                } else {
                    if (gx >= -gy) {
                        /* 101 */
                        /* Left point */
                        z1 = *(magptr - 1);
                        z2 = *(magptr + WIDTH - 1);
                        mag1 = (m00 - z1) * xperp + (z1 - z2) * yperp;
                        /* Right point */
                        z1 = *(magptr + 1);
                        z2 = *(magptr - WIDTH + 1);
                        mag2 = (m00 - z1) * xperp + (z1 - z2) * yperp;
                    } else {
                        /* 100 */
                        /* Left point */
                        z1 = *(magptr + WIDTH);
                        z2 = *(magptr + WIDTH - 1);
                        mag1 = (z1 - z2) * xperp + (m00 - z1) * yperp;
                        /* Right point */
                        z1 = *(magptr - WIDTH);
                        z2 = *(magptr - WIDTH + 1);
                        mag2 = (z1 - z2) * xperp + (m00 - z1) * yperp;
                    }
                }
            } else {
                if ((gy = *gyptr) >= 0) {
                    if (-gx >= gy) {
                        /* 011 */
                        /* Left point */
                        z1 = *(magptr + 1);
                        z2 = *(magptr - WIDTH + 1);
                        mag1 = (z1 - m00) * xperp + (z2 - z1) * yperp;
                        /* Right point */
                        z1 = *(magptr - 1);
                        z2 = *(magptr + WIDTH - 1);
                        mag2 = (z1 - m00) * xperp + (z2 - z1) * yperp;
                    } else {
                        /* 010 */
                        /* Left point */
                        z1 = *(magptr - WIDTH);
                        z2 = *(magptr - WIDTH + 1);
                        mag1 = (z2 - z1) * xperp + (z1 - m00) * yperp;
                        /* Right point */
                        z1 = *(magptr + WIDTH);
                        z2 = *(magptr + WIDTH - 1);
                        mag2 = (z2 - z1) * xperp + (z1 - m00) * yperp;
                    }
                } else {
                    if (-gx > -gy) {
                        /* 001 */
                        /* Left point */
                        z1 = *(magptr + 1);
                        z2 = *(magptr + WIDTH + 1);
                        mag1 = (z1 - m00) * xperp + (z1 - z2) * yperp;
                        /* Right point */
                        z1 = *(magptr - 1);
                        z2 = *(magptr - WIDTH - 1);
                        mag2 = (z1 - m00) * xperp + (z1 - z2) * yperp;
                    } else {
                        /* 000 */
                        /* Left point */
                        z1 = *(magptr + WIDTH);
                        z2 = *(magptr + WIDTH + 1);
                        mag1 = (z2 - z1) * xperp + (m00 - z1) * yperp;
                        /* Right point */
                        z1 = *(magptr - WIDTH);
                        z2 = *(magptr - WIDTH - 1);
                        mag2 = (z2 - z1) * xperp + (m00 - z1) * yperp;
                    }
                }
            }

            if ((mag1 > 0.0) || (mag2 > 0.0)) {
                *resultptr = (unsigned char) NOEDGE;
            } else {
                if (mag2 == 0.0)
                    *resultptr = (unsigned char) NOEDGE;
                else
                    *resultptr = (unsigned char) POSSIBLE_EDGE;
            }
        }
    }
}