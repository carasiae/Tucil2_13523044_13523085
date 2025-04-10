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

int MAX_FILEPATH_LEN = 1024;

int main(int argc, char **argv){
    char input_filename[MAX_FILEPATH_LEN];
    char output_filename[MAX_FILEPATH_LEN];
    int x, y, n, minimum_block_size;
    double error_threshold;
    VarianceFunction *variance_fn;
     
    get_input(input_filename, output_filename, &minimum_block_size, &error_threshold, &variance_fn);

    unsigned char *rgb_input = stbi_load(input_filename, &x, &y, &n, 3);
    unsigned char *rgb_output;
    if (rgb_input == NULL){
        fputs("Something went wrong, your image might be corrupted or is not in the correct format\n", stdout);
        return 1;
    }

    QTreeNode tree = qtree_new(x, y);
    quad_tree_compression(rgb_input, rgb_output, x, y, error_threshold, minimum_block_size,
                          variance_fn, tree);
    stbi_write_png(output_filename, x, y, n, rgb_output, x*n);
}