#ifndef SQUARE_H
#define SQUARE_H

#include "includes.h"

class Square {
public:
  Square();
  Square(GLuint program, float x, float y, float w, float h);
  void init(GLuint program, float x, float y, float w, float h);
  void render(glm::vec4 color, int resX, int resY);
private:
  float x;
  float y;
  float h;
  float w;
  GLuint program;
  GLuint vao;
  GLuint vbo;
  GLuint coord;
  GLuint color;

};

#endif
