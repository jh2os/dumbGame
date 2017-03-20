#include "Texture.h"

int EngineTexture::loadFile(std::string filename) {

	//std::cout << filename << std::endl;
	GLuint TextureID = 0;
	SDL_Surface* surf;
	SDL_PixelFormat *fmt;


	surf = IMG_Load(filename.c_str());
	fmt = surf->format;
	if(fmt->BitsPerPixel!=8){
  	std::cout << std::endl << "this is not an 8 bit pixel format size: " << (int)fmt->BytesPerPixel  << std::endl;
  	//return(-1);
	}


  if(!surf){
		Logger::Instance()->writeLine("Image failed to load: ",filename);
		std::cout << "Errors" << std::endl;
    return -1;
	}
	else {
		Logger::Instance()->writeLine("Read texture: ",filename," correctly");
    return loadSurface(surf);
  }

}

int loadSurface(SDL_Surface* sdlSurface) {
  //		SDL_Surface *tex = SDL_ConvertSurface(surf, &pf, SDL_SWSURFACE);
  std::cout << "Texture dimentions " << sdlSurface->w << ":" << sdlSurface->h << std::endl;

  glGenTextures(1, &TextureID);
  glBindTexture(GL_TEXTURE_2D, TextureID);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);


  //glPixelStorei(GL_UNPACK_ALIGNMENT, 2);
  int Mode = GL_RGB;

  if(surf->format->BytesPerPixel == 3) {
    Mode = GL_RGB;
  } else if (surf->format->BytesPerPixel == 4) {
    Mode = GL_RGBA;
  }
  glTexImage2D(	GL_TEXTURE_2D,0,Mode,surf->w,surf->h,0,Mode,GL_UNSIGNED_BYTE,surf->pixels);

  std::cout << "\t\tTexture: " << TextureID;
  glBindTexture(GL_TEXTURE_2D, 0);
  SDL_FreeSurface(surf);
  return TextureID;
}
