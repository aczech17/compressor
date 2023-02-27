#include "compress.h"
#include "Node_vector.h"
#include <stdlib.h>
#include <string.h>

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

static void print_bit_vector(const Bit_vector* vector, char* str)
{
    size_t i;
    for (i = 0; i < vector->size; i++)
    {
        strcat(str, vector->bits[i] == '0' ? "0" : "1"); // it needs a string
    }
    strcat(str, "\n");
}

char* get_codewords(FILE* input)
{
    const size_t header_size = 256 * 8;
    char* header = calloc(header_size, 1);

    Node_vector node_vector = init_node_vector();

    int byte;
    while ((byte = fgetc(input)) != EOF)
    {
        Tree_node* node = get_node_of_value(&node_vector, byte);
        //printf("%c", byte);
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


    if (!huffman_tree->left) // only one character
    {
        sprintf(header, "%02X0\n", huffman_tree->value);
        free_tree(huffman_tree);
        return header;
    }

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
            char header_line[15] = {0}; // byte value (2 characters), codeword (up to 8 characters), endline, '\0'

            sprintf(header_line, "%02X", i); // 2 nibbles
            print_bit_vector(codewords[i], header_line + 2); // then codeword, and then newline
            strcat(header, header_line);
        }
    }

    free_bit_vector(&bit_vector);

    for (i = 0; i < 256; i++)
    {
        free_bit_vector(codewords[i]);
        free(codewords[i]);
    }

    free_tree(huffman_tree);
    return header;
}