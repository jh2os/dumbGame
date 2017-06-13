#ifndef TEXTURE_H
#define TEXTURE_H

#include "includes.h"

class EngineTextures {
public:
  static EngineTextures* Instance();
  EngineTextures() {};
  EngineTextures(Timer const&){};
private:
  static EngineTextures* m_pInstance;

//private:
//  std::vector<GLint> texture;
public:
  int loadFile(std::string file);
  int loadSurface(SDL_Surface* sdlSurface);
  int generateTextureID();
//  void useTexture(GLint texNum, std::string texture);
};

#endif
