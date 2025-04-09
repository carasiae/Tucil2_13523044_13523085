#include "variance.h"
#include <omp.h>

static unsigned int seed = 100;
RGB average(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
            int col_end,int width, int height){
    RGB res;
    double r, g, b;
    #pragma omp parallel for reduction(+: r, g, b)
    for (int i = row_start; i <= row_end; i++){
        for (int j = col_start; j <= col_end; j++){
            r += (double) rgb_data[(i * width + j) * 3];
            g += (double) rgb_data[(i * width + j) * 3 + 1];
            b += (double) rgb_data[(i * width + j) * 3 + 2];
        }
    }
    int area = (row_end - row_start + 1) * (col_end - col_start + 1);
    res.r = (unsigned char) (r / area);
    res.g = (unsigned char) (g / area);
    res.b = (unsigned char) (b / area);
    return res;
}
double variance(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
            int col_end,int width, int height) {
    return 1;
}
double mean_absolute_deviation(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
            int col_end,int width, int height) {
    return 1;
}
double max_pixel_difference(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
            int col_end,int width, int height) {
    return 1;
}
double entropy(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
            int col_end,int width, int height) {
    return 1;
}