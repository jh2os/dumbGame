#ifndef DUNGEON_H
#define DUNGEON_H

#include <cstddef>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <iostream>

struct coord {
  int x;
  int y;
  coord(){};
  coord(int nx, int ny) {
    x = nx;
    y = ny;
  }
  void set(int nx, int ny) {
    x = nx;
    y = ny;
  }
  void display() {
    std::cout << "(" <<
    x << "," << y << ")";
  }
};

enum direction {
  UP = 0,
  DOWN,
  LEFT,
  RIGHT
};

struct door {
  coord doorCoord;
  direction dir;
};

enum Type {
  NONE = 0,
  FLOOR,
  WALL
};

struct tile {
  int room;
  Type type;
};
struct room {
  coord origin;
  direction entranceDir;
  int length;
  int width;
  door * entrances[4];
  room() {entrances[0] =entrances[1] = entrances[2] = entrances[3] = NULL;}
};

struct chest {
  coord position;
  std::vector<int> items;
};

class dungeon {
private:
  std::vector<room *> rooms;
  std::vector<chest*> chests;

  int dungeonWidth;
  int dungeonHeight;
  int dropPercentage;
  int roomMaxWidth;
  int roomMaxHeight;
  int numberOfRooms;
  coord entry;
  coord exit;
public:
  tile * tiles;
  dungeon(){}
  dungeon(int dw, int dh, int dp, int rmw, int rmh, int nor);
  void init();
  room genRoom(coord entrance, direction dir, int roomNumber);
  void display();

};

#endif
