#include "Bit_vector.h"
#include <stdlib.h>

Bit_vector init_bit_vector()
{
    Bit_vector vector;
    vector.capacity = 10;
    vector.size = 0;
    vector.bits = malloc(vector.capacity * sizeof(*vector.bits));
    return vector;
}

void free_bit_vector(Bit_vector* vector)
{
    if (vector == NULL)
        return;
    free(vector->bits);
}

void reverse_bit_vector(Bit_vector* vector)
{
    size_t i;
    for (i = 0; 2 * i < vector->size; i++)
    {
        char tmp = vector->bits[i];
        vector->bits[i] = vector->bits[vector->size - 1 - i];
        vector->bits[vector->size - 1 - i] = tmp;
    }
}

void push_bit(Bit_vector* vector, char bit)
{
    if (vector->size + 1 > vector->capacity)
    {
        size_t new_capacity = vector->capacity * 2;
        vector->bits = realloc(vector->bits, new_capacity);
        vector->capacity = new_capacity;
    }
    vector->bits[vector->size++] = bit;
}

void pop_bit(Bit_vector* vector)
{
    vector->size--;
}

Bit_vector* copy_bit_vector(const Bit_vector* vector)
{
    Bit_vector* new_vector = malloc(sizeof(Bit_vector));

    new_vector->capacity = vector->capacity;
    new_vector->size = vector->size;
    new_vector->bits = malloc(vector->size * sizeof(*vector->bits));

    size_t i;
    for (i = 0; i < new_vector->size; i++)
        new_vector->bits[i] = vector->bits[i];

    return new_vector;
}
