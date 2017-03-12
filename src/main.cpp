// Program by Johnathan Waters (The Waters Guy)
// 2016
#define GL_FRAGMENT_PRECISION_HIGH 1

#include "wakeEngine/WakeEngine.h"
#include "wakeEngine/Camera.h"
#include "wakeEngine/Model.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "dungeon.h"

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
	glm::vec3 cam1pos = glm::vec3(0,20,15);
	glm::vec3 cam1ori = glm::vec3(0,0,0);
	camera1.setPositionAndOrigin(cam1pos,cam1ori);
	float adder = -4.0f;
	glm::vec3 lightPos = glm::vec3(50,-50,20);
	e->glh.useProgram("program");
	GLint lightPosLoc = glGetUniformLocation(e->glh.activeProgram, "lightPos");
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	Model models[1];
	//for(unsigned int i = 0; i < 10000; i++) {
	models[0] = Model();

	//float heightScale = 0.0f; //(rand() % 3) * 0.1;
	models[0].setScale(glm::vec3(1.f,1.0f,1.0f));
	models[1] = Model();
	models[1].setScale(glm::vec3(1.0, 1.0, 1.0));
	/*float varianceX = (rand() % 5) * 0.1;
	float varianceY = (rand() % 5) * 0.1;

	float nZ = 0.0f; //+ 1 * heightScale;*/
	unsigned int x = 0 % 100;
	unsigned int y = 0 / 100;
	float nY = (float)y ; //+ varianceX;
	float nX = (float)x;
	models[0].setPosition(glm::vec3(nX, 0.0, -nY));
		//models[i].rotate(-90, glm::vec3(1,0,0));

	//}


	// SETTING UP INSTANCING DATA9+
	int itemCount = 0;
	int dirtCount = 0;
	std::vector<GLfloat> instanceOffset;
	std::vector<GLfloat> dirtInstances;
	dungeon *dd = new dungeon(100, 100, 0, 15, 15, 60);
	for(unsigned int i = 0; i < 10000 ; i++) {
		if(dd->tiles[i].type != FLOOR) {
			itemCount++;
			unsigned int x = i % 100;
			unsigned int y = i / 100;
			float nY = (float)y; //+ varianceX;
			float nX = (float)x;
			instanceOffset.push_back(nX);
			instanceOffset.push_back(0.0f);
			instanceOffset.push_back(-nY);

		} else if ( dd->tiles[i].type == FLOOR) {
			dirtCount++;
			unsigned int x = i % 100;
			unsigned int y = i / 100;
			float nY = (float)y; //+ varianceX;
			float nX = (float)x;
			dirtInstances.push_back(nX);
			dirtInstances.push_back(0.0f);
			dirtInstances.push_back(-nY);
		}
	}
	e->audio.loadSound("jump", "res/audio/sounds/jump.wav");
	e->audio.loadMusic("song", "res/audio/music/indianaJones.mp3");
	e->mesh["dirt"] = new Mesh("res/meshes/dirt", "dirt.dae");
	e->mesh["dirt"]->instance(dirtInstances);
	e->mesh["tree"] = new Mesh("res/meshes/tree" , "tree.dae");
	e->mesh["tree"]->instance(instanceOffset);


	// Game loop
	//  > Handle Input
	//	> Pause tickcount for logic and render
	//	> Movement
	//	> Collision
	//	> Logic (Collision / Map Events / Setting Flags)
	//	> Update Positions from Logic
	//	> Render

	// Main Loop =================================================================
	//float jumpspeed = 0.10;
	bool running = true;
	SDL_Event ev;
	unsigned int fpsRate = 1000 / 30;
	unsigned int targetFrame = SDL_GetTicks() + fpsRate;
	bool left;
	bool right;
	bool forward;
	bool backward;
	bool up;
	bool down;
	float camSpeed = 0.5f;
	while(running) {
		while(SDL_PollEvent(&ev)) {
				if(ev.type == SDL_QUIT) {
					running = false;
				}
				if(ev.type == SDL_KEYDOWN) {
					switch(ev.key.keysym.sym) {
						case SDLK_ESCAPE: {
							running = false;
						}
						case SDLK_w: {
							backward = false;
							forward = true;
							break;
						}
						case SDLK_s: {
							backward = true;
							forward = false;
							break;
						}
						case SDLK_a: {
							left = true;
							right = false;
							break;
						}
						case SDLK_d: {
							right = true;
							left = false;
							break;
						}
						case SDLK_SPACE: {
							up = true;
							down = false;
							break;
						}
						case SDLK_LSHIFT: {
							up = false;
							down = true;
							break;
						}
						default:
							break;
					}

				}
				if(ev.type == SDL_KEYUP) {
					switch(ev.key.keysym.sym) {
						case SDLK_w: {
							forward = false;
							break;
						}
						case SDLK_s: {
							backward = false;
							break;
						}
						case SDLK_a: {
							left = false;
							break;
						}
						case SDLK_d: {
							right = false;
							break;
						}
						case SDLK_SPACE: {
							up = false;
							break;
						}
						case SDLK_LSHIFT: {
							down = false;
							break;
						}

						default:
							break;
					}
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
		if ( SDL_GetTicks() >= targetFrame) {

			if (lightPos.x <= -30.0 || lightPos.x >= 130.0f) {
				adder = adder * -1;
			}

			if(left) {
				cam1pos.x -= camSpeed;
				cam1ori.x -= camSpeed;
			}
			if(right) {
				cam1pos.x += camSpeed;
				cam1ori.x += camSpeed;
			}
			if(forward) {
				cam1pos.z -= camSpeed;
				cam1ori.z -= camSpeed;
			}
			if(backward) {
				cam1pos.z += camSpeed;
				cam1ori.z += camSpeed;
			}
			if(up) {
				cam1pos.y += camSpeed;
				cam1ori.y += camSpeed;
			}
			if(down) {
				cam1pos.y -= camSpeed;
				cam1ori.y -= camSpeed;
			}

			lightPos.x = lightPos.x + adder;




		//================================================

		// Collision detection ===========================
		//pModel.checkCollision();
		//================================================

		// Update Render models ==========================
		//e->glh.useProgram("program");
		//pModel.bindUniform(e->glh.activeProgram, "MVP", &camera1);
		//================================================

		// Render things =================================
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

			//std::cout << SDL_GetTicks() - targetFrame << "\t" << SDL_GetTicks() << "\t" << targetFrame << std::endl;
			camera1.setPositionAndOrigin(cam1pos,cam1ori);
			targetFrame += fpsRate;
			glClearColor(0.7,0.7,1.0,1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





			e->glh.useProgram("program");
			glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
			models[0].bindUniform(e->glh.activeProgram, "MVP", &camera1);
			e->mesh["tree"]->renderInstanced(e->glh.activeProgram, "texUnit", itemCount);


			e->glh.useProgram("program");
			glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
			models[1].bindUniform(e->glh.activeProgram, "MVP", &camera1);
			e->mesh["dirt"]->renderInstanced(e->glh.activeProgram, "texUnit", dirtCount + 1);
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
