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

using namespace std;

class Node {
 public:
  uint32_t id;
  vector<Node> children;
  Node(){
  }
  void setChild(Node leaf);
  void findandset(uint32_t parent, Node child);
};

#endif	/* NODE_H */

