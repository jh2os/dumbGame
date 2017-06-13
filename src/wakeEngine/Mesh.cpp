#include "Mesh.h"
#include <iostream>

MeshObject::MeshObject(aiMesh *mesh) {
	vbo[VERTEX_BUFFER] = 0;
	vbo[TEXCOORD_BUFFER] = 0;
	vbo[NORMAL_BUFFER] = 0;
	vbo[INDEX_BUFFER] = 0;
	vbo[INSTANCE_BUFFER] = 0;
	this->diffuseTexture = 0;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	elementCount = mesh->mNumFaces * 3;
	//std::cout << glGetError() << std::endl;
	if(mesh->HasPositions()) {
		GLfloat *vertices = new GLfloat[mesh->mNumVertices * 3];
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
			vertices[i * 3] = mesh->mVertices[i].x;
			vertices[i * 3 + 1] = mesh->mVertices[i].y;
			vertices[i * 3 + 2] = mesh->mVertices[i].z;
		}
		//std::cout << "Num: " << mesh->mNumVertices << std::endl;
		///for (int i =0; i < mesh->mNumVertices * 3; i++){
		//	std::cout << i << ". " << vertices[i] << " " << std::endl;
		//}
		glGenBuffers(1, &vbo[VERTEX_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
		glBufferData(
			GL_ARRAY_BUFFER,
			3 * mesh->mNumVertices * sizeof(GLfloat),
			&vertices[0],
			GL_STREAM_DRAW
		);
			//std::cout << glGetError() << std::endl;
			glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		//delete[] vertices;
	}
	if(mesh->HasTextureCoords(0)) {
		GLfloat *texCoords = new GLfloat[mesh->mNumVertices * 2];
		for(unsigned int i = 0; i < mesh->mNumVertices; ++i) {
			//std::cout << mesh->mTextureCoords[0][i].x << ":" << mesh->mTextureCoords[0][i].y << ":" << mesh->mTextureCoords[0][i].z << std::endl;
			texCoords[i * 2] = mesh->mTextureCoords[0][i].x;
			texCoords[i * 2 + 1] = 1.0 - mesh->mTextureCoords[0][i].y;
		}

		glGenBuffers(1, &vbo[TEXCOORD_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXCOORD_BUFFER]);
		glBufferData(
			GL_ARRAY_BUFFER,
			2 * mesh->mNumVertices * sizeof(GLfloat),
			&texCoords[0],
			GL_STATIC_DRAW
		);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
	//std::cout << glGetError() << std::endl;
		//delete[] texCoords;
	}
	if(mesh->HasNormals()) {
		GLfloat *normals = new GLfloat[mesh->mNumVertices * 3];
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
			normals[i * 3] = mesh->mNormals[i].x;
			normals[i * 3 + 1] = mesh->mNormals[i].y;
			normals[i * 3 + 2] = mesh->mNormals[i].z;
		}

		glGenBuffers(1, &vbo[NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_BUFFER]);
		glBufferData(
			GL_ARRAY_BUFFER,
			3 * mesh->mNumVertices * sizeof(GLfloat),
			normals,
			GL_STATIC_DRAW
		);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//std::cout << glGetError() << std::endl;
		//delete[] normals;
	}
	if(mesh->HasFaces()) {
		GLuint *indices = new GLuint[mesh->mNumFaces * 3];
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			indices[i * 3] = mesh->mFaces[i].mIndices[0];
			indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}

		glGenBuffers(1, &vbo[INDEX_BUFFER]);
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , vbo[INDEX_BUFFER]);
		glBufferData(
			 GL_ELEMENT_ARRAY_BUFFER ,
			3 * mesh->mNumFaces * sizeof(GLuint),
			indices,
			GL_STATIC_DRAW
		);

		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(3);
	//std::cout << glGetError() << std::endl;
		//delete[] indices;
	} else { std::cout << "no faces?!?!?" << std::endl;}

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
}

MeshObject::~MeshObject() {
	if(vbo[VERTEX_BUFFER]) {
		glDeleteBuffers(1, &vbo[VERTEX_BUFFER]);
	}
	if(vbo[TEXCOORD_BUFFER]) {
		glDeleteBuffers(1, &vbo[TEXCOORD_BUFFER]);
	}
	if(vbo[NORMAL_BUFFER]) {
		glDeleteBuffers(1, &vbo[NORMAL_BUFFER]);
	}
	if(vbo[INDEX_BUFFER]) {
		glDeleteBuffers(1, &vbo[INDEX_BUFFER]);
	}
	glDeleteVertexArrays(1, &vao);
}

void MeshObject::render(GLint program, std::string textureUniform) {

	glUseProgram(program);

	GLint uniformTex = glGetUniformLocation(program, textureUniform.c_str());
	glBindVertexArray(vao);
	if (this->diffuseTexture != 0) {
		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,this->diffuseTexture);
		glUniform1i(uniformTex, 0);
	}


	glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, NULL);
	//glDrawElementsInstanced(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, NULL, 100);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

}

