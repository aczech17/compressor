#include "Tree_node.h"
#include <stdlib.h>

#include <stdio.h> // DEBUG

Tree_node* new_tree_node(bool has_value, unsigned char value, unsigned frequency)
{
    Tree_node* new_node = malloc(sizeof(Tree_node));
    if (new_node == NULL)
    {
        printf("Malloc sie zesral\n");
        exit(2137);
    }
    new_node->has_value = has_value;
    new_node->value = value;
    new_node->frequency = frequency;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

Tree_node* merge_nodes(const Tree_node* left, const Tree_node* right)
{
    Tree_node* new_node = new_tree_node(false, 0, left->frequency + right->frequency);
    new_node->left = (Tree_node*) left; // casting because const qualifier warning
    new_node->right = (Tree_node*) right;

    return new_node;
}

void free_tree(Tree_node* root)
{
    if (root->left != NULL)
    {
        free_tree(root->left);
        free_tree(root->right);
    }
    free(root);
}
