#include "vector.h"

#include <stdlib.h>
#include <string.h>

void vector_init(vector_t* v, size_t init_size){
    v->buffer = malloc(init_size);
    v->allocated_size = init_size;
    v->size = 0;
}

void vector_free(vector_t* v){
    if(v->buffer)
        free(v->buffer);
}

void vector_add(vector_t* v, void* data, size_t data_size){
    while(v->size + data_size > v->allocated_size){
        v->buffer = realloc(v->buffer, v->allocated_size*2);
        v->allocated_size *= 2;
    }
    memcpy(v->buffer + v->size, data, data_size);
    v->size += data_size;
}