#include <stdio.h>
#include "Node_vector.h"
#include "compress.h"
#include <stdlib.h>

void print_nodes(Node_vector node_vector) // DEBUG
{
    int i;
    for (i = 0; i < node_vector.size; i++)
    {
        printf("%c %d\n", node_vector.nodes[i]->value, node_vector.nodes[i]->frequency);
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

    char* header = get_codewords(input);

    printf("%s\n", header);
    free(header);

    fclose(input);
    return 0;
}
