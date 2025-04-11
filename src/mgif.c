#include "mgif.h"
#include "gif.h"
#include "compression.h"

void create_gif_frame(GifWriter *writer, unsigned char *rgb_output, int width, int height) {
    // Convert RGB (3 channel) to 4-channel RGBA (needed by gif.h)
    uint8_t *rgba = malloc(width * height * 4);
    for (int i = 0; i < width * height; i++) {
        rgba[i * 4 + 0] = rgb_output[i * 3 + 0];
        rgba[i * 4 + 1] = rgb_output[i * 3 + 1];
        rgba[i * 4 + 2] = rgb_output[i * 3 + 2];
        rgba[i * 4 + 3] = 255;
    }

    GifWriteFrame(writer, rgba, width, height, 70, 8, false); 

    free(rgba);
}

void create_gif_helper(QTreeNode tree, unsigned char * gif_rgb_output, 
                       int x, int y, int cur_depth, int max_depth) {
    for (int i = cur_depth; i < max_depth; i++) {
        fill_color(gif_rgb_output + (3 * x * y * i), x, y, tree);
    }

    if (tree->node_type == INTERNAL_NODE) {
        QTreeNode next = NODE(tree).data.first_child;
        for (int i = 0; i < 4; i++) {
            create_gif_helper(next + i, gif_rgb_output, x, y, cur_depth + 1, max_depth);
        }
    }
}

void create_gif(QTreeNode tree, char * filepath, int x, int y, int max_depth) {
    unsigned char * gif_rgb_output = malloc(sizeof(unsigned char) * 3 * x * y * max_depth);
    GifWriter writer;
    GifBegin(&writer, filepath, x, y, 70, 8, false);

    create_gif_helper(tree, gif_rgb_output, x, y, 0, max_depth);

    // Combine each layer of the tree into a GIF
    for (int i = 0; i < max_depth; i++) {
        create_gif_frame(&writer, gif_rgb_output + (3 * x * y * i), x, y);
    }

    GifEnd(&writer);
    free(gif_rgb_output);
}

