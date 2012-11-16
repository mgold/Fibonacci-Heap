#ifndef HEAP_INCLUDED
#define HEAP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

typedef struct{
    int key;     // Indicates the minimum
    void* value; //Arbitrary client data
} data;

//These functions are follow the same contracts listed on text page 505
//Functions that take a heap** may change that pointer by side effect

heap* heap_init();

//Returns a pointer to the element inserted, for decrease_key and delete
//The pointer to the heap may change as a side effect
elem* heap_insert(heap** H, int key, void* value);

data  heap_min(heap* H);
data  heap_extract_min(heap** H);

heap* heap_union(heap* H1, heap* H2);

void  heap_decrease_key(heap* H, elem* x, int newValue);
void* heap_delete(heap** H, elem* x);

data  elem_data(elem* x);

//Call to avoid leaking memory.
void heap_free(heap** H);
#endif
