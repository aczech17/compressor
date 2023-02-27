#include <stdio.h>
#include "Node_vector.h"
#include "compress.h"
#include <stdlib.h>
#include <string.h>
#include "Bit_vector.h"

void print_nodes(Node_vector node_vector) // DEBUG
{
    int i;
    for (i = 0; i < node_vector.size; i++)
    {
        printf("%c %d\n", node_vector.nodes[i]->value, node_vector.nodes[i]->frequency);
    }
}

static void bits_to_string(const Bit_vector** codewords)
{
    int i;
    for (i = 0; i < 256; i++)
    {
        if (codewords[i] != NULL)
        {
            printf("%02X", i);
            size_t j;
            for (j = 0; j < codewords[i]->size; j++)
            {
                printf("%c", codewords[i]->bits[j]);
            }
            printf("\n");
        }
    }
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "input output\n");
        return 1;
    }

    FILE* input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        fprintf(stderr, "Nie udalo sie otworzyc.\n");
        return 1;
    }

    Bit_vector** codewords = get_codewords(input);

    bits_to_string((const Bit_vector **) codewords);


    int i;
    for (i = 0; i < 256; i++)
    {

        free_bit_vector(codewords[i]);
        free(codewords[i]);
    }
    free(codewords);

    fclose(input);
    return 0;
}
