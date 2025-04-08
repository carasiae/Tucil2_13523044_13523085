#include "qtree.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

QTreeNode qtree_new(int width, int height) {
    QTreeNode res = malloc(sizeof(struct _QTreeNode));
    res->width = width;
    res->height = height;
    res->row = res->col = 0;
    res->node_type = LEAF_NODE;
    res->data.rgb.r = res->data.rgb.g = res->data.rgb.b = 0;
    return res;
}

QTreeNode qtree_subdivide(QTreeNode node) {
    QTreeNode next = malloc(sizeof(struct _QTreeNode) * 4);
    node->node_type = INTERNAL_NODE;
    node->data.first_child = next;

    NODE(next).node_type = LEAF_NODE;
    NODE(next).row = NODE(node).row;
    NODE(next).col = NODE(node).col;
    NODE(next).width = NODE(node).width / 2;
    NODE(next).height = NODE(node).height / 2;

    NODE(next+1).node_type = LEAF_NODE;
    NODE(next+1).row = NODE(node).row;
    NODE(next+1).col = NODE(node).col + NODE(node).width / 2;
    NODE(next+1).width = (NODE(node).width+1) / 2;
    NODE(next+1).height = NODE(node).height / 2;

    NODE(next+2).node_type = LEAF_NODE;
    NODE(next+2).row = NODE(node).row + NODE(node).height / 2;
    NODE(next+2).col = NODE(node).col;
    NODE(next+2).width = NODE(node).width / 2;
    NODE(next+2).height = (NODE(node).height+1) / 2;

    NODE(next+3).node_type = LEAF_NODE;
    NODE(next+3).row = NODE(node).row + NODE(node).height / 2;
    NODE(next+3).col = NODE(node).col + NODE(node).width / 2;
    NODE(next+3).width = (NODE(node).width+1) / 2;
    NODE(next+3).height = (NODE(node).height+1) / 2;
    return next;
}

void destroy_children(QTreeNode first_child){
    for (int i = 0; i < 4; i++){
        if (NODE(first_child+i).node_type == INTERNAL_NODE){
            destroy_children(NODE(first_child+i).data.first_child);
        }
    }
    free(first_child);
}
void qtree_destroy(QTreeNode qtree){
    if(qtree->node_type == INTERNAL_NODE){
        QTreeNode next = qtree->data.first_child;
        destroy_children(next);
    }
    free(qtree);
}