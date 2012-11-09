#include <vector>

#include "./mesh.h"
#include "./common.h"

using namespace std;

Mesh::Mesh() {
  _cur_mtl = -1;
}

// This will be called by the obj parser
void Mesh::AddVertex(const Vec3f& v) {
  // vertices[i] = [vertex[i], plane2normal1, plane2normal....]
  vector <Vec3f> vertex;
  vertex.push_back(v);
  _vertices.push_back(vertex);
  // updates the bounding box
  _bb(v);
}

// This will be called by the obj parser
void Mesh::AddTextureVertex(const Vec3f& v) {
  _textures.push_back(v);
}

void Mesh::AddPolygon(const std::vector<int>& p, const std::vector<int>& pt) {
  vector <Vec3f> polygon_texture;
  vector <Vec3f> polygon_vertices;
  for (int i = 0; i < p.size(); i++) {
    polygon_vertices.push_back(_vertices[p[i]][0]);
    if (!_textures.empty()) {
      polygon_texture.push_back(_textures[pt[i]]);
    }
  }
  // polygon is atleast of size 3
  // compute 2 vectors from the points on polygon
  // to use to computer normal for polygon
  Vec3f v0 = polygon_vertices[1] - polygon_vertices[0];
  Vec3f v1 = polygon_vertices[2] - polygon_vertices[0];
  Vec3f normal = v0^v1;
  // add polygon normal to each vertex in the polygon
  for (int i = 0; i <  p.size(); i ++) {
    _vertices[p[i]].push_back(normal);
  }
  if (!polygon_texture.empty()) {
    _polygon_textures.push_back(polygon_texture);
  }
  _polygons.push_back(p);
  _polygon2material.push_back(_cur_mtl);
}

void Mesh::render(bool texture, GLuint* texture_ids) {
  for (int i = 0; i < _polygons.size(); i ++) {
    if (texture && !_polygon_textures.empty()) {
      Material m = material(polygon2material(i));
      render_material(m, texture_ids);
    }
    if (_polygons[i].size() == 3) {
      glBegin(GL_TRIANGLES);
    } else {
      glBegin(GL_POLYGON);
    }
    // retrieve the polygon and render vertices for
    // point in polygon i
    vector<int> polygon = _polygons[i];
    for (int j = 0; j < _polygons[i].size(); j++) {
      if (!_polygon_textures.empty() && texture) {
        glTexCoord2d(1.0-_polygon_textures[i][j][0],
              1.0-_polygon_textures[i][j][1]);
      }
      // retrieve the vertex and normal
      Vec3f vertex = _vertices[polygon[j]][0];
      Vec3f normal = _normals[polygon[j]];
      glNormal3f(normal[0], normal[1], normal[2]);
      glVertex3f(vertex[0], vertex[1], vertex[2]);
    }
    glEnd();
  }
}

void Mesh::render_normals() {
  glColor3f(0.5, 1.0, 0.5);
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
  for (int i = 0; i < _vertices.size(); i ++) {
    glVertex3f(_vertices[i][0][0],
            _vertices[i][0][1],
            _vertices[i][0][2]);
    glVertex3f(_vertices[i][0][0]+_normals[i][0],
            _vertices[i][0][1]+_normals[i][1],
            _vertices[i][0][2]+_normals[i][2]);
  }
  glEnd();
  glEnable(GL_LIGHTING);
}

void Mesh::render_material(Material m, GLuint* texture_ids) {
  if (m.texture_id() != -1) {
    Vec3f spec = m.specular();
    Vec3f diff = m.diffuse();
    Vec3f ambi = m.ambient();
    GLfloat specular[] = {spec[0], spec[1], spec[2]};
    GLfloat diffuse[] = {diff[0], diff[1], diff[2]};
    GLfloat ambient[] = {ambi[0], ambi[1], ambi[2]};
    GLfloat coeff = m.specular_coeff();
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &coeff);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m.texture_id());
  } else {
    glDisable(GL_TEXTURE_2D);
  }
}

// Computes a normal for each vertex.
void Mesh::compute_normals() {
  for (int i = 0; i < _vertices.size(); i ++) {
    Vec3f vn = Vec3f::makeVec(0.0, 0.0, 0.0);
    for (int j = 1; j < _vertices[i].size(); j ++) {
      vn += _vertices[i][j];
    }
    _normals.push_back(vn.unit());
  }
}

// added for debugging
vector< vector<Vec3f> > Mesh::get_vertices() {
  return _vertices;
}

vector<Vec3f> Mesh::get_textures() {
  return _textures;
}

vector< vector<int> > Mesh::get_polygons() {
  return _polygons;
}

vector<Vec3f> Mesh::get_normals() {
  return _normals;
}
