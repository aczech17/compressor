#ifndef COMPRESSOR_BIT_VECTOR_H
#define COMPRESSOR_BIT_VECTOR_H

#include <stdio.h> // size_t

typedef struct Bit_vector
{
    char* bits;
    size_t size;
    size_t capacity;
}Bit_vector;

Bit_vector init_bit_vector();
void free_bit_vector(Bit_vector*);
void push_bit(Bit_vector*, char bit);
void pop_bit(Bit_vector*);
Bit_vector* copy_bit_vector(const Bit_vector*);

#endif //COMPRESSOR_BIT_VECTOR_H
