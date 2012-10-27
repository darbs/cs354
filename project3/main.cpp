/*
  CS 354 - Fall 2012
  main.cpp

  This is simple skeleton GLUT code.
*/

// C++ library includes
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <vector>

#include "./common.h"

#include "./types.h"
#include "./bvh_defs.h"
#include "./joint.h"
#include "./loader.h"
#include "./geom.h"
#include "./limbs.h"
#include "./node.h"

using namespace std;

#define PI 3.14159265f

// my variables
extern Node rootNode;
extern vector< vector<float> > allFrames;
extern uint32_t numOfFrames;
extern uint32_t frameSize;
extern float frameTime;
int frame = 0;
bool animate = false;
// created for camera manipulation
bool z = false;
bool r = false;
double zoom = 1.025f;
double turn = 1.025f;
double degrees = 0.0;
double toRad = PI / 180;



// window parameters
int window_width = 800, window_height = 600;
float window_aspect = window_width/static_cast<float>(window_height);

// callback prototypes
void InitGL();
void Display();
void Resize(int width, int height);
void Keyboard(unsigned char key, int x, int y);
void Idle();

SceneGraph sg;

Vec3f eye, center, up;
int waypoint = 1;

BoundingBox bbox = {{-100, -100, -100}, {100, 100, 100}};

char filename[1000];

bool showAxis = true;
float axisLen = 1.0f;

bool showBounds = false;

void RotateCamera(char dir) {
  if (dir == 'l') {
    degrees += turn;
  }
  if (dir == 'r') {
    degrees -= turn;
  }
  double radius = sqrt(eye[0]*eye[0] + eye[2]*eye[2]);
  eye[0] = radius*cos(degrees*PI/180);
  eye[2] = radius*sin(degrees*PI/180);
}

void changeColor(uint32_t id) {
    int color = id % 3;
    if (color >= 3) {
        color = 0;
        glColor3f(0.0, 0.0, 0.0);
    } else if (color == 2) {
        glColor3f(1.0, 0.0, 0.0);
    } else if (color == 1) {
        glColor3f(0.0, 1.0, 0.0);
    } else if (color == 0) {
        glColor3f(0.0, 0.0, 1.0);
    }
}

void rotateModel(Node * root, int allFrameIndex) {
    for (int i = 0; i < root->limb_.channels_; i++) {
        if (root->limb_.order_[i] == 5) {
            glRotatef(allFrames[allFrameIndex][i+root->limb_.index_], 0, 0, 1);
        } else if (root->limb_.order_[i] == 4) {
            glRotatef(allFrames[allFrameIndex][i+root->limb_.index_], 0, 1, 0);
        } else if (root->limb_.order_[i] == 3) {
            glRotatef(allFrames[allFrameIndex][i+root->limb_.index_], 1, 0, 0);
        }
    }
}

void makeModel(Node * root) {
    if (!root->limb_.end_) {
        rotateModel(root, frame);
        glPushMatrix();
        glColor3f(0, 0, 0);
        glutSolidCube(1);
        glPopMatrix();
        for (int i = 0; i < root->children_.size(); i++) {
            glPushMatrix();
            changeColor(root->id_);
            glBegin(GL_LINE_STRIP);
            glVertex3f(0, 0, 0);
            glVertex3f(root->children_[i].limb_.offSet_[0],
                    root->children_[i].limb_.offSet_[1],
                    root->children_[i].limb_.offSet_[2]);
            glEnd();
            glTranslatef(root->children_[i].limb_.offSet_[0],
                    root->children_[i].limb_.offSet_[1],
                    root->children_[i].limb_.offSet_[2]);
            makeModel(&root->children_[i]);
            glPopMatrix();
        }
    } else {
        if (root->id_ == 19) {
          glutSolidSphere(1.75, 5, 5);
        } else if (root->id_ == 26 || root->id_ == 35) {
            glColor3f(1.0, 0.0, 0.0);
            glutSolidCube(2.0);
        } else if (root->id_ < 19) {
            glColor3f(0, 0, 0);
            glutSolidCone(1, 2, 5, 5);
        }
    }
}

void translateOffsets(Node * node, vector<float> frame) {
    for (int i = 0; i < node->limb_.channels_; i++) {
        node->limb_.offSet_[i] = frame[node->limb_.index_+i];
    }
}

// can possible combine the two to one function
// translates first 6 offsets of frame n into root node
void modelTranslateRoot(Node * root, int allFrameIndex) {
    translateOffsets(root, allFrames[allFrameIndex]);
}

