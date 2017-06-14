#ifndef GAME1_H
#define GAME1_H

#include "wakeEngine/WakeEngine.h"
#include "wakeEngine/Camera.h"
#include "wakeEngine/Model.h"
#include "wakeEngine/Square.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "dungeon.h"
#include "entity.h"
#include "CollisionMap.hpp"
#include "Manager.hpp"

#if defined (__WIN32__)
#define DIR "../"
#else
#define DIR "./"
#endif

class Game1 : public Gamestate {

private:
  WakeEngine *e;
  unsigned int dungeonWidth;
  unsigned int dungeonHeight;
  int numberOfRooms;
  const int numOfEnemies = 200;
  float cameraOffsety;
  float cameraOffsetz;
  glm::vec3 cam1pos;
  glm::vec3 cam1ori;
  glm::vec3 lightPos;
  glm::vec4 lightDir;
  GLint lightPosLoc;
  GLint lightPosDir;
  EngineCamera camera1;
  Model models[2];
  unsigned int itemCount;
  unsigned int dirtCount;
  std::vector<GLfloat> instanceOffset;
  std::vector<GLfloat> dirtInstances;
  Entity player;
  std::vector<Entity> enemy;
  dungeon *dd;
  Square thebox;
  bool left;
  bool right;
  bool forward;
  bool backward;
  bool up;
  bool down;
  bool cameraBound;
  float camSpeed;
  vector<position> collisionQue;
  collisionMap map;
  glm::vec3 playerPos;

public:
  Game1();
  void init();
  void event(SDL_Event &ev);
  void logic();
  void render();
  void instanceModels(	dungeon *dd,
  											int w,
  											int h,
  											unsigned int &layer1Count,
  											unsigned int &layer2Count,
  											std::vector<GLfloat> &layer1,
  											std::vector<GLfloat> &layer2);

};

#endif
