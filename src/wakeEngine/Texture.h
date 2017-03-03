#ifndef TEXTURE_H
#define TEXTURE_H

#include "includes.h"

class EngineTexture {
private:
  std::vector<GLint> texture;
public:
  int loadFile(std::string file);
  int loadSurface(SDL_Surface* sdlSurface);
  void useTexture(GLint texNum, std::string texture);
};

#endif
