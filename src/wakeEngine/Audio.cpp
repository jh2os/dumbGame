#include "Audio.h"

EngineAudio::EngineAudio() {

  masterVolume = MIX_MAX_VOLUME;
  soundVolume = masterVolume;
  musicVolume = masterVolume;

  Logger::Instance()->writeLine("Initializing SDL Mixing system");
  int initFlags= MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
  int init = Mix_Init(initFlags);

  if ( (init&initFlags) != initFlags) {
    Logger::Instance()->writeLine("Mix_Init Error: Failed to get required support");
    Logger::Instance()->writeLine("Mix_Init Error: ", Mix_GetError());
  }

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1 ) {
    Logger::Instance()->writeLine("Mix_OpenAudio Error:", Mix_GetError());
  }

}

void EngineAudio::loadSound(std::string key, std::string file) {
  this->sound[key] = Mix_LoadWAV(file.c_str());
  if (!this->sound[key]) {
    Logger::Instance()->writeLine("Failed to load in audio \"",key,"\": ", file);
    Logger::Instance()->writeLine("SDL_Mixer Error: ", Mix_GetError());
  }
}

void EngineAudio::loadMusic(std::string key, std::string file) {
  this->music[key] = Mix_LoadMUS(file.c_str());
  if(!this->music[key]) {
    Logger::Instance()->writeLine("Failed to load in music \"",key,"\": ", file);
    Logger::Instance()->writeLine("SDL_Mixer Error: ", Mix_GetError());
  }
}

void EngineAudio::close() {

  std::map<std::string, Mix_Chunk*>::iterator i = this->sound.begin();
  for(;i!=this->sound.end(); ++i) {
    Mix_FreeChunk(this->sound[i->first]);
    this->sound[i->first] = NULL;
  }

  std::map<std::string, Mix_Music*>::iterator j = this->music.begin();
  for(;j!=this->music.end(); ++j) {
    Mix_FreeMusic(this->music[j->first]);
    this->music[j->first] = NULL;
  }
}
