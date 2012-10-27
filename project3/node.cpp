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
  this->children_.push_back(child);
}

// repetitive find and set methods, not pretty but works
// cant figure out a generic find to return node * without
// segfault
void Node::fas(uint32_t id, Node child) {
  if (this->id_ == id) {
    this->setChild(child);
  } else {
    for (int i = 0; i < this->children_.size(); i++) {;
      this->children_[i].fas(id, child);
    }
  }
}

void Node::fasOff(uint32_t id, float* offset) {
    if (this->id_ == id) {
        this->limb_.setOff(offset);
    } else {
        for (int i = 0; i < this->children_.size(); i ++) {
            this->children_[i].fasOff(id, offset);
        }
    }
}

void Node::fasChannels(uint32_t id, uint32_t num) {
    if (this->id_ == id) {
        this->limb_.channels_ = num;
    } else {
        for (int i = 0; i < this->children_.size(); i ++) {
            this->children_[i].fasChannels(id, num);
        }
    }
}

void Node::fasFlags(uint32_t id, uint32_t num) {
    if (this->id_ == id) {
        this->limb_.channel_flags_ = num;
    } else {
        for (int i = 0; i < this->children_.size(); i ++) {
            this->children_[i].fasFlags(id, num);
        }
    }
}

void Node::fasOrder(uint32_t id, int * order) {
    if (this->id_ == id) {
        this->limb_.setOrder(order);
    } else {
        for (int i = 0; i < this->children_.size(); i ++) {
            this->children_[i].fasOrder(id, order);
        }
    }
}

void Node::fasIndex(uint32_t id, uint32_t index) {
    if (this->id_ == id) {
        this->limb_.index_ = index;
    } else {
        for (int i = 0; i < this->children_.size(); i ++) {
            this->children_[i].fasIndex(id, index);
        }
    }
}
