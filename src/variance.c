#include "variance.h"
#include <math.h>

static unsigned int seed = 100;
RGB average_rgb(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
            int col_end,int width, int height){
    RGB res;
    double r = 0, g = 0, b = 0;
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

void average(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
            int col_end,int width, int height, double *avg_r, double *avg_g, double *avg_b){
    double r = 0, g = 0, b = 0;
    for (int i = row_start; i <= row_end; i++){
        for (int j = col_start; j <= col_end; j++){
            r += (double) rgb_data[(i*width+j)*3];
            g += (double) rgb_data[(i*width+j)*3+1];
            b += (double) rgb_data[(i*width+j)*3+2];
        }
    }
    int area = (row_end - row_start + 1) * (col_end - col_start + 1);
    *avg_r = r / area;
    *avg_g = g / area;
    *avg_b = b / area;
}

double variance(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
            int col_end,int width, int height) {
    double res;
    double mr, mg, mb, sr=0, sg=0, sb=0;
    average(rgb_data, row_start, col_start, row_end, col_end, width, height, &mr, &mg, &mb);
    for (int i = row_start; i <= row_end; i++){
        for (int j = col_start; j <= col_end; j++){
            double diff_r = rgb_data[(i*width+j)*3] - mr;
            double diff_g = rgb_data[(i*width+j)*3+1] - mg;
            double diff_b = rgb_data[(i*width+j)*3+2] - mb;
            sr += diff_r * diff_r;
            sg += diff_g * diff_g;
            sb += diff_b * diff_b;
        }
    }
    
    int area = (row_end - row_start + 1) * (col_end - col_start + 1);
    return (sr + sg + sb)/(area*3);
}
double mean_absolute_deviation(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
            int col_end,int width, int height) {
    double res;
    double mr, mg, mb, sr=0, sg=0, sb=0;
    average(rgb_data, row_start, col_start, row_end, col_end, width, height, &mr, &mg, &mb);
    for (int i = row_start; i <= row_end; i++){
        for (int j = col_start; j <= col_end; j++){
            sr += fabs(rgb_data[(i*width+j)*3] - mr);
            sg += fabs(rgb_data[(i*width+j)*3+1] - mg);
            sb += fabs(rgb_data[(i*width+j)*3+2] - mb);
        }
    }
    int area = (row_end - row_start + 1) * (col_end - col_start + 1);
    return (sr + sg + sb)/(area*3);
}
double max_pixel_difference(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
            int col_end,int width, int height) {
    return 1;
}
double entropy(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
            int col_end,int width, int height) {
    return 1;
}