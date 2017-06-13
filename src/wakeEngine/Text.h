#ifndef TEXT_H
#define TEXT_H

#include "includes.h"
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

class Text {

private:
  FT_Library ft;
  FT_Face face;
  map<int, FT_GlyphSlot> glyph;
  map<int, GLuint> textures;
  GLuint textureID;
  GLuint vbo;
  GLuint vao;
  GLint uniform_tex;
  GLint uniform_color;
  GLuint attribute_coord;
public:
  Text();
  Text(string fontFile, int fontSize);
  Text(string fontFile) ;
  void loadFont(string fontFile);
  void loadFont(GLuint program, string fontFile, int fontSize);
  void setFontSize(int size);
  void render(GLuint program,string text, float x, float y, int windowX, int windowY);
};

#endif
