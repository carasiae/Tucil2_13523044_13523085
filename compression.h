#ifndef COMPRESSION_H
#define COMPRESSION_H
#include "qtree.h"
#include "variance.h"


/** Does exactly as it sounds
    @param rgb_input            input image as arrays of pixel in the same
                                format as in stb_image library
    @param rgb_output           output image in the same format as input
    @param width                width of the image in pixels
    @param height               height of the image in pixels
    @param error_threshold      threshold of error/variance before a quadtree
                                is subdivided
    @param minimum_block_size   minimum area of a block (represented as a
                                quadtree node)
    @param variance_fn          the variance function used to determine
                                variance/error measurement
    @param current_node         current node of quadtree (representing a part
                                of image) processed 
*/
void quad_tree_compression(const unsigned char  *rgb_input,
                           unsigned char        *rgb_output,
                           int                  width,
                           int                  height,
                           double               error_threshold,
                           int                  minimum_block_size,
                           VarianceFunction     variance_fn,
                           QTreeNode            current_node);

#endif