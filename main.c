#include <stdio.h>
#include "heap.h"

int main(){
    printf("flag1");
    heap* myheap = heap_init();
    heap_insert(&myheap, 3, NULL);
    data d = heap_min(myheap);
    return d.key;
}
