#pragma once
#include <vector>
#include <string>
#include "Entity.h"
#include "Room.h"

#include "DukeMath.h"
#include "Tile.h"
using std::string;
using std::vector;
class Room;
class Entity;

class Level {
public:
    vector<Room*> rooms;
    Room* lastSaveRoom;
    Room* currentRoom;
    string levelName;

    Entity* player;
    Entity* camera;
    vector<Entity*> globalEntities;
    Level(string name);

    void goToLastSave();
    void onScreenTransition();
    void runningLevel(Camera2D& worldSpaceCamera, int virtualScreenWidth, int virtualScreenHeight, float fElapsedTime);
    void drawLevel(Camera2D& worldSpaceCamera, int virtualScreenWidth, int virtualScreenHeight);
    void drawUI(Camera2D& worldSpaceCamera, int virtualScreenWidth, int virtualScreenHeight);
    void addRoom(Room* r);
};