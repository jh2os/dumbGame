#include "Square.h"

Square::Square(GLuint nprogram, float nx, float ny, float nw, float nh) {

  this->x = nx;
  this->y = ny;
  this->h = nh;
  this->w = nw;
  this->program  = nprogram;
  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &this->vbo);
  glUseProgram(program);
  this->coord = glGetAttribLocation(this->program, "coord");
  this->color = glGetUniformLocation(this->program, "color");
//  std::cout << "coord " << this->coord << " " << this->color << std::endl;
}
void Square::render(glm::vec4 color, int resX, int resY) {
  glBindVertexArray(this->vao);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glUseProgram(this->program);
  glEnableVertexAttribArray(this->coord);
  glVertexAttribPointer(this->coord, 4, GL_FLOAT, GL_FALSE, 0,0);

  GLfloat box[4][4] = {
    {x,     y,      0, 0},
    {x + w, y,      1, 0},
    {x,     y - h,  0, 1},
    {x + w, y - h,  1, 1}
  };

  GLfloat black[4] = {color.x, color.y, color.z, color.w};
  glUniform4fv(this->color, 1, black);
  glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray(0);
}
