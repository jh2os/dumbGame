#include "Camera.h"

using namespace std;
EngineCamera::EngineCamera() {}

EngineCamera::EngineCamera(int resX, int resY) {
  projection = glm::perspective(glm::radians(45.0f), (float)resX/ resY, 0.1f, 100.f);
  
  position = glm::vec3(0.0f, 0.0f, 2.0f);
  origin = glm::vec3(0.0f, 0.0f, 0.0f);
  orientation = glm::vec3 (0,1,0);

  compileCamera();
}

void EngineCamera::compileCamera() {
  view = glm::lookAt(position, origin, orientation);
  mvp = projection * view;
}
void EngineCamera::setProjection(glm::mat4 nProjection) {
  projection = nProjection;
  mvp = projection * view;
}
void EngineCamera::setPosition(glm::vec3 nPosition) {
  position = nPosition;
  compileCamera();
}
void EngineCamera::setOrigin(glm::vec3 nOrigin) {
  origin = nOrigin;
  compileCamera();
}
void EngineCamera::setPositionAndOrigin(glm::vec3 nPosition, glm::vec3 nOrigin) {
  position = nPosition;
  origin = nOrigin;
  compileCamera();
}
void EngineCamera::setOrientation(glm::vec3 nOrientation) {
  orientation = nOrientation;
  compileCamera();
}
glm::mat4 EngineCamera::getMVP() {
  return mvp;
}

