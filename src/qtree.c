#include "qtree.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

int qtree_depth_helper(QTreeNode first_child){
    int depth = 1;
    if (NODE(first_child).node_type == INTERNAL_NODE){
        int child_depth = qtree_depth_helper(NODE(first_child).data.first_child);
        depth = max(depth, child_depth+1);
    }
    if (NODE(first_child+1).node_type == INTERNAL_NODE){
        int child_depth = qtree_depth_helper(NODE(first_child+1).data.first_child);
        depth = max(depth, child_depth+1);
    }
    if (NODE(first_child+2).node_type == INTERNAL_NODE){
        int child_depth = qtree_depth_helper(NODE(first_child+2).data.first_child);
        depth = max(depth, child_depth+1);
    }
    if (NODE(first_child+3).node_type == INTERNAL_NODE){
        int child_depth = qtree_depth_helper(NODE(first_child+3).data.first_child);
        depth = max(depth, child_depth+1);
    }
    return depth;
}

int qtree_depth(QTreeNode tree){
    if (NODE(tree).node_type == LEAF_NODE){
        return 0;
    }
    return qtree_depth_helper(NODE(tree).data.first_child);
}

int qtree_n_nodes_helper(QTreeNode first_child){
    int n = 4;
    if (NODE(first_child).node_type == INTERNAL_NODE){
        n += qtree_n_nodes_helper(NODE(first_child).data.first_child);
    }
    if (NODE(first_child + 1).node_type == INTERNAL_NODE){
        n += qtree_n_nodes_helper(NODE(first_child + 1).data.first_child);
    }
    if (NODE(first_child + 2).node_type == INTERNAL_NODE){
        n += qtree_n_nodes_helper(NODE(first_child + 2).data.first_child);
    }
    if (NODE(first_child + 3).node_type == INTERNAL_NODE){
        n += qtree_n_nodes_helper(NODE(first_child + 3).data.first_child);
    }
    return n;
}

int qtree_n_nodes(QTreeNode tree){
    if (tree == NULL){
        return 0;
    } else if (NODE(tree).node_type == LEAF_NODE){
        return 1;
    }
    return 1 + qtree_n_nodes_helper(NODE(tree).data.first_child);
}

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