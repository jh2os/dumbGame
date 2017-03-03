#ifndef WAKEENGINE_H
#define WAKEENGINE_H

#include "includes.h"
#include "Mesh.h"
#include "glHelper.h"
#include "Audio.h"

class WakeEngine {
// Singlton Stuff Just ignore
public:
	static WakeEngine* Instance();
private:
	WakeEngine() {};
	WakeEngine(WakeEngine const&){};
	static WakeEngine* m_pInstance;

public:
	// Begin class stuff
	Logger* log;
	Settings* settings;
	SDL_Window * window;
	SDL_GLContext gl;
	glHelper glh;
	EngineAudio audio;
	void init(std::string settingsFile);
	void shutdown();
	std::map<std::string, Mesh*> mesh;
};

#endif
