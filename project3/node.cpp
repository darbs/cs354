/*
 * File:   node.cpp
 * Author: darby
 *
 * Created on October 14, 2012, 10:30 PM
 */
#include <iostream>
#include <stdint.h>
#include "./node.h"

using namespace std;

// set child node
void Node::setChild(Node child) {
  this->children.push_back(child);
  cout << this->id << " has " << this->children.size() << endl;
}

// search for node;
void Node::findandset(uint32_t id, Node child) {
  if (this->id == id) {
    cout << "!FOUND! " << this->id << endl;
    this->setChild(child);
  } else {
    for (int i = 0; i < this->children.size(); i++) {
      // cout << this->children[i].id << " ";
      this->children[i].findandset(id, child);
    }
  }
}