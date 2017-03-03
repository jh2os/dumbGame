#ifndef PHYSICSMODEL_H
#define PHYSICSMODEL_H

#include "includes.h"

struct PhysicsSettings {
  float gravity;
};

class PhysicsModel {
public:
  PhysicsModel();

  glm::vec2 velocityDirection;
  float speed;

  float verticalSpeed;
  float verticalVelocity;

  glm::vec3 rotationalDirection;
  float rotationalSpeed;
  glm::vec3 applyGravity(float gravity);
  glm::vec3 applyMovement(float acceleration);
};

#endif
