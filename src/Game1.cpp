  #include "Game1.h"

  Game1::Game1() {

  }

  void Game1::init() {
    e = WakeEngine::Instance();
    dungeonWidth = 100;
    dungeonHeight = 100;
    numberOfRooms = 50;
    //numOfEnemies = 200;
    cameraOffsety = 10;
    cameraOffsetz = 5;
    cam1pos = glm::vec3(0,0,0);
    cam1ori = glm::vec3(0,0,0);
    lightPos = glm::vec3(50,-50,20);
    lightDir = glm::vec4(0,0,0,0);
    lightPosLoc = 0;
    lightPosDir = 0;
    camera1 = EngineCamera(e->settings->i("resX"), e->settings->i("resY"));
    itemCount = 0;
  	dirtCount = 0;
    dd = NULL;

    e->glh.useProgram("program");
  	lightPosLoc = glGetUniformLocation(e->glh.activeProgram, "lightPos");
  	lightPosDir = glGetUniformLocation(e->glh.activeProgram, "lightDir");

  	models[0] = Model();
  	models[0].setScale(glm::vec3(1.0f, 1.0f, 1.0f));
  	models[1] = Model();
  	models[1].setScale(glm::vec3(1.0f, 1.0f, 1.0f));

  	player.playerX = 0;
  	player.playerY = dungeonHeight / 2;
  	player.model.setScale(glm::vec3(0.8f, 1, 1));
  	player.model.setPosition(glm::vec3(0.0, 0, -(dungeonHeight / 2.0) + 0.5));
  	player.model.rotate(-20, glm::vec3(1,0,0));

  	for (int i = 0; i < numOfEnemies; i++){
      enemy.push_back(Entity());
  		enemy[i].model.rotate(-20, glm::vec3(1,0,0));
  		enemy[i].model.setScale(glm::vec3(0.8f,1.0f, 1.0f));
  	}

    left = false;
    right = false;
    forward = false;
    backward = false;
    up = false;
    down = false;
    cameraBound = true;
    playerPos = player.model.getPosition();

    // SETTING UP INSTANCING DATA9+
    dd = new dungeon(dungeonWidth, dungeonHeight, 0, 10, 10, numberOfRooms);
    instanceModels(dd, dungeonWidth, dungeonHeight, itemCount, dirtCount, instanceOffset, dirtInstances);

    map.resetMap(dungeonWidth, dungeonHeight);
    //std::cout << "here" << std::endl;

    for (int i = 0; i < numOfEnemies; i++) {
      while (enemy[i].playerX == 0) {
        int x = rand() % dungeonWidth;
        int y = rand() % dungeonHeight;
        if ( dd->getTile(x, y) == 1) {
          enemy[i].playerX = x;
          enemy[i].playerY = y;
          enemy[i].model.setPosition(glm::vec3(x, 0.0, -y + 0.5f));
        }
      }
    }

    e->audio.loadSound("jump", DIR"res/audio/sounds/jump2.wav");
    e->audio.loadMusic("song", DIR"res/audio/music/04. deadmau5 - Squid.mp3");

    e->mesh["dirt"] = new Mesh(DIR"res/meshes/dirt", "dirt.dae");
    e->mesh["dirt"]->instance(dirtInstances);
    e->mesh["tree"] = new Mesh(DIR"res/meshes/tree" , "tree.dae");
    e->mesh["tree"]->instance(instanceOffset);
    e->mesh["mom"] = new Mesh(DIR"res/meshes/mom", "mom.dae");
    //e->mesh["batman"] = new Mesh("res/meshes/bat", "batman.dae");

    e->text.loadFont(e->glh.program("text"),DIR"res/fonts/Note_this.ttf", 100);
    thebox.init(e->glh.program("square"),-1.0,-.75, 2.0, 0.25);

  }

  void Game1::event(SDL_Event &ev) {

    if(ev.type == SDL_KEYDOWN) {
      string command = e->getKeyCommand(ev.key.keysym.sym);

      if (command == "cameraUp") {
          backward = false;
          forward = true;
      }
      if (command == "cameraDown") {
          backward = true;
          forward = false;
      }
      if (command == "cameraLeft") {
        left = true;
        right = false;
      }
      if(command == "cameraRight") {
        right = true;
        left = false;
      }
      if (command == "cameraRaise"){
        up = true;
        down = false;
      }
      if (command == "cameraLower"){
        up = false;
        down = true;
      }
      if (command == "moveRight") {
        player.up = false;
        player.down = false;
        player.right = true;
        player.left = false;
      }
      if (command == "moveLeft") {
        player.up = false;
        player.down = false;
        player.right = false;
        player.left = true;
      }
      if (command == "moveUp") {
        player.up = true;
        player.down = false;
        player.right = false;
        player.left = false;
      }
      if (command == "moveDown") {
        player.up = false;
        player.down = true;
        player.right = false;
        player.left = false;
      }
      if (command == "toggleCamera") {
        cameraBound = (cameraBound) ? false : true;
      }

    }
    if(ev.type == SDL_KEYUP) {
      string command = e->getKeyCommand(ev.key.keysym.sym);

      if (command == "cameraUp")
        forward = false;
      if (command == "cameraDown")
        backward = false;
      if (command == "cameraLeft")
        left = false;
      if (command == "cameraRight")
        right = false;
      if (command == "cameraRaise")
        up = false;
      if (command == "cameraLower")
        down = false;
      if (command == "moveRight")
        player.right = false;
      if (command == "moveLeft")
        player.left = false;
      if (command == "moveUp")
        player.up = false;
      if (command == "moveDown")
        player.down = false;

    }
  }

  void Game1::logic() {
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

    //lightPos.x = lightPos.x + adder;
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

    if((player.up || player.right || player.down || player.left) && !player.moving){
      Mix_PlayChannel( -1, e->audio.sound["jump"], 0 );
    }
    //std::cout << dd->getTile(player.playerX, player.playerY - 1) << std::endl;
    if((player.up || player.right || player.down || player.left) && !player.moving){
      map.resetMap(dungeonWidth, dungeonHeight);

      int playerx = player.playerX;
      int playery = player.playerY;
      if (player.up)
        playery += 1;
      if (player.down)
        playery -= 1;
      if (player.left)
        playerx -= 1;
      if (player.right)
        playerx += 1;
      map.setSpace(playerx,playery, 1);
      for (int i = 0; i < numOfEnemies; i++){
        int fallthrough = 0;
        while(!enemy[i].up && !enemy[i].down && !enemy[i].left && !enemy[i].right && fallthrough < 4) {
          int direction = (rand() % 4) + 1;
          switch(direction){
            case 1:
              if(map.checkSpace(enemy[i].playerX, enemy[i].playerY + 1) == 0){
                enemy[i].up = (dd->getTile(enemy[i].playerX, enemy[i].playerY + 1) == 1) ? true : false;
                map.setSpace(enemy[i].playerX,enemy[i].playerY + 1, 2);
              }
              break;
            case 2:
              if(map.checkSpace(enemy[i].playerX +1, enemy[i].playerY) == 0) {
                enemy[i].right = (dd->getTile(enemy[i].playerX + 1, enemy[i].playerY) == 1) ? true : false;
                map.setSpace(enemy[i].playerX +1,enemy[i].playerY, 2);
              }
              break;
            case 3:
              if(map.checkSpace(enemy[i].playerX, enemy[i].playerY - 1) == 0) {
                enemy[i].down = (dd->getTile(enemy[i].playerX, enemy[i].playerY - 1) == 1) ? true : false;
                map.setSpace(enemy[i].playerX, enemy[i].playerY - 1, 2);
              }
              break;
            case 4:
              if(map.checkSpace(enemy[i].playerX -1, enemy[i].playerY) == 0) {
                enemy[i].left = (dd->getTile(enemy[i].playerX - 1, enemy[i].playerY) == 1) ? true : false;
                map.setSpace(enemy[i].playerX -1, enemy[i].playerY, 2);
              }
              break;
            case 0:
              break;
            }
          fallthrough++;
          }

          //enemy[i].move();

        }
    }
    player.move();
    //std::cout << "now here" << std::endl;
    for (int i = 0; i < numOfEnemies ; i++){
      enemy[i].move();
      enemy[i].up = enemy[i].down = enemy[i].left = enemy[i].right = false;
    }

    playerPos = player.model.getPosition();
    lightPos.x = playerPos.x ;
    lightPos.y = playerPos.y + 10;
    lightPos.z = playerPos.z ;
    lightDir = glm::vec4(playerPos.x, playerPos.y, playerPos.z, 10.0f);

    if (cameraBound) {
      cam1ori = playerPos;
      cam1ori.y = 0;
      cam1pos.x = playerPos.x; //cam1pos.x;
      cam1pos.y = /*playerPos.y +*/ cameraOffsety;
      cam1pos.z = playerPos.z + cameraOffsetz;
    }


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


  }

  void Game1::render() {
    glClearColor(0.0,0.0,0.0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);

    e->glh.useProgram("program");
    glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
    glUniform4f(lightPosDir, playerPos.x, playerPos.y, playerPos.z, lightDir.w);
    models[0].bindUniform(e->glh.activeProgram, "MVP", &camera1);
    e->mesh["tree"]->renderInstanced(e->glh.activeProgram, "texUnit", itemCount);

    e->glh.useProgram("program");
    glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
    glUniform4f(lightPosDir, playerPos.x, playerPos.y, playerPos.z, lightDir.w);
    models[1].bindUniform(e->glh.activeProgram, "MVP", &camera1);
    e->mesh["dirt"]->renderInstanced(e->glh.activeProgram, "texUnit", dirtCount + 1);

    e->glh.useProgram("program");
    glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
    glUniform4f(lightPosDir, playerPos.x, playerPos.y, playerPos.z, lightDir.w);
    player.model.bindUniform(e->glh.activeProgram, "MVP", &camera1);
    e->mesh["mom"]->render(e->glh.activeProgram, "texUnit");

    for (int i = 0; i < numOfEnemies; i++) {
      e->glh.useProgram("program");
      glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
      glUniform4f(lightPosDir, playerPos.x, playerPos.y, playerPos.z, lightDir.w);
      enemy[i].model.bindUniform(e->glh.activeProgram, "MVP", &camera1);
      e->mesh["mom"]->render(e->glh.activeProgram, "texUnit");
    }

    glm::vec4 color = {0.0, 0.0, 0.0, 0.4};
    thebox.render(color, e->settings->i("resX"), e->settings->i("resY"));
    //std::cout << "program " <<  e->glh.program("text") << e->glh.program("program") << std::endl;
    glUseProgram(0);
    glDisable(GL_DEPTH_TEST);
    e->glh.useProgram("text");
    e->text.render(
      e->glh.program("text"),
      "Into the Woods I Must Go",
      -1.0f,
      -0.98f,
      e->settings->i("resX"),
      e->settings->i("resY")
    );

  }

  void Game1::instanceModels(	dungeon *dd,
  											int w,
  											int h,
  											unsigned int &layer1Count,
  											unsigned int &layer2Count,
  											std::vector<GLfloat> &layer1,
  											std::vector<GLfloat> &layer2){

  	for(unsigned int i = 0; i < w * h ; i++) {
  		if(dd->tiles[i].type != FLOOR) {
  			layer1Count++;
  			unsigned int x = i % w;
  			unsigned int y = i / h;
  			float nY = (float)y; //+ varianceX;
  			float nX = (float)x;
  			layer1.push_back(nX);
  			layer1.push_back(0.0f);
  			layer1.push_back(-nY);

  		} else if ( dd->tiles[i].type == FLOOR) {
  			layer2Count++;
  			unsigned int x = i % w;
  			unsigned int y = i / h;
  			float nY = (float)y; //+ varianceX;
  			float nX = (float)x;
  			layer2.push_back(nX);
  			layer2.push_back(0.0f);
  			layer2.push_back(-nY);
  		}
  	}

  }
