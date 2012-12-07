#include "use.h"
#ifdef  USE_FIBO_HEAP

#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include "heap.h"
#include "node.h"

heap* heap_init(){
    return NULL;
}

elem* heap_add(heap** H, node* newNode);

elem* heap_insert(heap** H, int key, void* value){
    node* newNode = node_init(key, value);
    return heap_add(H, newNode);
}

int is_empty(heap* H){
    return H == NULL;
}

elem* heap_add(heap** H, node* newNode){
    assert(H);
    assert(newNode);
    node* oldNode = *H;
    newNode->parent = NULL;
    newNode->hasLostKid = 0;
    if (oldNode){ //nonempty heap
        node_add(oldNode, newNode);
        if (oldNode->key > newNode->key){ //new smallest
            *H = newNode;
        }
    }else{ //previously empty heap
        newNode->left = newNode;
        newNode->right = newNode;
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

void  heap_consolidate(heap** H);
void  heap_match_degrees(heap** H, node** A, node* x);
node* heap_link(heap** H, node* x, node* y);
void  heap_remove_from(heap** H, node* x);

data  heap_extract_min(heap** H){
    assert(H && *H);
    node* z = *H;
    data d = elem_data(z);
    node* first = z->kid;
    heap_remove_from(H, z);
    node_free(z);
    if (first){
        node* current = first->right;
        while (current != first){
            current->parent = NULL;
            current = current->right;
        }
        first->parent = NULL;
        *H = heap_union(*H, first);
    }
    heap_consolidate(H);
    return d;
}

void  heap_remove_from(heap** H, node* x){
    assert(!x->parent);
    if (x->right == x){
        *H = NULL;
    }else{
        x->left->right = x->right;
        x->right->left = x->left;
        *H = x->right;
    }
    x->left = x;
    x->right = x;
    x->parent = NULL;
}
void  heap_consolidate(heap** H){
    node* x = *H;
    if (!x) return;
    node** A = calloc(100, sizeof(node));
    memset(A, '\0', 100);
    assert(x->degree >= 0);
    node* last = x->left;
    while(x != last){
        node* next = x->right;
        heap_match_degrees(H, A, x);
        x = next;
    }
    heap_match_degrees(H, A, last);
    *H = heap_init();
    for (int i=0; i<100; i++){
        if (A[i]){
            heap_add(H, A[i]);
        }
    }
    free(A);
}

void heap_match_degrees(heap** H, node** A, node* x){
    int d = x->degree;
    while(A[d]){
        if (d > 99){
            exit(1);
        }
        node* y = A[d];
        if (y != x){
            x = heap_link(H, x, y);
            A[d] = NULL;
            d++;
        }else{
            break;
        }
    }
    A[d] = x;
}
node* heap_link(heap** H, node* x, node* y){
    assert(x);
    assert(y);
    assert(x->degree == y->degree);
    if (x->key > y->key){
        return heap_link(H, y, x);
    }
    heap_remove_from(H, y);
    if (x->kid){
        node* z = x->kid;
        y->right = z;
        y->left = z->left;
        z->left->right = y;
        z->left = y;
    }
    y->parent = x;
    x->kid = y;
    x->degree++;
    y->hasLostKid = 0;
    return x;
}

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
    if(x->parent && x->parent->key > newKey){
        if (x->left == x){
            assert(x->parent->degree == 2);
            x->parent->kid = NULL;
        }else{
            assert(x->parent->degree > 2);
            x->left->right = x->right;
            x->right->left = x->left;
            x->parent->kid = x->left;
        }
        x->parent->degree--;
        heap_add(H, x);
        if (! x->parent->hasLostKid){
            x->parent->hasLostKid = 1;
        }else{
            heap_decrease_key(H, x->parent, x->parent->key);
        }

    }else{
        if (newKey < (*H)->key){
            assert(!x->parent);
            *H = x;
        }
    }
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

void heap_print(heap* H){
    if (H){
        node* first = H;
        fprintf(stderr, "%d[%d](", first->key, first->degree);
        if(first->kid) heap_print(first->kid);
        fprintf(stderr, ")");
        node* current = first->right;
        while (first != current){
            fprintf(stderr, "%d[%d](", current->key, current->degree);
            if(current->kid) heap_print(current->kid);
            fprintf(stderr, ")");
            current = current->right;
        }
    }
    fprintf(stderr, "\n");
}

#endif
