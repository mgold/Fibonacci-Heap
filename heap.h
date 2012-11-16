#ifndef HEAP_INCLUDED
#define HEAP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "use.h"
#ifdef  USE_FIBO_HEAP
#include "node.h"
#endif

typedef struct{
    int key;     // Indicates the minimum
    void* value; //Arbitrary client data
} data;

//These functions are follow the same contracts listed on text page 505
//Functions that take a heap** may change that pointer by side effect

heap* heap_init();

//Returns a pointer to the element inserted, for decrease_key and delete
elem* heap_insert(heap** H, int key, void* value);

data  heap_min(heap* H);
data  heap_extract_min(heap** H);

heap* heap_union(heap* H1, heap* H2);

//elem x must be in heap H
//newKey must be less than elem's old key
void  heap_decrease_key(heap** H, elem* x, int newKey);
void  heap_delete(heap** H, elem* x);

data  elem_data(elem* x);
void  elem_set_value(elem* x, void* newValue);

//Call to avoid leaking memory.
void heap_free(heap** H);
#endif
