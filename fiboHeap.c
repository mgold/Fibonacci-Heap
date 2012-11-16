#include "use.h"
#ifdef  USE_FIBO_HEAP

#include <stdio.h>
#include <assert.h>
#include "heap.h"
#include "node.h"

//for reference
//typedef node heap;
//typedef node elem;

heap* heap_init(){
    return NULL;
}

elem* heap_add(heap** H, node* newNode);

elem* heap_insert(heap** H, int key, void* value){
    node* newNode = node_init(key, value);
    return heap_add(H, newNode);
}

elem* heap_add(heap** H, node* newNode){
    assert(H);
    assert(newNode);
    node* oldNode = *H;
    newNode->parent = NULL;
    if (oldNode){
        if (oldNode->key > newNode->key){ //new smallest
            node_add(oldNode->left, newNode);
            *H = newNode;
        }else{ //just another node
            node_add(oldNode, newNode);
        }
    }else{ //previously empty heap
        *H = newNode;
    }
    return newNode;
}

data  heap_min(heap* H){
    assert(H);
    data d;
    node* head = H;
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

    node* H1first = H1;
    node* H1last = H1first->left;
    node* H2first = H2;
    node* H2last = H2first->left;

    H1last->right = H2first;
    H2first->left = H1last;
    H2last->right = H1first;
    H1first->left = H2last;

    return H1first;
}

void  heap_decrease_key(heap** H, elem* x, int newKey){
    assert(H && *H);
    assert(x && x->key >= newKey);
    x->key = newKey;
    if(*H != x){ //don't touch the root
        node* x2 = NULL;
        if(x->parent){//in a tree
            x2 = node_remove_kid(x);
        }else{//on the ring
            assert(x->left && x->right);
            assert(x->left != x && x->right != x);
            x->left->right = x->right;
            x->right->left = x->left;
        }
        heap_add(H, x);
        if (x2){
            heap_decrease_key(H, x2, x2->key);
        }
    }
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
    node* header = *H;
    node* first = header;
    if (header){
        while(header != first){
            node* next = header->right;
            node_kill(header);
            header = next;
        }
    }
}

#endif
