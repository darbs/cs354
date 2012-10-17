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

void SceneGraph::CreateRoot(const char * name, uint32_t id) {
  root.name = name;
  root.id = id;
  root.channels = 6;
  root.offSet.assign(6, 0.0);
  root.index = 0;
  // cout << root.channels << endl;
  rootNode.id = id;
  rootNode.limb = root;
  limbStack.push_back(root);
}

void SceneGraph::CreateJoint(const char * name, uint32_t id) {
  Limb joint;
  joint.name = name;
  joint.id = id;
  limbStack.push_back(joint);
}

void SceneGraph::CreateEndSite(const char * name, uint32_t id) {
  Limb end;
  end.end = true;
  end.name = name;
  end.id = id;
  limbStack.push_back(end);
}

// called before class vals are init
void SceneGraph::SetChild(uint32_t parent, uint32_t child) {
  Node c;
  c.id = child;
  c.limb = limbStack[child];
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
  // cout << " setFrameTime:delta=" << frameTime << endl;
}

void SceneGraph::SetNumFrames(uint32_t num) {
  numOfFrames = num;
  cout << " setNumFrames:num=" << numOfFrames << endl;
}

void SceneGraph::SetFrameSize(uint32_t size) {
  frameSize = size;
  cout << " setFrameSize:size=" << frameSize << endl;
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
  cout << " setCurrentFrame:frameNumber=" << frameNum << endl;
}
