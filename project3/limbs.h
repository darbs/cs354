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
    const char * name_;
    uint32_t id_;
    uint32_t channel_flags_;
    vector<float> offSet_;
    int channels_;
    int order_[6];
    float frame_[6];
    int index_;
    bool end_;
    Limb() {
        offSet_.assign(3, 0.0);
        end_ = false;
        channels_ = 0;
    }
    void setOff(float * offset);
    void setOrder(int * order);
};


#endif /* LIMBS_H */

