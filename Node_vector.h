#ifndef COMPRESSOR_NODE_VECTOR_H
#define COMPRESSOR_NODE_VECTOR_H

#include "Tree_node.h"
#include <stdio.h>

typedef struct Node_vector
{
    Tree_node** nodes;
    int size;
}Node_vector;

Node_vector init_node_vector();
Tree_node* get_node_of_value(Node_vector* vector, unsigned char value);
void remove_zero_nodes(Node_vector*);
void sort_vector(Node_vector*);
void pop_front_node(Node_vector* vector);
void pop_2_front_nodes(Node_vector* vector);
void push_back_node(Node_vector* vector, Tree_node* node);

#endif //COMPRESSOR_NODE_VECTOR_H
