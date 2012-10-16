/*
 * File:   node.cpp
 * Author: darby
 *
 * Created on October 14, 2012, 10:30 PM
 */
#include <iostream>
#include <stdint.h>
#include "./node.h"
#include "./limbs.h"

using namespace std;

// set child node
void Node::setChild(Node child) {
  this->children.push_back(child);
  // cout << this->id << " has " << this->children.size() << endl;
}

// search for node, not pretty but cant get find to work;
void Node::fas(uint32_t id, Node child) {
  if (this->id == id) {
    // cout << "!FOUND! " << this->id << endl;
    this->setChild(child);
  } else {
    for (int i = 0; i < this->children.size(); i++) {
      // cout << this->children[i].id << " ";
      this->children[i].fas(id, child);
    }
  }
}

void Node::fasOff(uint32_t id, float* offset) {
    if (this->id == id) {
        this->limb.setOff(offset);
    } else {
        for (int i = 0; i < this->children.size(); i ++) {
            this->children[i].fasOff(id, offset);
        }
    }
}

void Node::fasChannels(uint32_t id, uint32_t num) {
    if (this->id == id) {
        this->limb.channels = num;
    } else {
        for (int i = 0; i < this->children.size(); i ++) {
            this->children[i].fasChannels(id, num);
        }
    }
}

void Node::fasFlags(uint32_t id, uint32_t num) {
    if (this->id == id) {
        this->limb.channelFlags = num;
    } else {
        for (int i = 0; i < this->children.size(); i ++) {
            this->children[i].fasFlags(id, num);
        }
    }
}

void Node::fasOrder(uint32_t id, int * order) {
    if (this->id == id) {
        this->limb.setOrder(order);
    } else {
        for (int i = 0; i < this->children.size(); i ++) {
            this->children[i].fasOrder(id, order);
        }
    }
}

void Node::fasIndex(uint32_t id, uint32_t index) {
    if (this->id == id) {
        this->limb.index = index;
    } else {
        for (int i = 0; i < this->children.size(); i ++) {
            this->children[i].fasIndex(id, index);
        }
    }
}
