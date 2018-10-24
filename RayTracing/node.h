#ifndef NODE_H
#define NODE_H
#include "boundrect.h"

class Node
{
public:
    BoundRect* value;
    Node *left;
    Node *right;
public:
    Node() {}
    Node(BoundRect *v){
        value=v;
    }
};
#endif // NODE_H
