#ifndef NODE_H
#define NODE_H

// node.h

#include <iostream>
#include <cstring>

using namespace std;

class node {
 public:
  node(int tdata);
  ~node();

  void setLeft(node* tleft);
  node* getLeft();

  void setRight(node* tright);
  node* getRight();

  int getValue();
  void setValue(int tdata);
  
 private:
  int data;
  node* right;
  node* left;

} ;

#endif
