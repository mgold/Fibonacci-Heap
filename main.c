#include <stdio.h>
#include "heap.h"

void print_data(data d){
    printf("%d\n", d.key);
}

int main(){
    heap* myheap = heap_init();
    heap_insert(&myheap, 3, NULL);
    heap_insert(&myheap, 8, NULL);
    heap_insert(&myheap, 2, NULL);
    heap_insert(&myheap, 6, NULL);
    heap_insert(&myheap, 1, NULL);
    heap_insert(&myheap, 9, NULL);
    heap_print(myheap);
    while (!is_empty(myheap)){
        print_data(heap_extract_min(&myheap));
    }
    heap_free(&myheap);
    return 0;
}
