#define USE_FIBO_HEAP
#ifdef  USE_FIBO_HEAP

#include <stdio.h>
#include <assert.h>
#include "heap.h"
#include "node.h"

//for reference
//typedef root heap;
//typedef node elem;

heap* heap_init(){
    return NULL;
}

elem* heap_insert(heap** H, int key, void* value){
    root* newRoot = root_init(key, value);
    root* oldRoot = (root*) *H;
    if (oldRoot){
        if (oldRoot->tree->key > key){
            root_add(oldRoot->left, newRoot);
            *H = newRoot;
        }else{
            root_add(oldRoot, newRoot);
        }
    }else{
        *H = newRoot;
    }
    return newRoot->tree;
}

data  heap_min(heap* H){
    assert(H);
    data d;
    node* head = ((root*) H)->tree;
    d.key = head->key;
    d.value = head->value;
    return d;
}

data  heap_extract_min(heap** H);

heap* heap_union(heap* H1, heap* H2);

void  heap_decrease_key(heap* H, elem* x, int newValue);
void* heap_delete(heap** H, elem* x);

data  elem_data(elem* x);

void heap_free(heap** H);

#endif
