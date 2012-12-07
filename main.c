#include <stdio.h>
#include "heap.h"

void print_data(data d){
    printf("%d\n", d.key);
}

int main(){
    heap* myheap = heap_init();
    for (int i = 100; i>0; i-=2){
        heap_insert(&myheap, i, NULL);
    }
    elem* mine = heap_insert(&myheap, 77, NULL);
    heap_decrease_key(&myheap, mine, 33);
    mine = heap_insert(&myheap, 67, NULL);
    heap_decrease_key(&myheap, mine, 23);
    mine = heap_insert(&myheap, 43, NULL);
    heap_delete(&myheap, mine);
    while (!is_empty(myheap)){
        print_data(heap_extract_min(&myheap));
    }
    heap_free(&myheap);
    return 0;
}
