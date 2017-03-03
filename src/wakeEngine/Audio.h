#ifndef AUDIO_H
#define AUDIO_H

#include "includes.h"
#include <SDL2/SDL_mixer.h>

class EngineAudio {
private:
  int masterVolume;
  int soundVolume;
  int musicVolume;
public:
  EngineAudio();
  std::map<std::string, Mix_Chunk *> sound;
  std::map<std::string, Mix_Music *> music;
  void loadSound(std::string key, std::string file);
  void loadMusic(std::string key, std::string file);
  void close();
};


#endif