void MeshObject::renderInstanced(GLint program, std::string textureUniform, int instances){
	glUseProgram(program);
	GLint uniformTex = glGetUniformLocation(program, textureUniform.c_str());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,this->diffuseTexture);
	glUniform1i(uniformTex, 0);
	glBindVertexArray(vao);
	glDrawElementsInstanced(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0,  instances + 1);


	glBindVertexArray(0);

	//glUseProgram(0);

}
Mesh::Mesh(std::string folder, std::string file) {
		//std::cout << glGetError() << std::endl;
	Assimp::Importer importer;
	Logger::Instance()->writeLine("Loading model: ",file);
	std::string texpath = folder + std::string("/") + file;
	const aiScene *scene = importer.ReadFile(texpath.c_str(), 0);
	if(!scene) {
		Logger::Instance()->write("Unable to read in model file: ");
		Logger::Instance()->write(file);
		std::cout << "here" << std::endl;

	}
	//std::cout << "Has Materials: " << scene->HasMaterials() << std::endl;
	//std::cout << "Num of Materials: " << scene->mNumMaterials << std::endl;
	//std::cout << "Num of meshes: " << scene->mNumMeshes << std::endl;
	for(unsigned int i = 0; i < scene->mNumMeshes; ++i) {
		mesh.push_back(new MeshObject(scene->mMeshes[i]));
	}
	//std::cout << "New Here" << std::endl;

	aiString path;
	for(unsigned int i = 0; i < scene->mNumMaterials; ++i) {
		//std::cout << "Loading textures" << std::endl;
		unsigned int numtex;
		aiTextureType type;
		//std::cout << "here " << std::endl;
		type = aiTextureType_DIFFUSE;
		numtex = scene->mMaterials[i]->GetTextureCount(type);
		//std::cout << i << " Diffuse:" << numtex << std::endl;
		if(numtex > 0) {

			for(unsigned int j = 0; j < numtex; j++){
				scene->mMaterials[i]->GetTexture(type,j,&path,NULL,NULL,NULL,NULL,NULL);
				//std::cout << "\t"<< j+1 << ".) " << path.C_Str();
				std::string file(path.C_Str());
				std::string texpath = std::string(folder) + std::string("/") + std::string(path.C_Str());
				//std::cout << std::endl <<" \t" << texpath << std::endl;
				mesh[i]->diffuseTexture = EngineTextures::Instance()->loadFile(texpath);
				//std::cout << "Thing " << mesh[i]->diffuseTexture << std::endl;

			}
		}

		//std::cout << std::endl;
/*
		type = aiTextureType_SPECULAR;
		numtex = scene->mMaterials[i]->GetTextureCount(type);
		std::cout << i << " Specular:" << scene->mMaterials[i]->GetTextureCount(aiTextureType_SPECULAR );
		if(numtex > 0) {
			for(unsigned int j = 0; j < numtex; j++){
				scene->mMaterials[i]->GetTexture(type,j,&path,NULL,NULL,NULL,NULL,NULL);
				std::cout << "\t\t"<< j+1 << ".) " << path.C_Str();
			}
		}
		std::cout << std::endl;

		type = aiTextureType_AMBIENT;
		numtex = scene->mMaterials[i]->GetTextureCount(type);
		std::cout << i << " Ambient:" << scene->mMaterials[i]->GetTextureCount(aiTextureType_AMBIENT);
		if(numtex > 0) {
			for(unsigned int j = 0; j < numtex; j++){
				scene->mMaterials[i]->GetTexture(type,j,&path,NULL,NULL,NULL,NULL,NULL);
				std::cout << "\t\t"<< j+1 << ".) " << path.C_Str();
			}
		}
		std::cout << std::endl;

		type = aiTextureType_HEIGHT;
		numtex = scene->mMaterials[i]->GetTextureCount(type);
		std::cout << i << " Emissive:" << scene->mMaterials[i]->GetTextureCount(aiTextureType_EMISSIVE );
		if(numtex > 0) {
			for(unsigned int j = 0; j < numtex; j++){
				scene->mMaterials[i]->GetTexture(type,j,&path,NULL,NULL,NULL,NULL,NULL);
				std::cout << "\t\t"<< j+1 << ".) " << path.C_Str();
			}
		}
		std::cout << std::endl;

		type = aiTextureType_HEIGHT;
		numtex = scene->mMaterials[i]->GetTextureCount(type);
		std::cout << i << " Height:" << scene->mMaterials[i]->GetTextureCount(aiTextureType_HEIGHT);
		if(numtex > 0) {
			for(unsigned int j = 0; j < numtex; j++){
				scene->mMaterials[i]->GetTexture(type,j,&path,NULL,NULL,NULL,NULL,NULL);
				std::cout << "\t\t"<< j+1 << ".) " << path.C_Str();
			}
		}
		std::cout << std::endl;

		type = aiTextureType_NORMALS;
		numtex = scene->mMaterials[i]->GetTextureCount(type);
		std::cout << i << " Normal:" << scene->mMaterials[i]->GetTextureCount(aiTextureType_NORMALS);
		if(numtex > 0) {
			for(unsigned int j = 0; j < numtex; j++){
				scene->mMaterials[i]->GetTexture(type,j,&path,NULL,NULL,NULL,NULL,NULL);
				std::cout << "\t\t"<< j+1 << ".) " << path.C_Str();
			}
		}
		std::cout << std::endl;

		type = aiTextureType_SHININESS;
		numtex = scene->mMaterials[i]->GetTextureCount(type);
		std::cout << i << " Shiny:" << scene->mMaterials[i]->GetTextureCount(aiTextureType_SHININESS);
		if(numtex > 0) {
			for(unsigned int j = 0; j < numtex; j++){
				scene->mMaterials[i]->GetTexture(type,j,&path,NULL,NULL,NULL,NULL,NULL);
				std::cout << "\t\t"<< j+1 << ".) " << path.C_Str();
			}
		}
		std::cout << std::endl;

		type = aiTextureType_OPACITY;
		numtex = scene->mMaterials[i]->GetTextureCount(type);
		std::cout << i << " Opacity:" << scene->mMaterials[i]->GetTextureCount(aiTextureType_OPACITY);
		if(numtex > 0) {
			for(unsigned int j = 0; j < numtex; j++){
				scene->mMaterials[i]->GetTexture(type,j,&path,NULL,NULL,NULL,NULL,NULL);
				std::cout << "\t\t"<< j+1 << ".) " << path.C_Str();
			}
		}
		std::cout << std::endl;

		type = aiTextureType_LIGHTMAP;
		numtex = scene->mMaterials[i]->GetTextureCount(type);
		std::cout << i << " Lightm:" << scene->mMaterials[i]->GetTextureCount(aiTextureType_LIGHTMAP );
		if(numtex > 0) {
			for(unsigned int j = 0; j < numtex; j++){
				scene->mMaterials[i]->GetTexture(type,j,&path,NULL,NULL,NULL,NULL,NULL);
				std::cout << "\t\t"<< j+1 << ".) " << path.C_Str();
			}
		}
		std::cout << std::endl;

		type = aiTextureType_REFLECTION;
		numtex = scene->mMaterials[i]->GetTextureCount(type);
		std::cout << i << " Reflection:" << scene->mMaterials[i]->GetTextureCount(aiTextureType_REFLECTION );
		if(numtex > 0) {
			for(unsigned int j = 0; j < numtex; j++){
				scene->mMaterials[i]->GetTexture(type,j,&path,NULL,NULL,NULL,NULL,NULL);
				std::cout << "\t\t"<< j+1 << ".) " << path.C_Str();
			}
		}
		std::cout << std::endl;

		type = aiTextureType_UNKNOWN;
		numtex = scene->mMaterials[i]->GetTextureCount(type);
		std::cout << i << " Unknown:" << scene->mMaterials[i]->GetTextureCount(aiTextureType_UNKNOWN );
		if(numtex > 0) {
			for(unsigned int j = 0; j < numtex; j++){
				scene->mMaterials[i]->GetTexture(type,j,&path,NULL,NULL,NULL,NULL,NULL);
				std::cout << "\t\t"<< j+1 << ".) " << path.C_Str();
			}
		}*/
		//std::cout << std::endl << std::endl;
	}

	//Logger::Instance()->closeLogFile();
}

