#include "compression.h"
#include "qtree.h"
#include "variance.h"

void fill_color(unsigned char       *rgb_output,
                int                  width,
                int                  height,
                QTreeNode            tree) {
    int row_start = NODE(tree).row;
    int col_start = NODE(tree).col;
    int row_end = row_start + NODE(tree).height - 1;
    int col_end = col_start + NODE(tree).width - 1;
    unsigned char r = NODE(tree).data.rgb.r;
    unsigned char g = NODE(tree).data.rgb.g;
    unsigned char b = NODE(tree).data.rgb.b;
    // printf("row: %d-%d col:%d-%d r:%d g:%d b:%d\n", row_start, row_end, col_start, col_end, tree->data.rgb.r, tree->data.rgb.g, tree->data.rgb.b);
    for (int i = row_start; i <= row_end; i++){
        for (int j = col_start; j <= col_end; j++){
            rgb_output[(i*width+j)*3] = r;
            rgb_output[(i*width+j)*3+1] = g;
            rgb_output[(i*width+j)*3+2] = b;
        }
    }
}


void quad_tree_compression(const unsigned char *rgb_input,
                                   unsigned char       *rgb_output,
                                   int                  width,
                                   int                  height,
                                   double               error_threshold,
                                   int                  minimum_block_size,
                                   VarianceFunction    *variance_fn,
                                   QTreeNode            tree) {
    int row_start = NODE(tree).row;
    int col_start = NODE(tree).col;
    int row_end = row_start + NODE(tree).height - 1;
    int col_end = col_start + NODE(tree).width - 1;
    // can't subdivide further
    if (NODE(tree).width * NODE(tree).height / 4 < minimum_block_size) {
        goto compute_color;
    }

    double variance = (*variance_fn)(rgb_input, row_start, col_start, row_end,
                                     col_end, width, height);

    if (variance >= error_threshold) {
        QTreeNode next = qtree_subdivide(tree);
        
        for (int i = 0; i < 4; i++) {
            quad_tree_compression(rgb_input, rgb_output, width, height,
                                          error_threshold, minimum_block_size,
                                          variance_fn, next+i);
        }
        return;
    } 

compute_color:;
    RGB temp = average_rgb(rgb_input, row_start, col_start, row_end,
                                      col_end, width, height);
    NODE(tree).data.rgb = temp;
    // printf("row: %d-%d col:%d-%d r:%d g:%d b:%d\n", row_start, row_end, col_start, col_end, temp.r, temp.g, temp.b);
    fill_color(rgb_output, width, height, tree);
    return;
}