#include "Logger.h"
#include "Timer.h"


Timer* Timer::m_pInstance = NULL;

Timer* Timer::Instance() {
	if(!m_pInstance)
		m_pInstance = new Timer;
	return m_pInstance;
}

float Timer::newLoop() {
  this->lastTick = this->newTick;
  this->newTick = SDL_GetTicks();
  this->tickRate = (this->newTick - this->lastTick) / 1000.0f;
}

float Timer::getTickRate() {
  return this->tickRate;
}
