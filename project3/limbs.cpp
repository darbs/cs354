#include <stdint.h>
#include <iostream>
#include "./limbs.h"

using namespace std;

void Limb::connectLimb(Limb limb){
}

void Limb::setOff(float* offset){
  this->offSet[0] = offset[0];
  this->offSet[1] = offset[1];
  this->offSet[2] = offset[2];
}

void Limb::setOrder(int* order){
  this->order[0] = order[0];
  this->order[1] = order[1];
  this->order[2] = order[2];
  this->order[3] = order[3];
  this->order[4] = order[4];
  this->order[5] = order[5];
}