void idle() {
    float startTime = glutGet(GLUT_ELAPSED_TIME);
    float delta = 0.0;
    while (delta < frameTime) {
        delta = glutGet(GLUT_ELAPSED_TIME);
        delta = delta - startTime;
        delta /= 1000;  // fix line for real time
    }
    frame++;
    if (frame >= numOfFrames) {
        frame = 0;
    }
}

void Mouse(int button, int state, int x, int y) {
  if (button == 3) {
      eye /= zoom;
  } else if (button == 4) {
      eye *= zoom;
  }
}

void SetLighting();

void InitGL() {
  // Perform any necessary GL initialization in this function

  // enable depth testing, and set clear color to white
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  SetLighting();

  // resize the window
  Resize(window_width, window_height);
}

void ComputeLookAt() {
  float maxDist = (bbox.max-bbox.min).max();
  center = (bbox.max+bbox.min)/2.0f;
  up = Vec3f::makeVec(0.0f, 1.0f, 0.0f);
  eye = center+Vec3f::makeVec(0.0f, 0.75f*maxDist, -1.5f*maxDist);
  if (waypoint == 1) {
    eye = center+Vec3f::makeVec(0.5f*maxDist, 0.75f*maxDist, 1.5f*maxDist);
    degrees = atan(eye[2]/eye[0])*180/PI;
  } else if (waypoint == 2) {
    degrees = 90.0;
    eye = center+Vec3f::makeVec(0, 0.1f*maxDist, 1.5f*maxDist);
  } else if (waypoint == 3) {
    eye = center+Vec3f::makeVec(1.5f*maxDist, 0.1f*maxDist, 0);
    degrees = 0.0;
  }
  axisLen = maxDist*0.05f;
}

void SetLighting() {
  glShadeModel(GL_FLAT);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
}

void SetCamera() {
  gluLookAt(eye[0], eye[1], eye[2],
            center[0], center[1], center[2],
            up[0], up[1], up[2]);
}

void SetProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(40.0, window_aspect, 1, 1500);
}

void SetDrawMode() {
  glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_FILL);
}

void DrawAxis() {
  Vec3f c = (bbox.min+bbox.max)*0.5f;
  float L = (bbox.max-bbox.min).max() * 0.2;

  Vec3f X = {L, 0, 0}, Y = {0, L, 0}, Z = {0, 0, L};

  glLineWidth(2.0);

  glBegin(GL_LINES);

  glColor3f(1, 0, 0);
  glVertex3fv(c.x);
  glVertex3fv((c+X).x);

  glColor3f(0, 1, 0);
  glVertex3fv(c.x);
  glVertex3fv((c+Y).x);

  glColor3f(0, 0, 1);
  glVertex3fv(c.x);
  glVertex3fv((c+Z).x);

  glEnd();
}

void DrawFloor(float W, float H, float w, float h) {
  float a = H/h, b = W/w;
  int M = static_cast<int>(floor(a+0.5f));
  int N = static_cast<int>(floor(b+0.5f));
  int i = 0, j = 0;
  Vec3f u = {w, 0, 0}, v = {0, 0, h}, r = {-(N/2)*w, 0, -(M/2)*h};
  Vec3f p0, p1, p2, p3;
  glEnable(GL_POLYGON_SMOOTH);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  glBegin(GL_QUADS);
  glColor3f(0.7, 0.7, 0.7);
  for (j = 0; j < N; j++) {
    p0 = r+u*static_cast<float>(j%2);
    for (i = j%2; i < M; i += 2) {
      p1 = p0+u;
      p2 = p1+v;
      p3 = p2-u;

      glVertex3fv(p3.x);
      glVertex3fv(p2.x);
      glVertex3fv(p1.x);
      glVertex3fv(p0.x);

      p0 += u*2.0f;
    }
    r += v;
  }
  glEnd();
}

void DrawRect(const Vec3f & u, const Vec3f & v, const Vec3f & o) {
  glBegin(GL_LINE_STRIP);
  glColor3f(0, 0, 1);
  glVertex3fv(o.x);
  glVertex3fv((o+u).x);
  glVertex3fv((o+u+v).x);
  glVertex3fv((o+v).x);
  glVertex3fv(o.x);
  glEnd();
}

