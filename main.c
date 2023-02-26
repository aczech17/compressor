#include <stdio.h>
#include <stdlib.h>
#include "Node_vector.h"
#include "Bit_vector.h"

void print_nodes(Node_vector node_vector) // DEBUG
{
    int i;
    for (i = 0; i < node_vector.size; i++)
    {
        printf("%c %d\n", node_vector.nodes[i]->value, node_vector.nodes[i]->frequency);
    }
}


void print_bit_vector(const Bit_vector* vector)
{
    size_t i;
    for (i = 0; i < vector->size; i++)
        printf("%c", vector->bits[i]);
    printf("\n");
}

void traverse(Tree_node* node, Bit_vector* bit_vector, Bit_vector** codewords)
{
    if (node->left)
    {
        push_bit(bit_vector, '0');
        traverse(node->left, bit_vector, codewords);
        pop_bit(bit_vector);
    }

    if (node->right)
    {
        push_bit(bit_vector, '1');
        traverse(node->right, bit_vector, codewords);
        pop_bit(bit_vector);
    }

    if (node->has_value)
    {
        codewords[node->value] = copy_bit_vector(bit_vector);
    }
}


int main(int argc, char** argv)
{
    FILE* input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        fprintf(stderr, "Nie udalo sie otworzyc.\n");
        return 1;
    }

    Node_vector node_vector = init_node_vector();

    int byte;
    while ((byte = fgetc(input)) != EOF)
    {
        Tree_node* node = get_node_of_value(&node_vector, byte);
        node->frequency++;
    }
    fclose(input);

    remove_zero_nodes(&node_vector);

    while (node_vector.size > 1)
    {

        Tree_node* left = node_vector.nodes[0];
        Tree_node* right = node_vector.nodes[1];

        Tree_node* new_node = merge_nodes(left, right);

        pop_2_front_nodes(&node_vector);
        push_back_node(&node_vector, new_node);

        sort_vector(&node_vector);
    }
    Tree_node* huffman_tree = node_vector.nodes[0];

    pop_front_node(&node_vector);
    free(node_vector.nodes);


    Bit_vector* codewords[256];
    int i;
    for (i = 0; i < 256; i++)
        codewords[i] = NULL;

    Bit_vector bit_vector = init_bit_vector();

    traverse(huffman_tree, &bit_vector, codewords);

    for (i = 0; i < 256; i++)
    {
        if (codewords[i] != NULL)
        {
            printf("%c ", i);
            print_bit_vector(codewords[i]);
        }
    }

    free_bit_vector(&bit_vector);

    for (i = 0; i < 256; i++)
    {
        free_bit_vector(codewords[i]);
        free(codewords[i]);
    }

    free_tree(huffman_tree);

    return 0;
}
