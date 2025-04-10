#include "variance.h"
#include <math.h>

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
            r += (double) rgb_data[(i * width + j) * 3];
            g += (double) rgb_data[(i * width + j) * 3 + 1];
            b += (double) rgb_data[(i * width + j) * 3 + 2];
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
            double diff_r = rgb_data[(i * width + j) * 3] - mr;
            double diff_g = rgb_data[(i * width + j) * 3 + 1] - mg;
            double diff_b = rgb_data[(i * width + j) * 3 + 2] - mb;
            sr += diff_r * diff_r;
            sg += diff_g * diff_g;
            sb += diff_b * diff_b;
        }
    }
    
    int area = (row_end - row_start + 1) * (col_end - col_start + 1);
    return (sr + sg + sb)/(area*3);
}

double mean_absolute_deviation(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
                               int col_end, int width, int height) {
    double res;
    double mr, mg, mb, sr = 0, sg = 0, sb = 0;
    average(rgb_data, row_start, col_start, row_end, col_end, width, height, &mr, &mg, &mb);
    for (int i = row_start; i <= row_end; i++){
        for (int j = col_start; j <= col_end; j++){
            sr += fabs(rgb_data[(i * width + j) * 3] - mr);
            sg += fabs(rgb_data[(i * width + j) * 3 +   1] - mg);
            sb += fabs(rgb_data[(i * width + j) * 3 +   2] - mb);
        }
    }
    int area = (row_end - row_start + 1) * (col_end - col_start + 1);
    return (sr + sg + sb)/(area*3);
}

double max_pixel_difference(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
                            int col_end, int width, int height) {
    double max_r = 0, min_r = 255; 
    double max_g = 0, min_g = 255;
    double max_b = 0, min_b = 255;
    double r, g, b;
    for (int i = row_start; i <= row_end; i++){
        for (int j = col_start; j <= col_end; j++){
            r = (double) rgb_data[(i * width + j) * 3];
            g = (double) rgb_data[(i * width + j) * 3 + 1];
            b = (double) rgb_data[(i * width + j) * 3 + 2];
            max_r = r > max_r ? r : max_r;
            max_g = g > max_g ? g : max_g;
            max_b = b > max_b ? b : max_b;
            min_r = r < min_r ? r : min_r;
            min_g = g < min_g ? g : min_g;
            min_b = b < min_b ? b : min_b;
        }
    }
    
    return (max_r - min_r + max_g - min_g + max_b - min_b) / 3;
}

void create_freq_table(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
                       int col_end, int width, int height, int freq_table[3][256]) {
    // initialize freq table
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 256; j++) {
            freq_table[i][j] = 0;
        }
    }

    // count frequency
    for (int i = row_start; i <= row_end; i++){
        for (int j = col_start; j <= col_end; j++){
            freq_table[0][rgb_data[(i * width + j) * 3]]++;
            freq_table[1][rgb_data[(i * width + j) * 3 + 1]]++;
            freq_table[2][rgb_data[(i * width + j) * 3 + 2]]++;
        }
    }
}

double entropy(const unsigned char *rgb_data, int row_start, int col_start, int row_end,
               int col_end, int width, int height) {
    int area = (row_end - row_start + 1) * (col_end - col_start + 1);
    double pr, pg, pb; 
    double hr = 0, hg = 0, hb = 0;
    int freq_table[3][256];
    create_freq_table(rgb_data, row_start, col_start, row_end, col_end, width, height, freq_table);
 
    for (int i = 0; i < 256; i++) {
        if (freq_table[0][i] > 0) {
            double pr = (double) freq_table[0][i] / area;
            hr += pr * log2(pr);
        }
        if (freq_table[1][i] > 0) {
            double pg = (double) freq_table[1][i] / area;
            hg += pg * log2(pg);
        }
        if (freq_table[2][i] > 0) {
            double pb = (double) freq_table[2][i] / area;
            hb += pb * log2(pb);
        }
    }

    hr *= -1;
    hg *= -1;
    hb *= -1;

    return (hr + hg + hb) / 3;
}