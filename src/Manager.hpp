#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <map>
#include <SDL2/SDL.h>

class Gamestate {
public:
  virtual void init() {}
  virtual void event(SDL_Event &ev) {}
  virtual void logic() {}
  virtual void render() {}
};

struct GamestateManager {
  std::map<std::string, Gamestate*> states;
  Gamestate *state;

  void setState(std::string nstate) {
    state = states[nstate];
  }



};

#endif
