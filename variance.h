#ifndef ERROR_MEASUREMENT_H
#define ERROR_MEASUREMENT_H
#include "qtree.h"

typedef double (*VarianceFunction)(const unsigned char *, int row, int col, int width, int height);

RGB average(const unsigned char *rgb_data, int row, int col, int width, int height);
double variance(const unsigned char *rgb_data, int row, int col, int width, int height);
double mean_absolute_deviation(const unsigned char *rgb_data, int row, int col, int width, int height);
double max_pixel_difference(const unsigned char *rgb_data, int row, int col, int width, int height);
double entropy(const unsigned char *rgb_data, int row, int col, int width, int height);

#endif