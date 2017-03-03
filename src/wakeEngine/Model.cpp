#include "Model.h"

using namespace std;

Model::Model() {
  modelTransform = glm::mat4(1.0f);
  rotationModel = glm::mat4(1.0f);
  position = glm::vec3(0.0f, 0.0f, 0.0f);
  newPosition = position;
  rotation = 0.0f;
  rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
  modelScale = glm::vec3(1.0f, 1.0f, 1.0f);
  physics = false;
}

glm::vec3 Model::getPosition() {
  return position;
}
void Model::setPosition(glm::vec3 nPosition) {
  position = nPosition;
  newPosition = position;
  //cout << "x: " << position.x << "\ty: " << position.y << endl;
}

void Model::setRotationa(float ndegrees, glm::vec3 nRotation) {
  rotation = ndegrees;
  rotationAxis = nRotation;
}

void Model::rotate(float ndegrees, glm::vec3 nRotation) {
  rotation = ndegrees;
  rotationAxis = nRotation;
  this->rotationModel = glm::rotate(this->rotationModel, glm::radians(rotation), glm::vec3(rotationAxis.x, rotationAxis.y, rotationAxis.z) );
  //glm::rotate(&this->rotationModel, glm::radians(rotation), glm::vec3(rotationAxis.x, rotationAxis.y, rotationAxis.z));
}

void Model::setScale(glm::vec3 nScale) {
  modelScale = nScale;
}

glm::mat4 Model::modelMatrix() {
  //glm::mat4 o = glm::mat4(1.0f);
  glm::mat4 trans = glm::translate(glm::vec3(position.x, position.y, position.z));
  //glm::mat4 rotatem = this->rotationAxis;
  //glm::mat4 rotatem = glm::rotate(glm::radians(rotation), glm::vec3(rotationAxis.x, rotationAxis.y, rotationAxis.z));
  glm::mat4 scale = glm::scale(glm::vec3(modelScale.x, modelScale.y, modelScale.z));
  modelTransform = trans *  this->rotationModel * scale;
  return modelTransform;
}

glm::mat4 Model::projectModel(EngineCamera *camera) {
  glm::mat4 mvp = camera->getMVP();
  glm::mat4 model = modelMatrix();
  return mvp * model;
}

void Model::bindUniform(GLuint program, string uniform, EngineCamera *camera) {
  GLuint MatrixID = glGetUniformLocation(program, uniform.c_str());
  glm::mat4 mvp = camera->getMVP();
  glm::mat4 model = modelMatrix();
  mvp = mvp * model;
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
}

void Model::updatePosition() {
  if (physics) {
    glm::vec3 translate = this->applyGravity(4.9f);
    /*std::cout << "Original: " << this->position.x << ", "
              << this->position.y << ", " << this->position.z << std::endl;
    std::cout << "Translate: " << translate.x << ", " << translate.y << ", "
              << translate.z << std::endl;*/
    this->newPosition.x += translate.x;
    this->newPosition.y += translate.y;
    this->newPosition.z += translate.z;
  }
}

void Model::checkCollision() {
  position = newPosition;
}
