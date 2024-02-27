//node.cpp
#include "node.h"
#include <iostream>
#include <cstring>


using namespace std;

node::node(int tdata) {
  data = tdata;
  left = NULL;
  right = NULL;
}

node::~node() {
  // is storing an int so should do nothing?

  // should i delete the left and right pointers or no??
  
}

void node::setLeft(node* tleft) {
  left = tleft;
}

node* node::getLeft() {
  return left;
}

void node::setRight(node* tright) {
  right = tright;
}

node* node::getRight() {
  return right;
}

int node::getValue() {
  return data;
}

void node::setValue(int tdata) {
  data = tdata;
}
