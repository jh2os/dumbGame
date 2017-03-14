#include "dungeon.h"

dungeon::dungeon(int dw, int dh, int dp, int rmw, int rmh, int nor){
  dungeonWidth  = dw;
  dungeonHeight = dh;
  dropPercentage= dp;
  roomMaxWidth  = rmw;
  roomMaxHeight = rmh;
  numberOfRooms = nor;

  srand (time(NULL));

  this->init();
}

void dungeon::init() {

  tiles = new tile[dungeonWidth * dungeonHeight];

  for(int y = dungeonHeight - 1; y >= 0; y--){
    for(int x = 0; x < dungeonWidth; x++) {
      tile newTile;
      newTile.room = 0;
      if ( y == 0 || y == dungeonHeight -1 || x == 0 || x == dungeonWidth - 1)
        newTile.type = WALL;
      else
        newTile.type = NONE;
      tiles[(y*dungeonWidth) + x] = newTile;
    }
  }

  std::vector<room> startRooms;
  std::vector<room> endRooms;
  // Create room 1
  //room testthing = genRoom(coord(dungeonWidth / 2, 0), UP, 1);
  //room testthing2 = genRoom(coord(dungeonWidth / 2, dungeonHeight -1), DOWN, 1);
  entry = coord(0, dungeonHeight / 2);
  room first = genRoom(entry, LEFT, 1);
  startRooms.push_back(first);
  // create room -1
  //room last = genRoom(coord(dungeonWidth - 1, dungeonHeight / 2), RIGHT, -1);
  //endRooms.push_back(last);

  room testRoom;
  for (int a =0; a < numberOfRooms; a++) {
    bool found = false;
    while (found == false) {
      int room = (rand() % startRooms.size());
      int direction = (rand() % 4);
      if (startRooms[room].entrances[direction] == NULL) {

        coord oldRoomE(0,0);
        coord newRoomE(0,0);

        switch (direction) {
          case UP: {
            int rangeStart = startRooms[room].origin.x + 1;
            int rangeEnd = (startRooms[room].origin.x) + (startRooms[room].width -1) -1;
            int newYpos = startRooms[room].origin.y + startRooms[room].length -1;
            int newXpos = (rand() % (rangeEnd - rangeStart + 1)) + rangeStart;

            oldRoomE = coord(newXpos, newYpos);
            newRoomE = coord(newXpos, newYpos + 1);

            testRoom = genRoom(newRoomE, UP, 2);
            if (testRoom.origin.x != -1){
              tiles[(oldRoomE.y  * dungeonWidth) + oldRoomE.x].type = FLOOR;
              startRooms.push_back(testRoom);
              found = true;
            }
            break;
          }
          case DOWN: {
            int rangeStart = startRooms[room].origin.x + 1;
            int rangeEnd = (startRooms[room].origin.x) + (startRooms[room].width -1) -1;
            int newYpos = startRooms[room].origin.y;
            int newXpos = (rand() % (rangeEnd - rangeStart + 1)) + rangeStart;

            oldRoomE = coord(newXpos, newYpos);
            newRoomE = coord(newXpos, newYpos - 1);

            testRoom = genRoom(newRoomE, DOWN, 2);
            if (testRoom.origin.x != -1){
              tiles[(oldRoomE.y * dungeonWidth) + oldRoomE.x].type = FLOOR;
              startRooms.push_back(testRoom);
              found = true;
            }

            break;
          }
          case LEFT: {
            int rangeStart = startRooms[room].origin.y + 1;
            int rangeEnd = (startRooms[room].origin.y) + (startRooms[room].length -1) - 1;
            int newYpos = (rand() % (rangeEnd - rangeStart + 1)) + rangeStart;
            int newXpos = startRooms[room].origin.x;

            oldRoomE = coord(newXpos, newYpos);
            newRoomE = coord(newXpos - 1, newYpos);

            testRoom = genRoom(newRoomE, RIGHT, 2);
            if (testRoom.origin.x != -1){
              tiles[(oldRoomE.y * dungeonWidth) + oldRoomE.x].type = FLOOR;
              startRooms.push_back(testRoom);
              found = true;
            }
            break;
          }
          case RIGHT: {
            int rangeStart = startRooms[room].origin.y + 1;
            int rangeEnd = (startRooms[room].origin.y) + (startRooms[room].length -1) - 1;
            int newYpos = (rand() % (rangeEnd - rangeStart + 1)) + rangeStart;
            int newXpos = startRooms[room].origin.x + startRooms[room].width -1;

            oldRoomE = coord(newXpos, newYpos);
            newRoomE = coord(newXpos + 1, newYpos);

            testRoom = genRoom(newRoomE, LEFT, 2);
            if (testRoom.origin.x != -1){
              tiles[(oldRoomE.y * dungeonWidth) + oldRoomE.x].type = FLOOR;
              startRooms.push_back(testRoom);
              found = true;
            }
            break;
          }
        }
      }


    }
  }
  bool prod = false;
  int lastCol = dungeonWidth -1;
  for(lastCol = dungeonWidth -1; lastCol > 0 && !prod; lastCol--){
    for(int y = 0; y < dungeonHeight && !prod; y++) {
      if (tiles[(y * dungeonWidth) + lastCol].type == FLOOR){
        prod = true;
        break;
      }
    }
  }
  lastCol++;
  Type magic = NONE;
  int randx = 0;
  while(magic != 1){
    randx = (rand() % dungeonHeight);
    magic = tiles[(randx * dungeonWidth) + lastCol].type;
  }
  tiles[(randx * dungeonWidth) + lastCol + 1].type = FLOOR;

}

