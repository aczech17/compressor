#include "compress.h"
#include "Node_vector.h"
#include <stdlib.h>

static void traverse(Tree_node* node, Bit_vector* bit_vector, Bit_vector** codewords)
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

static bool file_is_empty(FILE* input)
{
    fseek(input, 0, SEEK_END); // seek to end of file
    size_t size = ftell(input); // get current file pointer
    fseek(input, 0, SEEK_SET); // seek back to beginning of file

    return size == 0;
}

Bit_vector** get_codewords(FILE* input)
{
    if (file_is_empty(input))
        return NULL;

    Node_vector node_vector = init_node_vector();

    int byte;
    while ((byte = fgetc(input)) != EOF)
    {
        Tree_node* node = get_node_of_value(&node_vector, byte);
        node->frequency++;
    }

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

    Bit_vector** codewords = malloc(256 * sizeof(Bit_vector*));
    int i;
    for (i = 0; i < 256; i++)
        codewords[i] = NULL;

    Bit_vector* bit_vector = init_bit_vector();
    if (!huffman_tree->left) // only one character
    {
        push_bit(bit_vector, '0');
        codewords[huffman_tree->value] = bit_vector;

        free_tree(huffman_tree);
        return codewords;
    }

    traverse(huffman_tree, bit_vector, codewords);


    free_bit_vector(bit_vector);
    free(bit_vector);
    free_tree(huffman_tree);
    return codewords;
}
