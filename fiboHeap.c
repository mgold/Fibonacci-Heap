#include "use.h"
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

elem* heap_add(heap** H, root* newRoot);

elem* heap_insert(heap** H, int key, void* value){
    root* newRoot = root_init(node_init(key, value));
    return heap_add(H, newRoot);
}

elem* heap_add(heap** H, root* newRoot){
    assert(H);
    assert(newRoot);
    root* oldRoot = *H;
    if (oldRoot){
        assert(oldRoot->tree);
        assert(oldRoot->tree->key);
        assert(newRoot->tree);
        assert(newRoot->tree->key);
        if (oldRoot->tree->key > newRoot->tree->key){ //new smallest
            root_add(oldRoot->left, newRoot);
            *H = newRoot;
        }else{ //just another node
            root_add(oldRoot, newRoot);
        }
    }else{ //previously empty tree
        *H = newRoot;
    }
    return newRoot->tree;
}

data  heap_min(heap* H){
    assert(H);
    data d;
    node* head = H->tree;
    d.key = head->key;
    d.value = head->value;
    return d;
}

data  heap_extract_min(heap** H);

heap* heap_union(heap* H1, heap* H2){
    if(!H1) return H2;
    if(!H2) return H1;
    if (heap_min(H2).key < heap_min(H1).key){
        return heap_union(H2, H1);
    }

    root* H1first = H1;
    root* H1last = H1first->left;
    root* H2first = H2;
    root* H2last = H2first->left;

    H1last->right = H2first;
    H2first->left = H1last;
    H2last->right = H1first;
    H1first->left = H2last;

    return H1first;
}

void  heap_decrease_key(heap** H, elem* x, int newKey){
    assert(H && *H);
    assert(x && x->key > newKey);
    node_remove_kid(x);
    x->key = newKey;
    fprintf(stderr, "Assigned key.\n");
    //problem: what if you're already a root?
    heap_add(H, root_init((node*)x));
    fprintf(stderr, "Returing.\n");
}

void  heap_delete(heap** H, elem* x);

data  elem_data(elem* x){
    assert(x);
    data d;
    d.key = x->key;
    d.value = x->value;
    return d;
}

void heap_free(heap** H){
    root* header = *H;
    root* first = header;
    if (header){
        while(header != first){
            root* next = header->right;
            node_kill(header->tree);
            header = next;
        }
    }
}

#endif
