#include <stdint.h>
#include <iostream>
#include "./limbs.h"

using namespace std;

void Limb::setOff(float* offset){
  this->offSet_[0] = offset[0];
  this->offSet_[1] = offset[1];
  this->offSet_[2] = offset[2];
}

void Limb::setOrder(int* order){
  this->order_[0] = order[0];
  this->order_[1] = order[1];
  this->order_[2] = order[2];
  this->order_[3] = order[3];
  this->order_[4] = order[4];
  this->order_[5] = order[5];
}