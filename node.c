#include "node.h"

const int DEFAULT_KIDS_LEN = 8;
const int KIDS_RESIZE_FACTOR = 2;

node* node_init(int key, void* value){
    node* newNode = malloc(sizeof(node));
    newNode->left = newNode->right = newNode;
    newNode->key = key;
    newNode->value = value;
    newNode->parent = NULL;
    newNode->kids = calloc(DEFAULT_KIDS_LEN, sizeof(node*));
    newNode->kidsLogSize = 0;
    newNode->kidsPhySize = DEFAULT_KIDS_LEN;
    newNode->hasLostKid = 0;
    return newNode;
}

void node_free(node* toFree){
    free(toFree->kids);
    free(toFree);
}

void node_kill(node* toKill){
    for (int i=0; i < toKill->kidsLogSize; i++){
        node_free(toKill->kids[i]);
    }
    node_free(toKill);
}

void node_add_kid(node* parent, node* kid){
    if (parent->kidsPhySize == parent->kidsLogSize){
        node** newKids = calloc(KIDS_RESIZE_FACTOR*parent->kidsPhySize,
                                sizeof(node*));
        memcpy(newKids, parent->kids, parent->kidsLogSize*sizeof(node*));
        free(parent->kids);
        parent->kids = newKids;
        parent->kidsPhySize *= KIDS_RESIZE_FACTOR;
    }
    parent->kids[parent->kidsLogSize] = kid;
    parent->kidsLogSize++;
}

node* node_remove_kid(node* kidToRemove){
    assert(kidToRemove);
    node* parent = kidToRemove->parent;
    assert(parent);
    int slide = 0;
    for (int i = 0; i < parent->kidsLogSize; i++){
        if (parent->kids[i] == kidToRemove) slide = 1;
        if(slide && i < parent->kidsLogSize -1){
            parent->kids[i] = parent->kids[i+1];
        }
    }
    assert(slide);
    parent->kidsLogSize--;
    parent->kids[parent->kidsLogSize] = NULL;
    if (parent->hasLostKid){
        parent->hasLostKid = 0;
        return parent;
    }else{
        parent->hasLostKid = 1;
    }
    return NULL;
}

node* node_remove_right_kid(node* parent){
    node* kid = NULL;
    if (parent->kidsLogSize){
        kid = parent->kids[parent->kidsLogSize-1];
        parent->kids[parent->kidsLogSize-1] = NULL;
        parent->kidsLogSize--;
    }
    return kid;
}

void node_add(node* old, node* newRight){
    node* oldRight = old->right;
    old->right = newRight;
    oldRight->left = newRight;
    newRight->left = old;
    newRight->right = oldRight;
}
