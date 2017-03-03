#ifndef MODEL_H
#define MODEL_H

#include "includes.h"
#include "Camera.h"
#include "PhysicsModel.h"

using namespace std;

struct modelData {
  GLuint verts;
  GLuint size;
};

class Model: public PhysicsModel {
 private:
  glm::mat4 MVP;
  glm::mat4 modelTransform;

  glm::vec3 position;
  glm::vec3 newPosition;

  glm::mat4 scaleModel;
  glm::mat4 rotationModel;

  float rotation;
  glm::vec3 rotationAxis;
  glm::vec3 modelScale;

 public:
  bool physics;
  Model();
  glm::vec3 getPosition();
  void setPosition(glm::vec3 nPosition);
  void setRotationa(float degrees, glm::vec3 nRotation);
  void rotate(float degrees, glm::vec3 nRotation);
  void setScale(glm::vec3 nScale);

  glm::mat4 modelMatrix();
  glm::mat4 projectModel(EngineCamera *camera);
  void bindUniform(GLuint program, std::string uniform, EngineCamera *camera);

  void updatePosition();
  void checkCollision();
};

#endif
