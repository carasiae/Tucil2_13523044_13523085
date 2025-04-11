#ifndef MGIF_H
#define MGIF_H
#include "qtree.h"
#include "qtree.h"

/** create a gif showing the process of compression based on a quadtree
    @param tree                 current node of quadtree (representing a part
                                of image) processed 
    @param filepath             path to GIF file
                                format as in stb_image library
    @param x                    width of the image in pixels
    @param y                    height of the image in pixels
    @param max_depth            max depth of the given tree
*/
void create_gif(QTreeNode tree, char * filepath, int x, int y, int max_depth);

#endif