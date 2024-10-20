#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h>

typedef struct vector_t {
    void* buffer;
    size_t size;
    size_t allocated_size;
} vector_t;

void vector_init(vector_t* v, size_t init_size);
void vector_free(vector_t* v);
void vector_add(vector_t* v, void* data, size_t data_size);

#endif