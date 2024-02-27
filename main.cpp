// main.cpp
#include <cstring>
#include <iostream>
#include "node.h"
#include <fstream>
using namespace std;


/*
to do list:
DONE: create node.cpp adn node.h plus all the functions required
create thing to read in from file/ manual
create all of the functions
adn then do it all :(



atm need to do: line 50ish (reading in a file)---------------
 */
bool SEARCH(node* root, int toSearch);
node* ADD(node* &root, int data);
void PRINT(node* root, int count);
void REMOVE(node* & root, node* current, node* parent, int toRemove);

int main() {

  int quit = 0;

  node* root  = NULL; //creating root and setting to null.


  
  while(quit==0) {
    cout << "Options are: ADD   REMOVE   SEARCH   PRINT  QUIT" << endl;
    char input[50];

    cin>> input;

    if (strcmp(input, "ADD")==0) {
      // check if they want to add via file or console:

      cout << "Options are: FILE   MANUAL" << endl;

      char inputdos[10];
      cin >> inputdos;

      if (strcmp(inputdos, "FILE")==0) {
	// wants to add in by file

	cout << "What's the name of the file to open? Include the .txt at the end :)" << endl;

	char fileName[30];
	cin >> fileName;

	ifstream fin;
	fin.open(fileName);
	int input;
	cout << "reached here" << endl;
	while(fin>>input) {
	  cout <<"input is: " << input << endl;
	  ADD(root, input);
	}


	
      }
      else if (strcmp(inputdos, "MANUAL")==0) {
	// wants to add numbers manually
	int n;
	cout << "what number would u like to add: " ;
	cin >> n;
	ADD(root, n);
      }
    }

    else if (strcmp(input, "REMOVE")==0) {
      // wants to remove
      int toRemove;
      cout << "What number do you want to remove?: ";
      cin >> toRemove;
      REMOVE(root, root, root, toRemove);
      
    }

    else if (strcmp(input, "SEARCH")==0) {
      // wants to search
      cout << "what number are you searchign for? " ;
      int toSearch;
      cin >> toSearch;
      bool exists;
      exists = SEARCH(root, toSearch);
      if (exists==false) {
	cout << "not found in tree." << endl;
      }
      else {
	cout << "is in tree, yay" << endl;
      }
      //      cout << "Exists is: " << exists << endl;
    }

    else if (strcmp(input, "PRINT")==0) {
      // wants to print
      PRINT(root, 0);
    }

    else if (strcmp(input, "QUIT")==0) {
      // wants to quit
      quit = 1;
    }

  }

  return 0;
}



node* ADD(node* &root, int data) {
  if (!root) {
    root = new node(data);
    cout << "added: " << data << endl;
  }
  else if (data < root->getValue()) {
    node* l = root->getLeft();
    root->setLeft(ADD(l, data));
    //ADD(l, data); 
  }
  else {
    
    node* r = root->getRight();
    //ADD(r, data);
    root->setRight(ADD(r, data));
  }
  return root;

}


bool SEARCH(node* root, int toSearch) {
  // search
  if (root==NULL) {
    return false;
  }
  if (root->getValue()==toSearch) {
    return true;
  }
  if (toSearch < root->getValue()) {
    return(SEARCH(root->getLeft(), toSearch));
  }
  else {
    return(SEARCH(root->getRight(), toSearch));
  }
  
}

void PRINT(node* root, int count) {
  // print it visually lol
  //cout << "root is: " << root->getValue() << endl;

  /*
  for (int a=0; a<count; a++) {
    cout << '\t' ;
  }
  */
  //cout << root->getValue() << endl;
  if (root==NULL) {
    return;
  }
  if (root->getLeft()!=NULL) {
    //cout << "there's something left of currently " << root->getValue() << endl;
    PRINT(root->getLeft(), (count+1));
  }

  for (int b=0; b<count; b++) {
    cout <<'\t';
  }
  cout << root->getValue() << endl;
  //  cout << root->getValue() << endl;
  if (root->getRight()!=NULL) {
    //cout << "there's something right of the CUR which is " << root->getValue() << endl;
    //cout << "  " ;
    PRINT(root->getRight(), (count+1));
  }
    
}


void REMOVE(node* & root, node* current, node* parent, int toRemove) {

  // base cases:
  if (root==NULL) {
    // tree is empty
    cout << "tree is empty." << endl;
    return;
  }

  if (SEARCH(root, toRemove)==false) {

    cout << "doesn't exist in tree so cant delete it!" << endl;
    return;
  }

 

  if (current->getValue()==toRemove) {

    // we found the value, now..

    
    if (current->getRight()==NULL && current->getLeft()==NULL) {
      // it's a leaf, so set pointer in that direction to null
      // leaf removal is working correctlt

      if (root->getValue()==toRemove) {
	root = NULL;
      }
      if (current->getValue() < parent->getValue()) {
	// it's a left child, so set parent->Left to null.

	parent->setLeft(NULL);
      }
      else {
	// it's a right child, so set parent->Right to null.
	parent->setRight(NULL);
      }

      return;

    }

    else if (current->getRight()==NULL) {
      // there only exists a left child
      node* ltemp = current->getLeft();
      ///finding direction that parent points to
      if (current->getValue() < parent->getValue()) {
	// child is on parent's left
	
	parent->setLeft(ltemp);
      }
      else {
	// child is on parent's right
	parent->setRight(ltemp);
      }
      delete current;
      return;
      
    }

    else if (current->getLeft()==NULL) {
      // there only exists a right child
      //cout << "it only has a right child.." << endl;
      node* rtemp = current->getRight();

      // finding direction that the parent points to
      if (current->getValue() < parent->getValue()) {
	//cout << "inside line 208" << endl;
	// child is on paren'ts left
	parent->setLeft(rtemp);
      }
      else {
	// child is on parent's right
	//cout << "child is on paren'ts right" << endl;
	parent->setRight(rtemp);
      }
      delete current;
      //cout << "returning" << endl;
      return;
    }

    else {
      // there are two children

      // time to find successor
      //cout << "there are two children." << endl;
      node* s = current->getRight();
      node* sp = current;
      while(s->getLeft()!=NULL) {
	sp = s;
	s = s->getLeft();
      }

      if (sp!=current) {
	sp->setLeft(s->getRight());
      }
      else {
	sp->setRight(s->getRight());
      }

      current->setValue(s->getValue());

      delete s;
      return;

    }
      
  }


  
  //recursive cases

  if (toRemove < current->getValue()) {
    REMOVE(root, current->getLeft(), current, toRemove);
  }

  
  else if (toRemove > current->getValue()) {
    REMOVE(root, current->getRight(), current, toRemove);
  }


}
