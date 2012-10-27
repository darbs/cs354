#include <stdint.h>
#include <iostream>
#include <vector>
#include <list>
#include "./joint.h"
#include "./limbs.h"
#include "./node.h"

using namespace std;
Limb root;
Node rootNode;
vector<Limb> limbStack;
vector<float> frameStack;
float frameTime;
uint32_t numOfFrames;
uint32_t frameSize;
uint32_t frameNum;
vector<float> frames;
vector< vector<float> > allFrames;

// create limb and push to stack for use of adding to node later
void SceneGraph::CreateRoot(const char * name, uint32_t id) {
  root.name_ = name;
  root.id_ = id;
  root.channels_ = 6;
  root.offSet_.assign(6, 0.0);
  root.index_ = 0;
  rootNode.id_ = id;
  rootNode.limb_ = root;
  limbStack.push_back(root);
}

void SceneGraph::CreateJoint(const char * name, uint32_t id) {
  Limb joint;
  joint.name_ = name;
  joint.id_ = id;
  limbStack.push_back(joint);
}

void SceneGraph::CreateEndSite(const char * name, uint32_t id) {
  Limb end;
  end.end_ = true;
  end.name_ = name;
  end.id_ = id;
  limbStack.push_back(end);
}

// called before class limb vals are init
void SceneGraph::SetChild(uint32_t parent, uint32_t child) {
  Node c;
  c.id_ = child;
  c.limb_ = limbStack[child];
  rootNode.fas(parent, c);
}

void SceneGraph::SetOffset(uint32_t id, float * offset) {
  rootNode.fasOff(id, offset);
}

void SceneGraph::SetNumChannels(uint32_t id, uint16_t num) {
  rootNode.fasChannels(id, num);
}

void SceneGraph::SetChannelFlags(uint32_t id, uint16_t flags) {
  rootNode.fasFlags(id, flags);
}

void SceneGraph::SetChannelOrder(uint32_t id, int * order) {
  rootNode.fasOrder(id, order);
}

void SceneGraph::SetFrameIndex(uint32_t id, uint32_t index) {
  rootNode.fasIndex(id, index);
}

void SceneGraph::SetFrameTime(float delta) {
  frameTime = delta;
}

void SceneGraph::SetNumFrames(uint32_t num) {
  numOfFrames = num;
}

void SceneGraph::SetFrameSize(uint32_t size) {
  frameSize = size;
}

void SceneGraph::AddFrame(float * data) {
    vector<float> frame;
    for (int i = 0; i < numOfFrames; i++) {
        frame.push_back(data[i]);
    }
    allFrames.push_back(frame);
}

void SceneGraph::SetCurrentFrame(uint32_t frameNumber) {
  frameNum = frameNumber;
}
