#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "./common.h"
#include "./bb.h"
#include "./mesh.h"
#include "./io.h"
#include "./texture.h"

#define PI 3.14159265

using namespace std;

Mesh mesh;

GLuint* texture_ids;

// camera controls
bool click;
bool rclick;
float zoom = 1.1;
int zoomY;
float otheta = 0.0;
Vec3f eye = Vec3f::makeVec(2.0, 2.0, 5.0);
Vec3f oldEye;
Vec3f newEye;
GLfloat currentRotationMatrix[16];

// window parameters
int window_width = 800, window_height = 600;
float window_aspect = window_width / static_cast<float>(window_height);

bool scene_lighting;

// -----added code
Vec3f eyeVector(int x, int y) {
  Vec3f mouse = Vec3f::makeVec(2.0*x/window_width - 1.0,
                          2.0*y/window_height - 1.0,
                          0.0);
  mouse[1] = -mouse[1];
  float mousep = mouse.norm2();
  if (mousep <= 1) {
      mouse[2] = sqrt(1-mouse[0]*mouse[0]-mouse[1]*mouse[1]);
  } else {
      mouse = mouse.unit();
  }
  return mouse;
}

void computeEye() {
  float theta = acos(min(1.0f, oldEye*newEye));
  theta = theta*180/PI;
  Vec3f cross = oldEye^newEye;
  // glLoadMatrixf(currentRotationMatrix);
  glRotatef(theta, cross[0], cross[1], cross[2]);
  // glGetFloatv(GL_MODELVIEW_MATRIX, currentRotationMatrix);
  // PrintMatrix(*currentRotationMatrix);
}

void SetCamera() {
  Vec3f center = mesh.bb().center();
  gluLookAt(eye[0], eye[1], eye[2],
            center[0], center[1], center[2],
          0, 1, 0);
  glutPostRedisplay();
}
// -----end of added code

void Display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, window_aspect, 1, 1500);

  // TODO call gluLookAt such that mesh fits nicely in viewport.
  // mesh.bb() may be useful.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  SetCamera();

  if (!(oldEye == newEye)) {
    computeEye();
  }

  // glutWireCube(0.5);
  mesh.render(texture_ids);
  // mesh.render_normals();
  // mesh.render_texture();

  // TODO set up lighting, material properties and render mesh.
  // Be sure to call glEnable(GL_RESCALE_NORMAL) so your normals
  // remain normalized throughout transformations.
  glEnable(GL_RESCALE_NORMAL);
  // You can leave the axis in if you like.
  glDisable(GL_LIGHTING);
  glLineWidth(4);
  DrawAxis();
  glEnable(GL_LIGHTING);

  glFlush();
  glutSwapBuffers();
}

void PrintMatrix(GLfloat* m) {
  cout.precision(2);
  int w = 6;
  for (int i = 0; i < 4; ++i) {
    cout << setprecision(2) << setw(w) << m[i] << " "
         << setprecision(2) << setw(w) << m[i+4] << " "
         << setprecision(2) << setw(w) << m[i+8] << " "
         << setprecision(2) << setw(w) << m[i+12] << " "
         << endl;
  }
  cout << endl;
}

void PrintMatrix(GLint matrix) {
  GLfloat m[16];
  glGetFloatv(matrix, m);
  PrintMatrix(m);
}

void PrintMatrix() {
  PrintMatrix(GL_MODELVIEW_MATRIX);
}

void LoadMatrix(GLfloat* m) {
  // transpose to column-major
  for (int i = 0; i < 4; ++i) {
    for (int j = i; j < 4; ++j) {
      swap(m[i*4+j], m[j*4+i]);
    }
  }
  glLoadMatrixf(m);
}

void MultMatrix(GLfloat* m) {
  // transpose to column-major
  for (int i = 0; i < 4; ++i) {
    for (int j = i; j < 4; ++j) {
      swap(m[i*4+j], m[j*4+i]);
    }
  }
  glMultMatrixf(m);
}

void Init() {
  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  // resize the window
  window_aspect = window_width/static_cast<float>(window_height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(40.0, window_aspect, 1, 1500);
}

void DrawAxis() {
  const Vec3f c = {0, 0, 0};
  const float L = 1;
  const Vec3f X = {L, 0, 0}, Y = {0, L, 0}, Z = {0, 0, L};

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

void MouseButton(int button, int state, int x, int y) {
  cout << button << " " << state << endl;
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    click = true;
    oldEye = eyeVector(x, y);
  } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    rclick = true;
    zoomY = y;
  } else {
    click = false;
    rclick = false;
  }
  glutPostRedisplay();
}

void MouseMotion(int x, int y) {
  if (click) {
    newEye = eyeVector(x, y);
  }
  if (rclick) {
    if (zoomY > y) {
      eye /= zoom;
    } else {
      eye *= zoom;
    }
    zoomY = y;
  }
  glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case '1':
      eye = Vec3f::makeVec(2.0, 2.0, 5.0);
      cout << eye << endl;
      break;
    case 'q':
    case 27:  // esc
      exit(0);
      break;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << endl;
    cout << "Usage: ./viewer (filename.obj | -s) [-l]" << endl;
    cout << endl;
    cout << "To load data/test.obj: ./viewer data/test.obj" << endl;
    cout << "To load a custom scene: ./viewer -s" << endl;
    cout << endl;
    return 0;
  }

  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(window_width, window_height);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Object viewer");
  glutMouseFunc(MouseButton);
  glutMotionFunc(MouseMotion);
  glutKeyboardFunc(Keyboard);
  glutDisplayFunc(Display);

  Init();

  if (string(argv[1]) == "-s") {
    cout << "Create scene" << endl;
  } else {
    string filename(argv[1]);
    cout << filename << endl;

    // Detect whether to fix the light source(s) to the camera or the world
    scene_lighting = false;
    if (argc > 2 && string(argv[2]) == "-l") {
      scene_lighting = true;
    }

    // Parse the obj file, compute the normals, read the textures

    ParseObj(filename, mesh);
    mesh.compute_normals();
    // currentRotationMatrix = float[16];
    // test
    /*
    vector< vector<Vec3f> > vertexes = mesh.get_vertices();
    for (int i = 0; i < vertexes.size(); i++) {
      for (int j = 0;  j < vertexes[i].size(); j ++) {
        cout << vertexes[i][j];
      }
      cout << endl;
    }
    cout << mesh.get_vertices().size() << endl;
    /**/

    texture_ids = new GLuint[mesh.num_materials()];
    glGenTextures(mesh.num_materials(), texture_ids);

    for (int i = 0; i < mesh.num_materials(); ++i) {
      Material& material = mesh.material(i);
      material.LoadTexture(texture_ids[i]);
    }

    // do the texture rendering
  }

  glutMainLoop();

  return 0;
}
