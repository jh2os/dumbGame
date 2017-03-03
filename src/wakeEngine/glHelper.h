#ifndef GLHELPER_H
#define GLHELPER_H

#include "includes.h"

class glHelper {
	public:
	// Functions relating to shaders
	bool loadShader(std::string shadername, std::string file, GLenum type);
	GLint shader(std::string shader);
	void createProgram(std::string program);
	void attachShader(std::string program, std::string shader);
	void linkProgram(std::string program);
	void getAttribute(std::string program,std::string attrib);
	GLint attrib(std::string attrib);
	GLint program(std::string program);
	void useProgram(std::string program);
	GLint activeProgram;

	private:
	GLint read_file(const char* filename,GLenum type);
	void debug_shader(GLuint object);
	std::map<std::string,GLint> programs;
	std::map<std::string,GLint> shaders;
	std::map<std::string,GLint> attribs;
};

#endif
