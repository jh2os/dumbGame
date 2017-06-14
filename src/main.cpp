// Program by Johnathan Waters (The Waters Guy)
// 2016
#define SDL_MAIN_HANDLED
#define GL_FRAGMENT_PRECISION_HIGH 1
#define _WIN32_WINNT 0x0502

#include "wakeEngine/WakeEngine.h"
#include "wakeEngine/Camera.h"
#include "wakeEngine/Model.h"
#include "wakeEngine/Square.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "dungeon.h"
#include "entity.h"
#include "Manager.hpp"
#include "Game1.h"

#if defined (__WIN32__)
#define DIR "../"
#else
#define DIR "./"
#endif
using namespace std;

void createShaders(WakeEngine *e);
const int JOYSTICK_DEAD_ZONE = 8000;

int main( int argc, char *argv[]) {

  WakeEngine *e = WakeEngine::Instance();
	e->init(DIR"settings.conf");
	GamestateManager manager;
	createShaders(e);

	manager.states["game1"] = new Game1();
	manager.setState("game1");
	manager.state->init();

	bool running = true;
	SDL_Event ev;
	unsigned int fpsRate = 1000 / 30;
	unsigned int targetFrame = SDL_GetTicks() + fpsRate;

	while(running) {
		while(SDL_PollEvent(&ev)) {
			if(ev.type == SDL_QUIT || (ev.type == SDL_KEYDOWN && e->getKeyCommand(ev.key.keysym.sym) == "quit")) {
				running = false;
			}

			manager.state->event(ev);

		}

		Timer::Instance()->newLoop();
		if ( SDL_GetTicks() >= targetFrame) {
			targetFrame += fpsRate;
			manager.state->logic();
			manager.state->render();
			SDL_GL_SwapWindow(e->window);
		}

	}

	e->shutdown();

	return 0;
}

void createShaders(WakeEngine *e) {
	//Load in all OpenGL shaders for the program
	e->glh.createProgram("program");
	e->glh.loadShader("frag",DIR"res/shaders/simpleShader.frag",GL_FRAGMENT_SHADER);
	e->glh.loadShader("vert",DIR"res/shaders/simpleShader.vert",GL_VERTEX_SHADER);
	e->glh.attachShader("program", "vert");
	e->glh.attachShader("program", "frag");
	e->glh.linkProgram("program");
	//std::cout << "created shaders" << std::endl;
	e->glh.createProgram("text");
	e->glh.loadShader("frag",DIR"res/shaders/text.frag",GL_FRAGMENT_SHADER);
	e->glh.loadShader("vert",DIR"res/shaders/text.vert",GL_VERTEX_SHADER);
	e->glh.attachShader("text", "vert");
	e->glh.attachShader("text", "frag");
	e->glh.linkProgram("text");

	e->glh.createProgram("square");
	e->glh.loadShader("frag",DIR"res/shaders/square.frag",GL_FRAGMENT_SHADER);
	e->glh.loadShader("vert",DIR"res/shaders/square.vert",GL_VERTEX_SHADER);
	e->glh.attachShader("square", "vert");
	e->glh.attachShader("square", "frag");
	e->glh.linkProgram("square");

}
