#include "compression.h"
#include "qtree.h"
#include "variance.h"
#include <omp.h>


void _quad_tree_compression_helper(const unsigned char *rgb_input,
                                   unsigned char       *rgb_output,
                                   int                  width,
                                   int                  height,
                                   double               error_threshold,
                                   int                  minimum_block_size,
                                   VarianceFunction     variance_fn,
                                   QTreeNode            tree) {
    // can't subdivide further
    if (NODE(tree).width * NODE(tree).height / 4 < minimum_block_size) {
        goto compute_color;
    }

    int row_start = NODE(tree).row;
    int col_start = NODE(tree).col;
    int row_end = row_start + NODE(tree).height - 1;
    int col_end = col_start + NODE(tree).width - 1;
    double variance = (*variance_fn)(rgb_input, row_start, col_start, row_end,
                                     col_end, width, height);

    if (variance >= error_threshold) {
        QTreeNode next = qtree_subdivide(tree);
        for (int i = 0; i < 4; i++) {
            #pragma omp task
            _quad_tree_compression_helper(rgb_input, rgb_output, width, height,
                                          error_threshold, minimum_block_size,
                                          variance_fn, next+i);
        }
        return;
    }

compute_color:
    NODE(tree).data.rgb = average_rgb(rgb_input, row_start, col_start, row_end,
                                      col_end, width, height);
    return;
}

void quad_tree_compression(const unsigned char *rgb_input,
                           unsigned char       *rgb_output,
                           int                  width,
                           int                  height,
                           double               error_threshold,
                           int                  minimum_block_size,
                           VarianceFunction     variance_fn,
                           QTreeNode            tree) {
    #pragma omp parallel
    #pragma omp single
    {
        _quad_tree_compression_helper(rgb_input, rgb_output, width, height,
                                      error_threshold, minimum_block_size,
                                      variance_fn, tree);
    }
}