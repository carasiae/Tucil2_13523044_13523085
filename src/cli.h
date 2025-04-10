#ifndef CLI_H
#define CLI_H
#include "variance.h"

extern int MAX_FILEPATH_LEN;

/** gets user input. im just doing it so main isnt full from just this
    @param input_filepath       absolute address to image file
    @param output_filepath      absolute address to output compressed image file
    @param minimum_block_size   minimum area of a block (represented as a quadtree node)
    @param error_threshold      threshold of error/variance before a quadtreeyis subdivided
    @param variance_fn          memory address to the variance function of choice
*/
void get_input(char* input_filepath, 
               char* output_filepath, 
               int* minimum_block_size,
               double* error_threshold,
               VarianceFunction** variance_fn);

#endif