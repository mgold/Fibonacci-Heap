#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//The representation of the node is exposed to facilitate pointer manipulation.
//However functions on nodes are given for other operations.
typedef struct node node;
struct node{
  int key;
  void* value; //Arbitrary heap client data
  node* parent; // NULL iff this node is a root
  node** kids;
  int kidsLogSize; //Logical  size of kids, i.e first empty index
  int kidsPhySize; //Physical size of kids
  int hasLostKid; //Boolean
};

//The circular array itself consists of these structs
typedef struct root root;
struct root{
    node* tree;
    int height; //In nodes, not edges
    root* left;
    root* right;
};

typedef root heap;
typedef node elem;

//Don't pass any NULL pointers to these functions. Just don't.

node* node_init(int key, void* value);
root* root_init(node* head);

//node_free deallocates the node. Will leak memory and leave dead pointers.
//node_kill recursively kills its children and then frees itself.
void  node_free(node* toFree);
void  node_kill(node* toKill);

void  node_add_kid(node* parent, node* kid);
void  node_remove_kid(node* kidToRemove);
//Removes the rightmost kid of parent and returns it, or NULL if no kids.
node* node_remove_right_kid(node* parent);



//Adds root newRight to the circularly linked list, right of old
void root_add(root* old, root* newRight);

#endif
