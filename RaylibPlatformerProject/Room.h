#pragma once
#include <vector>
#include <string>
#include "Tile.h"
#include "Level.h"
#include "Entity.h"

using std::string;
using std::vector;
class Level;
class Room {
public:
    Level* inLevel;
    Vec2 pos;
    string roomName;
    vector<vector<Tile*>> tileSet;
    vector<vector<Tile*>> background;
    vector<Entity*> eList;
    int width = 0;
    int height = 0;

    Room();
    Room(string name);


    void addEntity(Entity* add);
    void drawLevel(Camera2D& worldSpaceCamera, int virtualScreenWidth, int virtualScreenHeight, bool debugMode = false);
    void drawUI();
    void startLevel();
    void updateLevel(Camera2D& worldSpaceCamera, int virtualScreenWidth, int virtualScreenHeight, float fElapsedTime);
    void drawLevel2(float ratioL, Camera2D& worldSpaceCamera, int virtualScreenWidth, int virtualScreenHeight);
};