Mesh::~Mesh(void) {
	for (unsigned int i = 0; i < mesh.size(); ++i) {
		delete mesh.at(i);
	}
	mesh.clear();
}

void Mesh::render(GLint program, std::string textureUniform) {
	//std::cout << "Mesh size: " << mesh.size() << std::endl;
	for(unsigned int i = 0; i < mesh.size(); ++i) {
		mesh.at(i)->render(program, textureUniform);
	}
}

void Mesh::renderInstanced(GLint program, std::string textureUniform, int instances){
	for(unsigned int i = 0; i < mesh.size(); ++i) {
		mesh.at(i)->renderInstanced(program, textureUniform, instances);
	}
}

Uint32 getPixel32(SDL_Surface *surface, int x, int y) {
	Uint32 *pixels = (Uint32*)surface->pixels;
	return pixels[ (y * surface->w ) + x];
}

void putPixel32(SDL_Surface *surface, int x, int y, Uint32 pixel) {
	Uint32 *pixels = (Uint32*) surface->pixels;
	pixels[(y * surface->w) +x] = pixel;
}


void Mesh::instance(std::vector<GLfloat> instanceData) {
	for (unsigned int i = 0; i < mesh.size(); i++) {
		mesh[i]->instance(instanceData);
	}
}

void MeshObject::instance(std::vector<GLfloat> instanceData){
	//glBindVertexArray(vao);
	glGenBuffers(1, &vbo[INSTANCE_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[INSTANCE_BUFFER]);
	//std::cout << instanceData.size() << std::endl;
	glBufferData(
		GL_ARRAY_BUFFER,
		(instanceData.size() +1) * sizeof(GLfloat),
		&instanceData[0],
		GL_STATIC_DRAW
	);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);
	glVertexAttribDivisor(4, 1);
	//glEnable(GL_DEPTH_TEST);
}