void DrawBounds() {
  Vec3f u, v, m1[] = {bbox.min, bbox.max}, m2[] = {bbox.max, bbox.min};

  for (int k = 0; k < 2; k++) {
    for (int i = 0; i < 3; i++) {
      for (int j = i+1; j < 3; j++) {
        u = m1[k];
        v = m1[k];
        u.x[i] = m2[k].x[i];
        v.x[j] = m2[k].x[j];
        u = u-m1[k];
        v = v-m1[k];
        DrawRect(u, v, m1[k]);
      }
    }
  }
}

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  SetProjection();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  SetLighting();
  SetCamera();
  SetDrawMode();
  DrawFloor(800, 800, 80, 80);

  glPushMatrix();
  // start position
  glTranslatef(rootNode.limb_.offSet_[0],
                    rootNode.limb_.offSet_[1],
                    rootNode.limb_.offSet_[2]);
  // translate root and draw model
  modelTranslateRoot(&rootNode, frame);

  makeModel(&rootNode);
  // animate if space is hit
  if (animate) {
    idle();
  }
  glPopMatrix();

  if (showAxis) DrawAxis();
  if (showBounds) DrawBounds();
  glFlush();          // finish the drawing commands
  glutSwapBuffers();  // and update the screen
  glutPostRedisplay();
}

// This reshape function is called whenever the user
// resizes the display window.
void Resize(int width, int height) {
  window_width = width;
  window_height = height;
  float fheight = static_cast<float>(height);
  window_aspect = width / fheight;

  // resize the window
  glViewport(0, 0, window_width, window_height);

  SetProjection();

  // setup basic orthographic projection
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // let glut know to redraw the screen
  glutPostRedisplay();
}

// This function is called whenever the user hits letters or numbers
// on the keyboard.  The 'key' variable has the character the user hit,
// and x and y tell where the mouse was when it was hit.
void Keyboard(unsigned char key, int x, int y) {
  y = window_height - y;
  float sgn = 1.0f;
  Vec3f v;

  switch (key) {
    case '1':
      waypoint = 1;
      ComputeLookAt();
      break;
    case '2':
      waypoint = 2;
      ComputeLookAt();
      break;
    case '3':
      waypoint = 3;
      ComputeLookAt();
      break;
    case 'z':
      eye /= zoom;
      cout << "Zoom in" << endl;
      SetCamera();
      break;
    case 'Z':
      eye *= zoom;
      cout << "Zoom out" << endl;
      SetCamera();
      break;
    case 'j':
      RotateCamera('l');
      cout << "Orbit left" << endl;
      SetCamera();
      break;
    case 'k':
      RotateCamera('r');
      cout << "Orbit right" << endl;
      SetCamera();
      break;
    case ' ':
      animate = !animate;
      cout << "Start/stop animation" << endl;
      break;
    case 'a':
      showAxis=!showAxis;
      break;
    case 'b':
      showBounds=!showBounds;
      break;
    case 'q':
    case 27:  // esc
      exit(0);
      break;
  }

  // let glut know to redraw the screen
  glutPostRedisplay();
}

void Idle() {}

void processCommandLine(int argc, char *argv[]) {
  if (argc>1) {
    snprintf(&(filename[0]), strlen(argv[1])+1, "%s", argv[1]);
    BVHLoader::loadBVH(filename, &sg);
    ComputeLookAt();
  } else {
    printf("Filename argument required.\n");
    exit(0);
  }
}

void showMenu() {
  cout << "------------ menu ------------" << endl;
  cout << "q - quit" << endl;
  cout << "a - show/hide axis" << endl;
  cout << "b - show/hide bounds" << endl;
  cout << "[1-3] - move to waypoint" << endl;
  cout << "z - zoom in or scroll the mouse wheel forward" << endl;
  cout << "Z - zoom out or scroll the mouse wheel backward" << endl;
  cout << "j - rotate left" << endl;
  cout << "k - rotate right" << endl;
  cout << "[SPACE] - start/stop" << endl;
}

int main(int argc, char *argv[]) {
  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(window_width, window_height);
  glutInitWindowPosition(100, 100);
  // Do not change the name of the window -- it is needed for the screenshot
  glutCreateWindow("Mocap");
  glutDisplayFunc(Display);
  glutReshapeFunc(Resize);
  glutKeyboardFunc(Keyboard);
  glutMouseFunc(Mouse);
  glutIdleFunc(Idle);

  processCommandLine(argc, argv);

  showMenu();

  InitGL();
  // glColor3f(0, 0, 0);
  glutMainLoop();

  return 0;
}
