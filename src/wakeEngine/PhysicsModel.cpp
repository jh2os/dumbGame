#include "PhysicsModel.h"
#include "Timer.h"
#include <iostream>

PhysicsModel::PhysicsModel() {
  this->verticalSpeed = 0.0f;
  this->speed = 0.0f;
}
glm::vec3 PhysicsModel::applyGravity(float gravity) {
  //std::cout << gravity << ":" << Timer::Instance()->getTickRate() << std::endl;
  this->verticalSpeed += -(gravity * Timer::Instance()->getTickRate());
  //std::cout << gravity << ":" << Timer::Instance()->getTickRate() << ":" << this->verticalSpeed << std::endl;
  return glm::vec3(0,this->verticalSpeed,0);
}
