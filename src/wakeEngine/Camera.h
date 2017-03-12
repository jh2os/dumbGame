#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class EngineCamera {
 private:
  glm::mat4 projection;
  glm::mat4 view;
  glm::mat4 mvp;
  glm::vec3 position;
  glm::vec3 origin;
  glm::vec3 orientation;
  void compileCamera();

 public:
  EngineCamera();
  EngineCamera(int resX, int resY);
  void setProjection(glm::mat4 nProjection);
  void setPosition(glm::vec3 nPosition);
  void setOrigin(glm::vec3 nOrigin);
  void setPositionAndOrigin(glm::vec3 nPosition, glm::vec3 nOrigin);
  void setOrientation(glm::vec3 nOrientation);
  glm::mat4 getProjection();
  glm::mat4 getView();
  glm::mat4 getMVP();

};


#endif
