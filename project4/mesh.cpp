#include <vector>

#include "./mesh.h"
#include "./common.h"

using namespace std;

int i = 0;

Mesh::Mesh() {
  _cur_mtl = -1;
}

// This will be called by the obj parser
void Mesh::AddVertex(const Vec3f& v) {
  // TODO
  // vertice[i][0] will vontain vertex i
  // while vertice[i][j] will contain jth polygon normal incident
  // on vertex i
  vector <Vec3f> vertex;
  vertex.push_back(v);
  vertices.push_back(vertex);
  // updates the bounding box
  _bb(v);
}

// This will be called by the obj parser
void Mesh::AddTextureVertex(const Vec3f& v) {
  // TODO
  GLfloat x = v[0];
  GLfloat y = v[1];
  GLfloat z = v[2];
  textures.push_back(Vec3f::makeVec(x, y, z));
}

// p is the list of indices of vertices for this polygon.  For example,
// if p = {0, 1, 2} then the polygon is a triangle with the zeroth, first and
// second vertices added using AddVertex.
//
// pt is the list of texture indices for this polygon, similar to the
// actual vertices described above.
void Mesh::AddPolygon(const std::vector<int>& p, const std::vector<int>& pt) {
  // TODO
  // updates the poly2mat map
  vector <Vec3f> polygon;
  vector <Vec3f> polygon_texture;
  for (int i = 0; i < p.size(); i++) {
    polygon.push_back(vertices[p[i]][0]);
    polygon_texture.push_back(textures[pt[i]]);
  }
  // polygon is atleast of size 3
  // compute 2 vectors from the points on polygon
  // to use to computer normal for polygon
  Vec3f v0 = polygon[1] - polygon[0];
  Vec3f v1 = polygon[2] - polygon[0];
  Vec3f normal = v0^v1;

  // add polygon normal to each vertex in the polygon
  for (int i = 0; i <  p.size(); i ++) {
    vertices[p[i]].push_back(normal);
  }

  polygon_textures.push_back(polygon_texture);
  polygons.push_back(polygon);
  _polygon2material.push_back(_cur_mtl);
}

void Mesh::render(GLuint* texture_ids) {
  glEnable(GL_TEXTURE_2D);
  for (int i = 0; i < polygons.size(); i ++) {
    glBindTexture(GL_TEXTURE_2D, texture_ids[polygon2material(i)]);
    if (polygons[i].size() == 3) {
      glBegin(GL_TRIANGLES);
    } else {
      glBegin(GL_POLYGON);
    }
    for (int j = 0; j < polygons[i].size(); j++) {
      glTexCoord3f(polygon_textures[i][j][0],
              polygon_textures[i][j][1],
              polygon_textures[i][j][2]);
      glVertex3f(polygons[i][j][0],  polygons[i][j][1], polygons[i][j][2]);
    }
    glEnd();
  }
}

void Mesh::render_normals() {
  // glColor3f(1.0, 0.5, 0.5);
  glBegin(GL_LINES);
  for (int i = 0; i < vertices.size(); i ++) {
    glVertex3f(vertices[i][0][0],
            vertices[i][0][1],
            vertices[i][0][2]);
    glVertex3d(vertices[i][0][0]+normals[i][0],
            vertices[i][0][1]+normals[i][1],
            vertices[i][0][2]+normals[i][2]);
  }
  glEnd();
}

void Mesh::render_texture() {
  /*
  glEnable(GL_TEXTURE_3D);
  texture_ids = new GLuint[polygons.size()];
  for (int i = 0; i < polygons.size(); i ++) {
    texture_ids[i] = polygon2material(i);
  }
  glBindTexture(GL_TEXTURE_3D, polygon2material(0));
  */
  glEnable(GL_TEXTURE_3D);
  // given polygon i
  // get index j for material of polygon i
  // get material j
  glEnd();
}

// Computes a normal for each vertex.
void Mesh::compute_normals() {
  // TODO don't forget to normalize your normals!
  for (int i = 0; i < vertices.size(); i ++) {
    Vec3f vn = Vec3f::makeVec(0.0, 0.0, 0.0);
    for (int j = 1; j < vertices[i].size(); j ++) {
      vn += vertices[i][j];
    }
    // cout << vn.unit() << endl;
    normals.push_back(vn.unit());
  }
}

// delete added for testing
vector< vector<Vec3f> > Mesh::get_vertices() {
  return vertices;
}

vector<Vec3f> Mesh::get_textures() {
  return textures;
}

vector< vector<Vec3f> > Mesh::get_polygons() {
  return polygons;
}

vector<Vec3f> Mesh::get_normals() {
  return normals;
}
