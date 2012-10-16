/*
 * File:   limbs.h
 * Author: Darby Perez
 *
 */

#ifndef LIMBS_H
#define LIMBS_H

#include <stdint.h>
#include <iostream>
#include <list>
#include "./vec.h"

using namespace std;

class Limb {
 public:
    const char * name;
    uint32_t id;
    uint32_t channelFlags;
    float offSet[3];
    int channels;
    int order[6];
    float frame[6];
    bool end;
    Limb() {}
    void connectLimb(Limb i);
    void setOff(float * offset);
    void setOrder(int * order);
};


#endif /* LIMBS_H */

