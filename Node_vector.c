#include <stdlib.h>
#include "Node_vector.h"


static int compare_nodes(const void* a, const void* b)
{
    Tree_node* node1 = *((Tree_node**)a);
    Tree_node* node2 = *((Tree_node**)b);

    if (node1 == NULL)
        return 1;
    if (node2 == NULL)
        return -1;

    if (node1->frequency < node2->frequency)
        return -1;
    if (node1->frequency > node2->frequency)
        return 1;
    return 0;
}

Node_vector init_node_vector()
{
    Node_vector vector;
    vector.nodes = malloc(256 * sizeof(Tree_node*));

    int i;
    for (i = 0; i < 256; i++)
    {
        vector.nodes[i] = new_tree_node(true, i, 0);
    }

    vector.size = 256;
    return vector;
}

Tree_node* get_node_of_value(Node_vector* vector, unsigned char value)
{
    int i;
    for (i = 0; i < vector->size; i++)
    {
        if (vector->nodes[i]->value == value)
            return vector->nodes[i];
    }
    return NULL;
}

void remove_zero_nodes(Node_vector* vector)
{
    int i;
    for (i = 0; i < 256; i++)
    {
        if (vector->nodes[i]->frequency == 0)
        {
            free(vector->nodes[i]);
            vector->nodes[i] = NULL;
            vector->size--;
        }
    }
    sort_vector(vector);
}

void sort_vector(Node_vector* vector)
{
    qsort(vector->nodes, 256, sizeof(Tree_node*), compare_nodes);
}


void pop_front_node(Node_vector* vector)
{
    vector->nodes[0] = vector->nodes[vector->size - 1];
    vector->nodes[vector->size - 1] = NULL;

    vector->size--;
}

void pop_2_front_nodes(Node_vector* vector)
{
    vector->nodes[0] = vector->nodes[vector->size - 1];
    vector->nodes[1] = vector->nodes[vector->size - 2];

    vector->nodes[vector->size - 1] = NULL;
    vector->nodes[vector->size - 2] = NULL;

    vector->size -= 2;
}

void push_back_node(Node_vector* vector, Tree_node* node)
{
    vector->nodes[vector->size++] = node;
}

