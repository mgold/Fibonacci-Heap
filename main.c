#include <stdio.h>
#include "heap.h"

int main(){
    heap* myheap = heap_init();
    elem* seven = heap_insert(&myheap, 7, NULL);
    heap_insert(&myheap, 3, NULL);
    heap_decrease_key(&myheap, seven, 2);
    data d = heap_min(myheap);
    heap_free(&myheap);
    return d.key;
}
