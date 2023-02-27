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

static char* bits_to_string(char value, const Bit_vector* bit_vector)
{
    size_t string_size = 2 + bit_vector->size + 10;
    char* string = calloc(string_size, 1);
    sprintf(string, "%02X", value);
    size_t i;
    for (i = 0; i < bit_vector->size; i++)
    {
        strcat(string, bit_vector->bits[i] == '0' ? "0" : "1"); // it needs a string
    }
    strcat(string, "\n");
    return string;
}

char* get_codewords(FILE* input)
{
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
        char* result = calloc(5, 1);
        sprintf(result, "%02X0\n", huffman_tree->value);
        free_tree(huffman_tree);
        return result;
    }

    Bit_vector* codewords[256];
    int i;
    for (i = 0; i < 256; i++)
        codewords[i] = NULL;

    Bit_vector bit_vector = init_bit_vector();

    traverse(huffman_tree, &bit_vector, codewords);

    const size_t header_size = 256 * 100; // ???
    char* header = calloc(header_size, 1);

    for (i = 0; i < 256; i++)
    {
        if (codewords[i] != NULL)
        {
            char* header_line = bits_to_string((char)i, codewords[i]);
            strcat(header, header_line);
            free(header_line);
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
