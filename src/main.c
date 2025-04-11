#include <stdio.h>
#include <stdlib.h>
#include "compression.h"
#include "qtree.h"
#include "variance.h"
#include "cli.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <time.h>
#include "file_size.h"
#include "mgif.h"

int MAX_FILEPATH_LEN = 1024;

int main(int argc, char **argv){
    char input_filename[MAX_FILEPATH_LEN];
    char output_filename[MAX_FILEPATH_LEN];
    char gif_output_filename[MAX_FILEPATH_LEN];
    int x, y, n, minimum_block_size;
    double error_threshold;
    VarianceFunction *variance_fn;
     
    get_input(input_filename, output_filename, gif_output_filename, &minimum_block_size, &error_threshold, &variance_fn);

    clock_t start = clock();

    int initial_size = file_size(input_filename);
    unsigned char *rgb_input = stbi_load(input_filename, &x, &y, &n, 3);
    unsigned char *rgb_output = malloc(sizeof(unsigned char) * 3 * x * y);
    if (rgb_input == NULL){
        fputs("Something went wrong, your image might be corrupted or is not in the correct format\n", stdout);
        return 1;
    }

    QTreeNode tree = qtree_new(x, y);
    quad_tree_compression(rgb_input, rgb_output, x, y, error_threshold, minimum_block_size,
                          variance_fn, tree);
    stbi_write_png(output_filename, x, y, n, rgb_output, x*n);

    clock_t end = clock();

    double exec_time = (double) (end - start) / (double) CLOCKS_PER_SEC * 1000;
    int final_size = file_size(output_filename);
    double ratio = (double) (initial_size - final_size) / (double) initial_size * 100;
    int tree_depth = qtree_depth(tree);

    // gif creation
    create_gif(tree, gif_output_filename, x, y, tree_depth);

    printf("Waktu eksekusi   : %f ms\n", exec_time);
    printf("Kedalaman pohon  : %d\n", tree_depth);
    printf("Banyak node pohon: %d\n", qtree_n_nodes(tree));
    printf("Besar file awal  : %d byte\n", initial_size);
    printf("Besar file akhir : %d byte\n", final_size);
    printf("Rasio kompresi   : %.2f%%\n", ratio);

    
    free(rgb_output);
}