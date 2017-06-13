#include "Text.h"

Text::Text() {
  //std::cout << "trying to initalize freetpe" << std::endl;
  int error = FT_Init_FreeType(&this->ft);
  if(error) {
    fprintf(stderr, "Could not init freetype library\n");
    //return 1;
  }
}

Text::Text(string fontFile) {
    Text();
    this->loadFont(fontFile);
}

Text::Text(string fontFile, int fontSize) {
    Text();
    this->loadFont(fontFile);
    this->setFontSize(fontSize);
}

void Text::loadFont(string fontFile) {
  if(FT_New_Face(ft, fontFile.c_str(), 0, &face)) {
    fprintf(stderr, "Could not open font\n");
    // Log Error
  }
}

void Text::loadFont(GLuint program, string fontFile, int fontSize) {

  glUseProgram(program);
  //std::cout << "did I get here" << std::endl;
  attribute_coord = glGetAttribLocation(program, "coord");
	uniform_tex = glGetUniformLocation(program, "tex");
	uniform_color = glGetUniformLocation(program, "color");
  glGenVertexArrays(1, &vao);
  //std::cout << attribute_coord << " " << uniform_tex << " " << uniform_color << std::endl;
  glGenBuffers(1, &vbo);

  this->loadFont(fontFile);
  this->setFontSize(fontSize);
}

void Text::setFontSize(int size) {
  FT_Set_Pixel_Sizes(this->face, 0, size);
  /*for (int i = 32; i < 127; i++) {
    std::cout << (char)i << std::endl;

    if(FT_Load_Char(this->face, (char)i, FT_LOAD_RENDER)) {
      fprintf(stderr, "Could not load character 'X'\n");
      //return 1;
    }
    else {
      this->glyph[i] = this->face->glyph;
    }
  }*/

  // Now we need to set up the texture for displaying things
  //glBindTexture(GL_TEXTURE_2D, 0);

}

void Text::render(GLuint program, string text, float x, float y, int windowX, int windowY) {

  glBindVertexArray(vao);
  glUseProgram(program);

  float sx = 2.0 / windowX;
  float sy = 2.0 / windowY;

  glActiveTexture(GL_TEXTURE0);
  textureID = EngineTextures::Instance()->generateTextureID();
  glBindTexture(GL_TEXTURE_2D, textureID);
  glUniform1i(uniform_tex, 0);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glEnableVertexAttribArray(attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

  FT_GlyphSlot g = face->glyph;

  for (int i = 0; i < text.length(); i++) {
    char currentLetter = text.at(i);
    if (FT_Load_Char(face, currentLetter, FT_LOAD_RENDER))
		  continue;

    //std::cout << g->bitmap.width << std::endl;
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      g->bitmap.width,
      g->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      g->bitmap.buffer
    );

    float x2 = x + g->bitmap_left * sx;
    float y2 = -y - g->bitmap_top * sy;
    float w = g->bitmap.width * sx;
    float h = g->bitmap.rows * sy;

    GLfloat box[4][4] = {
      {x2,     -y2    , 0, 0},
      {x2 + w, -y2    , 1, 0},
      {x2,     -y2 - h, 0, 1},
      {x2 + w, -y2 - h, 1, 1},
    };

    GLfloat black[4] = {1, 1, 1, 1};
    glUniform4fv(uniform_color, 1, black);

    glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    x += (g->advance.x/64) * sx;
    y += (g->advance.y/64) * sy;
  }
  //glDisableVertexAttribArray(attribute_coord);
  glDeleteTextures(1, &textureID);
  glBindVertexArray(0);
}
