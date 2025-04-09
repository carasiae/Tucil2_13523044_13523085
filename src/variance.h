#ifndef ERROR_MEASUREMENT_H
#define ERROR_MEASUREMENT_H
#include "qtree.h"

/** Variance function used to determine the variance of an area in an image
    @param rgb_data     pixels of an image, following stb_image's format
    @param row_start    starting row of the area to be calculated
    @param col_start    starting column of the area to be calculated
    @param row_end      ending row of the area to be calculated
    @param col_end      ending column of the area to be calculated
    @param width        width of the image
    @param height       height of the image
    @return             the variance value
*/
typedef double (VarianceFunction)(const unsigned char *rgb_data,
                                  int row_start,
                                  int col_start,
                                  int row_end,
                                  int col_end,
                                  int width,
                                  int height);

VarianceFunction variance;
VarianceFunction mean_absolute_deviation;
VarianceFunction max_pixel_difference;
VarianceFunction entropy;

/** Average (mean) RGB value of an area of an area in an image
    @param rgb_data     pixels of an image, following stb_image's format
    @param row_start    starting row of the area to be calculated
    @param col_start    starting column of the area to be calculated
    @param row_end      ending row of the area to be calculated
    @param col_end      ending column of the area to be calculated
    @param width        width of the image
    @param height       height of the image
    @return             the average value
*/
RGB average_rgb(const unsigned char *rgb_data,
                int row_start,
                int col_start,
                int row_end,
                int col_end,
                int width,
                int height);
#endif