room dungeon::genRoom(coord entrance, direction dir, int roomNumber){
  // ray cast the entrance in the opposite direections
  //int raycast = 0;
  int howWide = (rand() % (roomMaxWidth-5)) + 5;
  int howHigh = (rand() % (roomMaxHeight-5)) + 5;
  //std::cout << "Entrance: " << entrance.x << "," << entrance.y << std::endl;
  //std::cout << "Height: " << howHigh << "\tWidth: " << howWide << std::endl;
  howWide = (howWide % 2 == 1) ? howWide : howWide + 1;
  howHigh = (howHigh % 2 == 1) ? howHigh : howHigh + 1;
  //std::cout << "Height: " << howHigh << "\tWidth: " << howWide << std::endl;

  room returnRoom;
  returnRoom.origin = coord(-1,-1);
  door doorO;
  doorO.doorCoord = entrance;
  doorO.dir = dir;

  if (dir == 0) {
    int check = howWide / 2;

    for (int y = 0; y < howHigh; y++) {
      for (int x = 0 -check; x < howWide -check; x++) {
        if (
          (entrance.x + x > dungeonWidth -1 ) ||
          (entrance.x + x  < 0) ||
          (entrance.y + y > dungeonHeight -1) ||
          (entrance.y + y < 0) ||
            tiles[(entrance.y + y) * dungeonWidth + entrance.x + x].room != 0){
              return returnRoom;
            }
      }
    }
    for (int y = 0; y < howHigh; y++) {
      for (int x = 0 - check; x < howWide - check; x++) {
        tile newTile;
        newTile.room = roomNumber;
        if (  (y == 0) ||
              (y == howHigh -1) ||
              (x == 0 - check) ||
              (x == howWide -1 - check)){
          newTile.type = WALL;
        } else {
          newTile.type = FLOOR;
        }
        tiles[(entrance.y + y) * dungeonWidth + entrance.x + x ] = newTile;
      }
    }
    returnRoom.origin = coord(entrance.x-check, entrance.y);


  } else if (dir == 1){
    int check = howWide / 2;

    for (int y = 0; y < howHigh; y++) {
      for (int x = 0 - check; x < howWide - check; x++) {
        if (
          (entrance.x + x > dungeonWidth -1 ) ||
          (entrance.x + x  < 0) ||
          (entrance.y - y > dungeonHeight -1) ||
          (entrance.y - y < 0) ||
            tiles[(entrance.y - y) * dungeonWidth + entrance.x + x].room != 0){
              return returnRoom;
            }
      }
    }
    for (int y = 0; y < howHigh; y++) {
      for (int x = 0 - check; x < howWide -check; x++) {
        tile newTile;
        newTile.room = roomNumber;
        if (  (y == 0) ||
              (y == howHigh-1) ||
              (x == 0 - check) ||
              (x == howWide -1 - check)){
          newTile.type = WALL;
        } else {
          newTile.type = FLOOR;
        }
        tiles[(entrance.y - y) * dungeonWidth + entrance.x + x ] = newTile;
      }
    }
    returnRoom.origin = coord(entrance.x-check, entrance.y - howHigh+1);

  } else if (dir == 2) {
    int check = howHigh / 2;

    for (int x = 0; x < howWide; x++) {
      for (int y = 0 - check; y < howHigh - check; y++) {
        if (
            (entrance.x + x > dungeonWidth - 1) ||
            (entrance.x + x  < 0) ||
            (entrance.y + y > dungeonHeight -1) ||
            (entrance.y + y < 0) ||
            tiles[(entrance.y + y ) * dungeonWidth + entrance.x + x].room != 0){
              return returnRoom;
            }
      }
    }
    for (int y = 0 - check; y < howHigh - check; y++) {
      for (int x = 0; x < howWide; x++) {
        tile newTile;
        newTile.room = roomNumber;
        if (  (y == 0 - check) ||
              (y == howHigh - 1 - check) ||
              (x == 0) ||
              (x == howWide -1)){
          newTile.type = WALL;
        } else {
          newTile.type = FLOOR;
        }
        tiles[(entrance.y + y) * dungeonWidth + entrance.x + x] = newTile;
      }
    }
    returnRoom.origin = coord(entrance.x, entrance.y -check);


  } else if (dir == 3) {
    int check = howHigh / 2;

    for (int x = 0; x < howWide; x++) {
      for (int y = 0 - check; y < howHigh - check; y++) {
        if (
            (entrance.x - x > dungeonWidth - 1) ||
            (entrance.x - x  < 0) ||
            (entrance.y + y > dungeonHeight -1) ||
            (entrance.y + y < 0) ||
            tiles[(entrance.y + y ) * dungeonWidth + entrance.x + x].room != 0){
              //std::cout << x << " " << y <<  " " << (entrance.x - x > dungeonWidth) << (entrance.x - x  < 0) << (entrance.y + y > dungeonHeight) << (tiles[(entrance.y + y ) * dungeonWidth + entrance.x - x] != 0) << std::endl;
              //std::cout << (entrance.y + y ) * dungeonWidth + entrance.x - x << std::endl;
              //tiles[(entrance.y + y ) * dungeonWidth + entrance.x - x] = 10;
              return returnRoom;
            }
      }
    }
    for (int y = 0 - check; y < howHigh - check; y++) {
      for (int x = 0; x < howWide; x++) {
          tile newTile;
          newTile.room = roomNumber;
          if (  (y == 0 - check) ||
                (y == howHigh - 1 - check) ||
                (x == 0) ||
                (x == howWide - 1)){
            newTile.type = WALL;
          } else {
            newTile.type = FLOOR;
          }
        tiles[(entrance.y + y) * dungeonWidth + entrance.x - x] = newTile;
      }
    }
    returnRoom.origin = coord(entrance.x , entrance.y -check);



  }

  tile entryway;
  entryway.room = roomNumber;
  entryway.type = FLOOR;
  tiles[(entrance.y * dungeonWidth) + entrance.x] = entryway;
  returnRoom.entranceDir = dir;
  returnRoom.length = howHigh;
  returnRoom.width = howWide;
  returnRoom.entrances[dir] = &doorO;
  return returnRoom;

}

void dungeon::display() {
  std::cout << std::endl << " \t";
  for(int i = 0; i < dungeonWidth; i++){
    if(i < 10)
      std::cout << " ";
    std::cout << i;
  }
  std::cout << std::endl;
  for(int y = dungeonHeight-1; y >= 0; y--){
    std::cout <<  y << "\t";
    for(int x = 0; x < dungeonWidth; x++) {
      if (tiles[(y * dungeonWidth) + x].type == NONE) {
        std::cout << " ";
      } else if (tiles[(y * dungeonWidth) + x].type == FLOOR) {
        std::cout << ".";
      } else if (tiles[(y * dungeonWidth) + x].type == WALL) {
        std::cout << "#";
      }
      std::cout << " ";
    }
    std::cout << std::endl;
  }
}

int dungeon::getTile(int x, int y) {
  return tiles[(y * dungeonWidth) + x].type;
}
