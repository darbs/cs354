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

void SceneGraph::CreateRoot(const char * name, uint32_t id) {
  root.name = name;
  root.id = id;
  rootNode.id = id;
  limbStack.push_back(root);
  cout << "!!!!!!!!-----createRoot:name=" << root.name
          << " id=" << root.id << endl;
}

void SceneGraph::CreateJoint(const char * name, uint32_t id) {
  Limb joint;
  joint.name = name;
  joint.id = id;
  limbStack.push_back(joint);
  cout << "!!!!!!!!-----addedJoint:name=" << joint.name
          << " id=" << joint.id << " size: " << limbStack.size() << endl;
}

void SceneGraph::CreateEndSite(const char * name, uint32_t id) {
  Limb end;
  end.end = true;
  end.name = name;
  end.id = id;
  limbStack.push_back(end);
  cout << "---createEndSite:name=" << end.name << " id=" << end.id << endl;
}

// setChild called b4 all joints created!!!
// iterate thought limbStack to find limbs and connect them in the tree
void SceneGraph::SetChild(uint32_t parent, uint32_t child) {
  cout << "want to set " << parent << " with child " << child << endl;
  Node c;
  c.id = child;
  // have no idea how to do this in c++
  // get seg fault when find node then try to add to it
  // from here....
  // i want to punch a baby....
  rootNode.findandset(parent, c);
  cout << rootNode.children.size() << endl;
}

void SceneGraph::SetOffset(uint32_t id, float * offset) {
  for (int i = 0; i < limbStack.size(); i ++) {
     if (limbStack[i].id == id) {
      limbStack[i].setOff(offset);
      cout << limbStack[i].name << " id:" << id
              << " offset: " << limbStack[i].offSet << endl;
      break;
    }
  }
}

void SceneGraph::SetNumChannels(uint32_t id, uint16_t num) {
  for (int i = 0; i < limbStack.size(); i ++) {
     if (limbStack[i].id == id) {
      limbStack[i].channels = num;
      cout << limbStack[i].name << " id:" << id
              << " channels: " << limbStack[i].channels << endl;
      break;
    }
  }
}

void SceneGraph::SetChannelFlags(uint32_t id, uint16_t flags) {
  for (int i = 0; i < limbStack.size(); i ++) {
     if (limbStack[i].id == id) {
      limbStack[i].channelFlags = flags;
      cout << limbStack[i].name << " id:" << id
              << " channels: " << limbStack[i].channelFlags << endl;
      break;
    }
  }
}

void SceneGraph::SetChannelOrder(uint32_t id, int * order) {
  for (int i = 0; i < limbStack.size(); i ++) {
     if (limbStack[i].id == id) {
      limbStack[i].setOrder(order);
      cout << limbStack[i].name << " id:" << id << "order: "
              << limbStack[i].order[0] << limbStack[i].order[1]
              << limbStack[i].order[2] << limbStack[i].order[3]
              << limbStack[i].order[4] << limbStack[i].order[5]
              << endl;
      break;
    }
  }
}

void SceneGraph::SetFrameIndex(uint32_t id, uint32_t index) {
  cout << "setFrameIndex:id=" << id << " index=" << index << endl;
  // TODO
}

void SceneGraph::SetFrameTime(float delta) {
  frameTime = delta;
  cout << " setFrameTime:delta=" << frameTime << endl;
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
  // TODO adds freedom corresponding to its number of def
  // might cause problem if not added in order
  int index = 0;
  // cout << limbStack.size() << " " << frameNum << endl;
  for (int i = 0; i < limbStack.size(); i++) {
    for (int j = 0; j < limbStack[i].channels; j++) {
      if (!limbStack[i].end) {
        limbStack[i].frame[j] = data[index];
      }
      index++;
    }
  }
}

void SceneGraph::SetCurrentFrame(uint32_t frameNumber) {
  frameNum = frameNumber;
  cout << " setCurrentFrame:frameNumber=" << frameNum << endl;
}
