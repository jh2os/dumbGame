#include "Texture.h"

EngineTextures* EngineTextures::m_pInstance = NULL;

EngineTextures* EngineTextures::Instance() {
	if(!m_pInstance)
		m_pInstance = new EngineTextures;
	return m_pInstance;
}

int EngineTextures::generateTextureID() {
	glBindTexture(GL_TEXTURE_2D,0);
	GLuint TextureID = 0;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D,TextureID);
	return TextureID;
}


int EngineTextures::loadFile(std::string filename) {
	SDL_Surface* surf;
	surf = IMG_Load(filename.c_str());
	if(!surf) {
		std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
		Logger::Instance()->writeLine("IMG_Load ERROR: ",IMG_GetError());
	} else {
		Logger::Instance()->writeLine("Loaded in texture ",filename , " into surface");
	}

	return this->loadSurface(surf);

}

int EngineTextures::loadSurface(SDL_Surface* sdlSurface) {

		SDL_Surface* surf = sdlSurface;

		GLuint TextureID = this->generateTextureID();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		int Mode = GL_RGBA;

		if(surf->format->BytesPerPixel == 3) {
			Mode = GL_RGB;
		} else if (surf->format->BytesPerPixel == 4) {
			Mode = GL_RGBA;
		}

		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RGBA,sdlSurface->w,
				sdlSurface->h,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				sdlSurface->pixels);

		SDL_FreeSurface(surf);
		surf = NULL;
		return TextureID;

}
