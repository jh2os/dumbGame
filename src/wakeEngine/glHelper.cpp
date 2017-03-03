#include "glHelper.h"
#include "Logger.h"
#include <iostream>
// Public function that loads shader
bool glHelper::loadShader(std::string shadername, std::string file, GLenum type) {
	Logger::Instance()->writeLine("Reading in shader \"",shadername,"\" file: ", file);
	//std::cout << glGetError() << std::endl;
	int shader  = read_file(file.c_str(), type);
	
	GLint compile_ok;
	//std::cout << glGetError() << std::endl;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);

	if (compile_ok == GL_FALSE) {
		//cerr << file << ":";
		Logger::Instance()->write("Error in loading shader \"");
		Logger::Instance()->write(shadername);
 		Logger::Instance()->write("\" \t file: ");
		Logger::Instance()->write(file);
		Logger::Instance()->endline();
		debug_shader(shader);
		//cout << endl;
		//glDeleteShader(shader);
		return false;
	}
	//std::cout << glGetError() << std::endl;
	shaders[shadername] = shader;
	//std::cout << glGetError() << std::endl;
return true;
}



// Returns shader with this name
GLint glHelper::shader(std::string shader) {
	GLint returnShader = shaders[shader];
	return returnShader;
}


void glHelper::createProgram(std::string program) {
	GLuint daProgram = glCreateProgram();
	programs[program] = daProgram;
	Logger::Instance()->writeLine("Creating Shader Program: ",program);
}


void glHelper::attachShader(std::string program, std::string shader) {
	Logger::Instance()->writeLine("Program: ",programs[program],"\tAttaching shader: ",shaders[shader]);
	glAttachShader(programs[program], shaders[shader]);
}


void glHelper::linkProgram(std::string program) {
	Logger::Instance()->writeLine("Compiling shader program");
	glLinkProgram(programs[program]);
	GLint Result;
	GLint InfoLogLength;
	glGetProgramiv(programs[program], GL_LINK_STATUS, &Result);
	glGetProgramiv(programs[program], GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(programs[program], InfoLogLength, NULL, &ProgramErrorMessage[0]);
		Logger::Instance()->writeLine(&ProgramErrorMessage[0]);
	}
}

void glHelper::getAttribute(std::string program, std::string attribS) {
	GLint attrib = glGetAttribLocation(programs[program],attribS.c_str());
	if (attrib == -1) {
	    //cerr << "Problem finding attributez " << attribS << endl;
		Logger::Instance()->write("Problem finding attributez ");
		Logger::Instance()->write(attribS);
		Logger::Instance()->endline();
	}
	else
   		attribs[attribS] = attrib;
}

GLint glHelper::attrib(std::string attrib) {
 	return attribs[attrib];
}

GLint glHelper::program(std::string daprogram) {
	return programs[daprogram];
}

void glHelper::useProgram(std::string program) {
	glUseProgram(programs[program]);
	activeProgram = programs[program];
}

// Private function that reads file supplied from loadshader function
GLint glHelper::read_file(const char* filename, GLenum type) {

	GLint shaderid = glCreateShader(type);

	std::string code;
	std::ifstream shaderStream(filename, std::ios::in);
	if(shaderStream.is_open()) {
		std::string line = "";
		while(getline(shaderStream, line)) {
		  code += line + "\n";
		}
		shaderStream.close();
		char const * shaderSourcePointer = code.c_str();
		glShaderSource(shaderid, 1, &shaderSourcePointer, NULL);
		glCompileShader(shaderid);
		return shaderid;
  	}
  	else
    	return -1;
}



// coppied from wikibooks
void glHelper::debug_shader(GLuint object) {
	GLint log_length = 0;
	if (glIsShader(object)) {
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	} else if (glIsProgram(object)) {
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	} else {
		//cerr << "printlog: Not a shader or a program" << endl;
		Logger::Instance()->write("printlog: Not a shader or a program");		
		return;
	}

	char* log = (char*)malloc(log_length);
	
	if (glIsShader(object))
		glGetShaderInfoLog(object, log_length, NULL, log);
	else if (glIsProgram(object))
		glGetProgramInfoLog(object, log_length, NULL, log);
	
	Logger::Instance()->write("Error compiling shader");
	Logger::Instance()->endline();
	Logger::Instance()->write(log);
	Logger::Instance()->endline();
	//cerr << log;
	free(log);
}

