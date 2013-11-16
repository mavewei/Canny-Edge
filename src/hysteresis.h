/* 
 * File:   hysteresis.h
 * Author: mavewei
 *
 * Created on October 31, 2013, 5:28 PM
 */

 #ifndef __HYSTERESIS_H__
 #define __HYSTERESIS_H__

 void follow_edges(unsigned char *edgemapptr, short *edgemagptr, short lowval, int cols);
 void applyHysteresis(short int *mag, unsigned char *nms, float tlow, float thigh, unsigned char *edge);
 void nonMaxSup(short *mag, short *gradX, short *gradY, unsigned char *result);

 #endif