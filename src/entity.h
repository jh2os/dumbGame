#ifndef ENTITY_H
#define ENTITY_H

#include "wakeEngine/Model.h"


#define PI 3.14159265

class Entity {

public:
  Entity();
  Model model;
  int playerX;
  int playerY;
  //movement booleans
  bool left;
  bool right;
  bool up;
  bool down;
  bool moving;
  int direction;
  float moveVar;
  unsigned int startMoveTime;
  glm::vec3 startMovePos;
  void move();
};

#endif