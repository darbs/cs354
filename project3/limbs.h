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
#include <vector>
#include "./vec.h"

using namespace std;

class Limb {
 public:
    const char * name;
    uint32_t id;
    uint32_t channelFlags;
    vector<float> offSet;
    int channels;
    int order[6];
    float frame[6];
    int index;
    bool end;
    Limb() {
        offSet.assign(3, 0.0);
        end = false;
        channels = 0;
    }
    void setOff(float * offset);
    void setOrder(int * order);
};


#endif /* LIMBS_H */

