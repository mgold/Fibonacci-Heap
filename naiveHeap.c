#include "use.h"
#ifndef USE_FIBO_HEAP
#include "heap.h"
#include <assert.h>
#include <limits.h>

const int INITIAL_SIZE = 16;
const int RESIZE_FACTOR = 2;

heap* heap_init(){
    heap* H = malloc(sizeof(array));
    H->phySize = INITIAL_SIZE;
    H->logSize = 0;
    H->A = calloc(INITIAL_SIZE, sizeof(elem*));
    return H;
}

void  heap_resize(heap** H);

elem* heap_insert(heap** H, int key, void* value){
    assert(H && *H);
    heap* arr = *H;
    if (arr->phySize == arr->logSize){
        heap_resize(H);
    }
    data* d = malloc(sizeof(data));
    d->key = key;
    d->value = value;
    arr->A[arr->logSize] = d;
    arr->logSize++;
    return d;
}

void  heap_resize(heap** H){
    assert(H && *H);
    heap* arr = *H;
    elem** A2 = calloc(arr->phySize*RESIZE_FACTOR, sizeof(elem*));
    memcpy(A2, arr->A, arr->phySize*sizeof(elem*));
    arr->phySize *= RESIZE_FACTOR;
    free(arr->A);
    arr->A = A2;
}

int is_empty(heap* H){
    return !H->logSize;
}

data  heap_min(heap* H){
    assert(H);
    data d;
    d.key = INT_MAX;
    d.value = NULL;
    for (int i = 0; i < H->logSize; i++){
        elem* current = H->A[i];
        if (current->key < d.key){
            d.key = current->key;
            d.value = current->value;
        }
    }
    return d;
}

data  heap_extract_min(heap** H){
    assert(H && *H);
    heap* arr = *H;
    elem** A = arr->A;
    int j = -1;
    data d;
    d.key = INT_MAX;
    d.value = NULL;
    for (int i = 0; i < arr->logSize; i++){
        elem* current = A[i];
        if (current->key < d.key){
            d.key = current->key;
            d.value = current->value;
            j = i;
        }
    }
    for (int i = j; i < arr->logSize; i++){
        A[i] = A[i+1];
    }
    arr->logSize--;
    return d;
}

heap* heap_union(heap* H1, heap* H2){
    elem** A = H2->A;
    for (int i = 0; i < H2->logSize; i++){
        elem* current = A[i];
        heap_insert(&H1, current->key, current->value);
    }
    return H1;
}

void  heap_decrease_key(heap** H, elem* x, int newKey){
    (void) H;
    assert(x && newKey <= x->key);
    x->key = newKey;
}

void  heap_delete(heap** H, elem* x){
    heap_decrease_key(H, x, INT_MIN);
    heap_extract_min(H);
}

data  elem_data(elem* x){
    assert(x);
    data d;
    d.key = x->key;
    d.value = x->value;
    return d;
}

void heap_free(heap** H){
    assert(H && *H);
    for (int i = 0; i < (*H)->logSize; i++){
        free((*H)->A[i]);
    }
    free((*H)->A);
    free(*H);
    *H = NULL;

}

#else
int dummy = 1;
#endif
