#ifndef MESH_H
#define MESH_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include "includes.h"


struct MeshObject {
	enum BUFFERS {
		VERTEX_BUFFER,TEXCOORD_BUFFER,NORMAL_BUFFER,INDEX_BUFFER,INSTANCE_BUFFER,
	};

	GLuint vao;
	GLuint vbo[5];
	GLuint diffuseTexture;
	unsigned int elementCount;
	MeshObject(aiMesh *mesh);
	~MeshObject();
	void load(aiMesh *mesh);
	void render(GLint program, std::string textureUniform);
	void renderInstanced(GLint program, std::string textureUniform, int instances);
	void instance(std::vector<GLfloat> instanceData);
};


class Mesh {
public:
	std::vector<MeshObject*> mesh;
	Mesh(std::string folder, std::string file);
	~Mesh(void);
	void render(GLint program, std::string textureUniform);
		void renderInstanced(GLint program, std::string textureUniform, int instances);
	void instance(std::vector<GLfloat> instanceData);
	std::vector<GLint> textures;
	GLint tex;
};


#endif
