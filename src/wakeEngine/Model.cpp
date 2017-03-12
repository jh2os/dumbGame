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
  //GLuint MatrixID = glGetUniformLocation(program, uniform.c_str());
  //GLuint ModelID = glGetUniformLocation(program, "Model");
  //GLuint ViewID = glGetUniformLocation(program, "View");
  //GLuint ProjectionID = glGetUniformLocation(program, "Projection");
  //glm::mat4 mvp = camera->getMVP();
  glm::mat4 model = modelMatrix();
  glm::mat4 view = camera->getView();
  glm::mat4 projection = camera->getProjection();
  GLuint mid = getUniform(program, 0);
  GLuint vid = getUniform(program, 1);
  GLuint pid = getUniform(program, 2);
  //mvp = mvp * model;
  //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
  glUniformMatrix4fv(mid, 1, GL_FALSE, &model[0][0]);
  glUniformMatrix4fv(vid, 1, GL_FALSE, &view[0][0]);
  glUniformMatrix4fv(pid, 1, GL_FALSE, &projection[0][0]);

}

GLuint Model::getUniform(GLuint program, int typeofu) {
  if (uniforms[program].ModelID == 0 && uniforms[program].ViewID == 0 && uniforms[program].ProjectionID == 0 ) {
    //std::cout << "In here, program: " << program << "\ttype: " << typeofu << std::endl;
    uniforms[program].ModelID = glGetUniformLocation(program, "Model");
    uniforms[program].ViewID = glGetUniformLocation(program, "View");
    uniforms[program].ProjectionID = glGetUniformLocation(program, "Projection");
  }
  switch (typeofu) {
    case 0:
      return uniforms[program].ModelID;
      break;
    case 1:
      return uniforms[program].ViewID;
      break;
    case 2:
      return uniforms[program].ProjectionID;
      break;
  }
  return -1;
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
