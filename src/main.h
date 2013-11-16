/* 
 * File:   canny.h
 * Author: mavewei
 */

 #ifndef __MAIN_H__
 #define __MAIN_H__

/*******************
 * Standard headers
 *******************/
 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <string.h>

/*******************
 * Program headers
 *******************/
 #include "fileIO.h"
 #include "gaussianSmooth.h"
 #include "hysteresis.h"
 #include "canny.h"

/*******************
 * Program DEFINE
 *******************/
 #define VERBOSE         0
 #define DEBUG           0
 #define HEIGHT          512
 #define WIDTH           512
 #define NOEDGE          0
 #define EDGE            255
 #define POSSIBLE_EDGE   128
 #define BLURFACTOR      90.0

 #endif