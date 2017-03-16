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
#include "entity.h"

using namespace std;

void createShaders(WakeEngine *e);

struct entity {
	Model m;

};
const int JOYSTICK_DEAD_ZONE = 8000;
int main() {

	// Create our window
	WakeEngine *e = WakeEngine::Instance();
	e->init("settings.conf");
	createShaders(e);
	srand (time(NULL));

	unsigned int dungeonWidth = 100;
	unsigned int dungeonHeight = 100;
	int numberOfRooms = 50;
	const int numOfEnemies = 200;

	//gamestate("titleScreen");
	// Set up views
	EngineCamera camera1(e->settings->i("resX"), e->settings->i("resY"));
	glm::vec3 cam1pos = glm::vec3(0,20,15);
	glm::vec3 cam1ori = glm::vec3(0,0,0);
	camera1.setPositionAndOrigin(cam1pos,cam1ori);
	float cameraOffsety = 10;
	float cameraOffsetz = 5;

	float adder = -0.01f;
	glm::vec3 lightPos = glm::vec3(50,-50,20);

	e->glh.useProgram("program");
	GLint lightPosLoc = glGetUniformLocation(e->glh.activeProgram, "lightPos");
	glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

	Model models[2];
	//for(unsigned int i = 0; i < 10000; i++) {
	models[0] = Model();
	models[0].setScale(glm::vec3(1.f,1.0f,1.0f));

	models[1] = Model();
	models[1].setScale(glm::vec3(1.0, 1.0, 1.0));

	Entity player;
	player.playerX = 0;
	player.playerY = dungeonHeight / 2;
	player.model.setScale(glm::vec3(1, 1, 1));
	player.model.setPosition(glm::vec3(0.0, 0, -(dungeonHeight / 2.0) + 0.5));
	player.model.rotate(-20, glm::vec3(1,0,0));

	Entity enemy[numOfEnemies];
	for (int i = 0; i < numOfEnemies; i++)
		enemy[i].model.rotate(-20, glm::vec3(1,0,0));

	//float nZ = 0.0f; //+ 1 * heightScale;*/
	models[0].setPosition(glm::vec3(0.0, 0.0, 0.0));

	// SETTING UP INSTANCING DATA9+
	int itemCount = 0;
	int dirtCount = 0;
	std::vector<GLfloat> instanceOffset;
	std::vector<GLfloat> dirtInstances;
	dungeon *dd = new dungeon(dungeonWidth, dungeonHeight, 0, 10, 10, numberOfRooms);
	//dd->display();
	for(unsigned int i = 0; i < dungeonWidth * dungeonHeight ; i++) {
		if(dd->tiles[i].type != FLOOR) {
			itemCount++;
			unsigned int x = i % dungeonWidth;
			unsigned int y = i / dungeonHeight;
			float nY = (float)y; //+ varianceX;
			float nX = (float)x;
			instanceOffset.push_back(nX);
			instanceOffset.push_back(0.0f);
			instanceOffset.push_back(-nY);

		} else if ( dd->tiles[i].type == FLOOR) {
			dirtCount++;
			unsigned int x = i % dungeonWidth;
			unsigned int y = i / dungeonHeight;
			float nY = (float)y; //+ varianceX;
			float nX = (float)x;
			dirtInstances.push_back(nX);
			dirtInstances.push_back(0.0f);
			dirtInstances.push_back(-nY);
		}
	}

	for (int i = 0; i < numOfEnemies; i++) {
		while (enemy[i].playerX == 0) {
			//std::cout << "here" << std::endl;
			int x = rand() % dungeonWidth;
			int y = rand() % dungeonHeight;
			if ( dd->getTile(x, y) == 1) {
				enemy[i].playerX = x;
				enemy[i].playerY = y;
				enemy[i].model.setPosition(glm::vec3(x, 0.0, -y + 0.5f));
				//std::cout << std::endl << enemy.playerX << "," << enemy.playerY << std::endl;
			}
		}
	}
	e->audio.loadSound("jump", "res/audio/sounds/jump.wav");
	e->audio.loadMusic("song", "res/audio/music/indianaJones.mp3");
	e->mesh["dirt"] = new Mesh("res/meshes/dirt", "dirt.dae");
	e->mesh["dirt"]->instance(dirtInstances);
	e->mesh["tree"] = new Mesh("res/meshes/tree" , "tree.dae");
	e->mesh["tree"]->instance(instanceOffset);
	e->mesh["mom"] = new Mesh("res/meshes/mom", "mom.dae");
	e->mesh["batman"] = new Mesh("res/meshes/bat", "batman.dae");

	//Mix_PlayMusic(e->audio.music["song"], 1);
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
						case SDLK_RIGHT: {
							player.up = false;
							player.down = false;
							player.right = true;
							player.left = false;
							break;
						}
						case SDLK_LEFT: {
							player.up = false;
							player.down = false;
							player.right = false;
							player.left = true;
							break;
						}
						case SDLK_UP:{
							player.up = true;
							player.down = false;
							player.right = false;
							player.left = false;
							break;
						}
						case SDLK_DOWN: {
							player.up = false;
							player.down = true;
							player.right = false;
							player.left = false;
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
						case SDLK_RIGHT: {
							player.right = false;
							break;
						}
						case SDLK_LEFT: {
							player.left = false;
							break;
						}
						case SDLK_UP:{
							player.up = false;
							break;
						}
						case SDLK_DOWN: {
							player.down = false;
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
			if (player.up) {
					player.up = (dd->getTile(player.playerX, player.playerY + 1) == 1) ? true : false;
			}
			if (player.right){
				player.right = (dd->getTile(player.playerX + 1, player.playerY) == 1) ? true : false;
			}
			if (player.down){
				player.down = (dd->getTile(player.playerX, player.playerY - 1) == 1) ? true : false;
			}
			if (player.left){
				player.left = (dd->getTile(player.playerX - 1, player.playerY) == 1) ? true : false;
			}
			//std::cout << dd->getTile(player.playerX, player.playerY - 1) << std::endl;
			if(true/*(player.up || player.right || player.down || player.left) && !player.moving*/){
				for (int i = 0; i < numOfEnemies; i++){
					while(!enemy[i].up && !enemy[i].down && !enemy[i].left && !enemy[i].right) {
						int direction = (rand() % 4) + 1;
						switch(direction){
							case 1:
								enemy[i].up = (dd->getTile(enemy[i].playerX, enemy[i].playerY + 1) == 1) ? true : false;
								break;
							case 2:
								enemy[i].right = (dd->getTile(enemy[i].playerX + 1, enemy[i].playerY) == 1) ? true : false;
								break;
							case 3:
								enemy[i].down = (dd->getTile(enemy[i].playerX, enemy[i].playerY - 1) == 1) ? true : false;
								break;
							case 4:
								enemy[i].left = (dd->getTile(enemy[i].playerX - 1, enemy[i].playerY) == 1) ? true : false;
								break;
							case 0:
								break;
							}
						}
						//enemy[i].move();

					}
			}
			player.move();
			for (int i = 0; i < numOfEnemies; i++){
				enemy[i].move();
				enemy[i].up = enemy[i].down = enemy[i].left = enemy[i].right = false;
			}

			glm::vec3 playerPos = player.model.getPosition();
			cam1ori = playerPos;
			cam1ori.y = 0;
			cam1pos.x = playerPos.x;
			cam1pos.y = /*playerPos.y +*/ cameraOffsety;
			cam1pos.z = playerPos.z + cameraOffsetz;



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
			glClearColor(0.0,0.0,0.0,1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





			e->glh.useProgram("program");
			glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
			models[0].bindUniform(e->glh.activeProgram, "MVP", &camera1);
			e->mesh["tree"]->renderInstanced(e->glh.activeProgram, "texUnit", itemCount);

			e->glh.useProgram("program");
			glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
			models[1].bindUniform(e->glh.activeProgram, "MVP", &camera1);
			e->mesh["dirt"]->renderInstanced(e->glh.activeProgram, "texUnit", dirtCount + 1);

			e->glh.useProgram("program");
			glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
			player.model.bindUniform(e->glh.activeProgram, "MVP", &camera1);
			e->mesh["mom"]->render(e->glh.activeProgram, "texUnit");

			for (int i = 0; i < numOfEnemies; i++) {
				e->glh.useProgram("program");
				glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
				enemy[i].model.bindUniform(e->glh.activeProgram, "MVP", &camera1);
				e->mesh["tree"]->render(e->glh.activeProgram, "texUnit");
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
