#ifndef COMPRESSOR_COMPRESS_H
#define COMPRESSOR_COMPRESS_H

#include "Tree_node.h"
#include "Bit_vector.h"

void traverse(Tree_node* node, Bit_vector* bit_vector, Bit_vector** codewords);
char* get_codewords(FILE* input);

#endif //COMPRESSOR_COMPRESS_H
