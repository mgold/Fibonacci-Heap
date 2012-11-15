#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    root* left;
    root* right;
};

//Don't pass any NULL pointers to these functions. Just don't.

node* node_init(int key, void* value);

//node_free deallocates the node. Will leak memory and leave dead pointers.
//node_kill recursively kills its children and then frees itself.
void  node_free(node* toFree);
void  node_kill(node* toKill);

void  node_addKid(node* parent, node* kid);
//Removes the rightmost kid of parent and returns it, or NULL if no kids.
node* node_removeKid(node* parent);

//Adds root newRight to the circularly linked list, right of old
void root_add(root* old, root* newRight);

#endif
