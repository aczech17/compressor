#ifndef COMPRESSOR_TREE_NODE_H
#define COMPRESSOR_TREE_NODE_H

#include <stdbool.h>

typedef struct Tree_node
{
    bool has_value;
    unsigned char value;
    unsigned frequency;
    struct Tree_node* left;
    struct Tree_node* right;
}Tree_node;

Tree_node* new_tree_node(bool has_value, unsigned char value, unsigned frequency);
Tree_node* merge_nodes(const Tree_node* left, const Tree_node* right);
void free_tree(Tree_node* root);

#endif //COMPRESSOR_TREE_NODE_H
