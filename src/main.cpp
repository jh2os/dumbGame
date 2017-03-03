// Program by Johnathan Waters (The Waters Guy)
// 2016
#define GL_FRAGMENT_PRECISION_HIGH 1

#include "wakeEngine/WakeEngine.h"
#include "wakeEngine/Camera.h"
#include "wakeEngine/Model.h"
#include <iostream>
using namespace std;

void createShaders(WakeEngine *e);

struct entity {
	Model m;

};

int main() {

	// Create our window
	WakeEngine *e = WakeEngine::Instance();
	e->init("settings.conf");
	createShaders(e);

	//gamestate("titleScreen");
	// Set up views
	EngineCamera camera1(e->settings->i("resX"), e->settings->i("resY"));
	camera1.setPositionAndOrigin(
		glm::vec3(0,0,20),
		glm::vec3(0,0,0)
	);

	e->audio.loadSound("jump", "res/audio/sounds/jump.wav");
	e->audio.loadMusic("song", "res/audio/music/indianaJones.mp3");
	e->mesh["whale"] = new Mesh("res/meshes/bat", "batman.dae");
	e->mesh["dwarf"] = new Mesh("res/meshes/tree" , "tree.dae");
	Model pModel;
	pModel.physics = true;
	pModel.setPosition(glm::vec3(0.0, 0.0, 0.0));
	pModel.rotate(-90, glm::vec3(1,0,0));
	pModel.verticalSpeed = 0.01;
	//Mix_PlayMusic(e->audio.music["song"], -1);

	Model pModel2;
	pModel2.setPosition(glm::vec3(0.0, 0.0, 0.0));
	pModel2.rotate(-90, glm::vec3(1,0,0));
	pModel2.setScale(glm::vec3(1.0,1.0,1.0));
	// Game loop
	//  > Handle Input
	//	> Pause tickcount for logic and render
	//	> Movement
	//	> Collision
	//	> Logic (Collision / Map Events / Setting Flags)
	//	> Update Positions from Logic
	//	> Render

	// Main Loop =================================================================
	float jumpspeed = 0.10;
	bool running = true;
	SDL_Event ev;
	while(running) {
		while(SDL_PollEvent(&ev)) {
				if(ev.type == SDL_QUIT) {
					running = false;
				}
		}

		Timer::Instance()->newLoop();

		pModel2.rotate(-0.1, glm::vec3(0,0,1));
		// Movement ======================================
		pModel.rotate(-1, glm::vec3(0,0,1));
		if (pModel.getPosition().y <=	 0.0f) {
			pModel.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
			jumpspeed = (jumpspeed >= 1.0) ? 1.0 : jumpspeed + 0.2;
			pModel.verticalSpeed = jumpspeed;
			//std::cout << jumpspeed << std::endl;
			//Mix_PlayChannel(-1, e->audio.sound["jump"], 0);
		}
		pModel.updatePosition();
		//================================================

		// Collision detection ===========================
		pModel.checkCollision();
		//================================================

		// Update Render models ==========================
		//e->glh.useProgram("program");
		//pModel.bindUniform(e->glh.activeProgram, "MVP", &camera1);
		glUseProgram(0);
		//================================================

		// Render things =================================
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glClearColor(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		e->glh.useProgram("program");
		pModel.bindUniform(e->glh.activeProgram, "MVP", &camera1);
		e->mesh["whale"]->render(e->glh.activeProgram, "texUnit");

		e->glh.useProgram("program");
		pModel2.bindUniform(e->glh.activeProgram, "MVP", &camera1);
		e->mesh["dwarf"]->render(e->glh.activeProgram, "texUnit");
		SDL_GL_SwapWindow(e->window);
		//================================================
	}
	// End Game Loop =============================================================

	// Shut down program
	e->shutdown();

	return 0;
}

void createShaders(WakeEngine *e) {
	//Load in all OpenGL shaders for the program
	e->glh.createProgram("program");
	e->glh.loadShader("frag","res/shaders/simpleShader.frag",GL_FRAGMENT_SHADER);
	e->glh.loadShader("vert","res/shaders/simpleShader.vert",GL_VERTEX_SHADER);
	e->glh.attachShader("program", "vert");
	e->glh.attachShader("program", "frag");
	e->glh.linkProgram("program");
}
