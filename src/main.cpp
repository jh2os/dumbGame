// Program by Johnathan Waters (The Waters Guy)
// 2016
#define GL_FRAGMENT_PRECISION_HIGH 1

#include "wakeEngine/WakeEngine.h"
#include "wakeEngine/Camera.h"
#include "wakeEngine/Model.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

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
	srand (time(NULL));

	//gamestate("titleScreen");
	// Set up views
	EngineCamera camera1(e->settings->i("resX"), e->settings->i("resY"));
	glm::vec3 cam1pos = glm::vec3(52.5,5,20);
	glm::vec3 cam1ori = glm::vec3(50,0,-50);
	camera1.setPositionAndOrigin(cam1pos,cam1ori);
	float adder = -4.0f;
	glm::vec3 lightPos = glm::vec3(50,-50,20);
	GLint lightPosLoc = glGetUniformLocation(e->glh.activeProgram, "lightPos");
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

	Model models[10000];
	for(unsigned int i = 0; i < 10000; i++) {
		models[i] = Model();
		models[i].setScale(glm::vec3(0.3,0.3,0.3));
		unsigned int x = i % 100;
		unsigned int y = i / 100;
		float nY = (float)y;
		float nX = (float)x;
		if (y % 2 == 1) {
			nX = (float)x;//+ 0.5f;
		} else
			nX = (float)x;
		models[i].setPosition(glm::vec3(nX, 0.0f, -nY));
		models[i].rotate(-90, glm::vec3(1,0,0));
	}

	e->audio.loadSound("jump", "res/audio/sounds/jump.wav");
	e->audio.loadMusic("song", "res/audio/music/indianaJones.mp3");
	e->mesh["whale"] = new Mesh("res/meshes/bat", "batman.dae");
	e->mesh["dwarf"] = new Mesh("res/meshes/tree" , "tree.dae");

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
	unsigned int fpsRate = 1000 / 60;
	unsigned int targetFrame = SDL_GetTicks() + fpsRate;
	while(running) {
		while(SDL_PollEvent(&ev)) {
				if(ev.type == SDL_QUIT) {
					running = false;
				}
		}

		Timer::Instance()->newLoop();

		//pModel2.rotate(-0.1, glm::vec3(0,0,1));
		// Movement ======================================
		//pModel.rotate(-1, glm::vec3(0,0,1));
		/*if (pModel.getPosition().y <=	 0.0f) {
			pModel.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
			jumpspeed = (jumpspeed >= 1.0) ? 1.0 : jumpspeed + 0.2;
			pModel.verticalSpeed = jumpspeed;
			//std::cout << jumpspeed << std::endl;
			//Mix_PlayChannel(-1, e->audio.sound["jump"], 0);
		}*/
		//pModel.updatePosition();

		if (lightPos.x <= -30.0 || lightPos.x >= 130.0f) {
			adder = adder * -1;
		}
		lightPos.x = lightPos.x + adder;
		cam1pos.x = cam1pos.x + (adder * 0.05f);
		camera1.setPositionAndOrigin(cam1pos,cam1ori);

		//================================================

		// Collision detection ===========================
		//pModel.checkCollision();
		//================================================

		// Update Render models ==========================
		//e->glh.useProgram("program");
		//pModel.bindUniform(e->glh.activeProgram, "MVP", &camera1);
		glUseProgram(0);
		//================================================

		// Render things =================================
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		if ( SDL_GetTicks() >= targetFrame) {
			targetFrame += fpsRate;
			glClearColor(1,1,1,1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for(unsigned int i = 0; i < 10000; i++) {
				e->glh.useProgram("program");
				GLint lightPosLoc = glGetUniformLocation(e->glh.activeProgram, "lightPos");
				glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
				models[i].bindUniform(e->glh.activeProgram, "MVP", &camera1);
				int test = rand() % 8 + 1;
				if (test == 1) {
					e->mesh["dwarf"]->render(e->glh.activeProgram, "texUnit");
				}
			}
			SDL_GL_SwapWindow(e->window);
		}
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
