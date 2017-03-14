#include "entity.h"

Entity::Entity() {
    this->up = false;
    this->down = false;
    this->left = false;
    this->right = false;
    this->moving = false;
    this->direction = 0;
    this->moveVar = 0.0f;
    this->startMoveTime = 0;
    this->playerX = 0;
    this->playerY = 0;
    this->model.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

void Entity::move() {
  float movespeed = 150.0f;
  if (!this->moving) {
    //std::cout << "here" << std::endl;
    //glm::vec3 oldPos = this->model.getPosition();
    if (this->left) {
      this->moving = true;
      this->direction = 4;
      this->startMoveTime = SDL_GetTicks();
      this->startMovePos = this->model.getPosition();
      //this->model.setPosition(glm::vec3(oldPos.x - movespeed, oldPos.y, oldPos.z));
    } else if (this->right) {
      //std::cout << "Go Right!!!" << std::endl;
      this->moving = true;
      this->direction = 2;
      this->startMoveTime = SDL_GetTicks();
      this->startMovePos = this->model.getPosition();
      //this->model.setPosition(glm::vec3(oldPos.x + movespeed, oldPos.y, oldPos.z));
    } else if (this->up) {
      this->moving = true;
      this->direction = 1;
      this->startMoveTime = SDL_GetTicks();
      this->startMovePos = this->model.getPosition();
      //this->model.setPosition(glm::vec3(oldPos.x, oldPos.y, oldPos.z - movespeed));
    } else if (this->down) {
      this->moving = true;
      this->direction = 3;
      this->startMoveTime = SDL_GetTicks();
      this->startMovePos = this->model.getPosition();
      //this->model.setPosition(glm::vec3(oldPos.x, oldPos.y, oldPos.z + movespeed));
    }
    //this->up = this->down = this->left = this->right = false;
  }
  if (this->moving){
    float distance = (SDL_GetTicks() - this->startMoveTime) / movespeed;
    //std::cout << distance << "\t" << direction << std::endl;
    distance = (distance >= 1.0f) ? 1.0f : distance;
    if (distance == 1.0f) {
      this->moving = false;
      switch(this->direction) {
        case 1:
        this->playerY += 1;
        break;
        case 2:
        this->playerX += 1;
        break;
        case 3:
        this->playerY -= 1;
        break;
        case 4:
        this->playerX -= 1;
        break;
      }
      //std::cout << " (" << this->playerX << ", " << this->playerY << ") " << std::endl;
    }
    float hopdist = sin(distance * PI) /4 ;

    switch(this->direction) {
      case 1: {//up
        float newpos = this->startMovePos.z - distance;
        this->model.setPosition(glm::vec3(this->startMovePos.x, this->startMovePos.y + hopdist, newpos));
        break;
      }
      case 2:{ //right
        float newpos = this->startMovePos.x + distance;
        this->model.setPosition(glm::vec3(newpos, this->startMovePos.y + hopdist, this->startMovePos.z));
        break;
      }
      case 3:{ //down
        float newpos = this->startMovePos.z + distance;
        this->model.setPosition(glm::vec3(this->startMovePos.x, this->startMovePos.y + hopdist, newpos));
        break;
      }
      case 4:{ //left
        float newpos = this->startMovePos.x - distance;
        this->model.setPosition(glm::vec3(newpos, this->startMovePos.y + hopdist, this->startMovePos.z));
        break;
      }
    }
  }
}
