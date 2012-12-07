#include "node.h"

node* node_init(int key, void* value){
    node* newNode = malloc(sizeof(node));
    newNode->left = newNode->right = newNode;
    newNode->key = key;
    newNode->value = value;
    newNode->parent = NULL;
    newNode->kid = NULL;
    newNode->hasLostKid = 0;
    newNode->degree = 0;
    return newNode;
}

void node_free(node* toFree){
    toFree->degree = -1;
    free(toFree);
}

void node_kill(node* toKill){
    node* kid = toKill->kid;
    if (kid){
        kid->left->right = NULL;
        while(kid->right != NULL){
            kid = kid->right;
            node_kill(kid->left);
        }
        node_kill(kid);
    }
    node_free(toKill);
}

void node_add(node* old, node* newRight){
    assert(old != newRight);
    node* oldRight = old->right;
    assert((oldRight->right != oldRight) || (old == oldRight));
    old->right = newRight;
    oldRight->left = newRight;
    newRight->left = old;
    newRight->right = oldRight;
    assert(oldRight->right != oldRight);
    assert(newRight->right != newRight);
    assert(old->right != old);
}
