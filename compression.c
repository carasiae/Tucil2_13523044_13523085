#include "compression.h"
#include "qtree.h"
#include <omp.h>


void _quad_tree_compression_helper(const unsigned char *rgb_input,
                                   unsigned char       *rgb_output,
                                   int                  width,
                                   int                  height,
                                   double               error_threshold,
                                   int                  minimum_block_size,
                                   VarianceFunction     variance_fn,
                                   QTreeNode            current_index) {
    if (NODE(current_index).width * NODE(current_index).height / 4 < minimum_block_size) {
        goto compute_color;
    }
    double variance = (*variance_fn)(rgb_input, NODE(current_index).row,
                                     NODE(current_index).col, NODE(current_index).width,
                                     NODE(current_index).height);
    if (variance >= error_threshold) {
        QTreeNode next = qtree_subdivide(current_index);
        for (int i = 0; i < 4; i++) {
            #pragma omp task
            _quad_tree_compression_helper(rgb_input, rgb_output, width, height, error_threshold,
                                          minimum_block_size, variance_fn, next+i);
        }
        return;
    }
compute_color:;
    RGB avg = average(rgb_input,
                      NODE(current_index).row,
                      NODE(current_index).col,
                      NODE(current_index).width,
                      NODE(current_index).height);
    NODE(current_index).data.rgb = avg;
}

void quad_tree_compression(const unsigned char *rgb_input,
                           unsigned char       *rgb_output,
                           int                  width,
                           int                  height,
                           double               error_threshold,
                           int                  minimum_block_size,
                           VarianceFunction     variance_fn,
                           QTreeNode            current_index) {
    #pragma omp parallel
    #pragma omp single
    {
        _quad_tree_compression_helper(rgb_input, rgb_output, width, height,
                                    error_threshold, minimum_block_size,
                                    variance_fn, current_index);
    }
}