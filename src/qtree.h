#ifndef QUAD_TREE_H
#define QUAD_TREE_H
#include <stdint.h>
#include <stdlib.h>

/** RGB struct for storing rgb value */
typedef struct _RGB {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

#define LEAF_NODE 0
#define INTERNAL_NODE 1

/** QuadTreeNode struct
    a quadtree node is either an internal node, which contains indexes to other
    nodes or a leaf node which contains graphics related information.
*/
typedef struct _QTreeNode{
    /** node's row */
    int row;
    /** node's column */
    int col;
    /** node's width */
    int width;
    /** node's height */
    int height;
    /** content of the quadtree */
    union _data {
        /** Internal node's first child */
        struct _QTreeNode *first_child;
        /** leaf node's RGB value */
        RGB rgb;
    } data;
    /** type of the quadtree, its' value is either INTERNAL_NODE or LEAF_NODE */
    char node_type;
} *QTreeNode;

#define NODE(p) (*(p))

/** Creates a new quad tree
    @param  width   width of the image which the tree correlates to.
    @param  height  height of the image which the tree correlates to.
    @return a new quatree if the creation is successfull,
            NULL otherwise.
*/
QTreeNode qtree_new(int width, int height);

/** Subdivide a leaf node.
    Turn a leaf node into an internal node and allocate four of its children.
    @return the index of the first child of the original node if successful,
            -1 otherwise.
*/
QTreeNode qtree_subdivide(QTreeNode node_idx);

/** Deallocate a quad tree
    @param  quad_tree   pointer to a QTree to be destroyed.
*/
void qtree_destroy(QTreeNode qtree);

/** Compute depth of a tree
    @param  tree   the root node of the tree.
    @return the depth of the tree.
*/
int qtree_depth(QTreeNode tree);

/** Compute the total number of nodes of a tree
    @param  tree   the root node of the tree.
    @return the total number of nodes of the tree.
*/
int qtree_n_nodes(QTreeNode tree);
#endif