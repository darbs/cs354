/*
 * File:   node.h
 * Author: Darby Perez
 *
 * Created on October 14, 2012, 10:30 PM
 */

#ifndef NODE_H
#define	NODE_H
#include <stdint.h>
#include <vector>
#include <list>
#include "./limbs.h"

using namespace std;

class Node {
 public:
  uint32_t id_;
  vector<Node> children_;
  Limb limb_;
  Node(){
  }
  void setChild(Node leaf);
  // not pretty but cant access a returned node seg fault?
  // find and set elements of the tree
  void fas(uint32_t parent, Node child);
  void fasOff(uint32_t id, float * offset);
  void fasChannels(uint32_t id, uint32_t num);
  void fasFlags(uint32_t id, uint32_t flags);
  void fasOrder(uint32_t id, int * order);
  void fasIndex(uint32_t id, uint32_t index);
};

#endif	/* NODE_H */

