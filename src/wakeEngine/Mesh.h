#ifndef MESH_H
#define MESH_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include "includes.h"


struct MeshObject {
	enum BUFFERS {
		VERTEX_BUFFER,TEXCOORD_BUFFER,NORMAL_BUFFER,INDEX_BUFFER
	};

	GLuint vao;
	GLuint vbo[4];
	GLuint diffuseTexture;
	unsigned int elementCount;
	MeshObject(aiMesh *mesh);
	~MeshObject();
	void load(aiMesh *mesh);
	void render(GLint program, std::string textureUniform);
};


class Mesh {
public:
	std::vector<MeshObject*> mesh;
	Mesh(std::string folder, std::string file);
	~Mesh(void);
	void render(GLint program, std::string textureUniform);
	std::vector<GLint> textures;
	GLint tex;
};

int loadTexture(std::string filename);

#endif
