#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <map>
#include <vector>
#include <SDL2/SDL.h>

class Timer {
// Singlton Stuff Just ignore
public:
	static Timer* Instance();
private:
	Timer() {lastTick = SDL_GetTicks(); newTick = SDL_GetTicks();};
	Timer(Timer const&){lastTick = SDL_GetTicks(); newTick = SDL_GetTicks();};
	static Timer* m_pInstance;

// Class things
public:
  float newLoop();
  float getTickRate();

private:
  unsigned int lastTick;
  unsigned int newTick;
  float tickRate;
};

#endif
