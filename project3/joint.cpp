#include <stdint.h>
#include <iostream>
#include <vector>
#include "./node.h"
#include "./bodyParts.h"
#include "./joint.h"

using namespace std;
Node root;
Node * ptr;
vector<BodyPart> limbs;
vector<Node>::iterator it;

void SceneGraph::CreateRoot(const char * name, uint32_t id) {
  // create start point for tree
  root = Node();
  root.id = id;
  ptr = &root;
  // create the root limb
  BodyPart limb;
  limb.name = name;
  limb.id = id;
  limbs.push_back(limb);
  cout << "-----createRoot BITCH:name=" << name << " id=" << root.id << endl;
  // cout << limbs[0].name << " " << limbs[0].id << endl;
}

void SceneGraph::CreateJoint(const char * name, uint32_t id) {
    BodyPart limb;
    limb.name = name;
    limb.id = id;
    limbs.push_back(limb);
}

void SceneGraph::CreateEndSite(const char * name, uint32_t id) {
  cout << "---createEndSite:name=" << name << " id=" << id << endl;
  // TODO
  BodyPart limb;
  limb.name = name;
  limb.id = id;
  limbs.push_back(limb);
}

void SceneGraph::SetChild(uint32_t parent, uint32_t child) {
  cout << "---setChild:parent=" << parent << " child=" << child << endl;
  root.setNode(parent, child);
  // cout << "retrieved node: " << *p->id << endl;
  // root.print();
}

void SceneGraph::SetOffset(uint32_t id, float * offset) {
  limbs[id].offSet = Vec3f::makeVec(offset[0], offset[1], offset[2]);
  cout << "---setOffset:id=" << id
          << " offset= " << limbs[id].offSet[0]
          << "," << limbs[id].offSet[1]
       << "," << limbs[id].offSet[2] << endl;
}

void SceneGraph::SetNumChannels(uint32_t id, uint16_t num) {
  limbs[id].channels = num;
    cout << "---Channels:id=" << id << " num="
            << limbs[id].channels << endl;
}

void SceneGraph::SetChannelFlags(uint32_t id, uint16_t flags) {
  cout << "setChannelFlags:id=" << id << " flags=" << flags << endl;
  // TODO
}

void SceneGraph::SetChannelOrder(uint32_t id, int * order) {
  cout  << "setChannelOrder:id=" << id << endl;
  // TODO
}

void SceneGraph::SetFrameIndex(uint32_t id, uint32_t index) {
  cout << "setFrameIndex:id=" << id << " index=" << index << endl;
  // TODO
}

void SceneGraph::SetFrameTime(float delta) {
  cout << "setFrameTime:delta=" << delta << endl;
  // TODO
}

void SceneGraph::SetNumFrames(uint32_t num) {
  cout << "setNumFrames:num=" << num << endl;
  // TODO
}

void SceneGraph::SetFrameSize(uint32_t size) {
  cout << "setFrameSize:size=" << size << endl;
  // TODO
}

void SceneGraph::AddFrame(float * data) {
    for (int i = 0; i < 6; i++) {
        limbs[i].degreesOfFreedom.push_back(data[i]);
    }
    for (int j = 1; j < limbs.size(); j++){
        for(k = 0; k < limbs[j].channels; k++){
            limbs[j].degreesOfFreedom.pushback(data[i]);
        }
    }
  // TODO adds freedom corresponding to its number of def
  // might cause problem if not added in order
  // root.degreesOfFreedom.push_back(data);
}

void SceneGraph::SetCurrentFrame(uint32_t frameNumber) {
  cout << "setCurrentFrame:frameNumber=" << frameNumber << endl;
}
