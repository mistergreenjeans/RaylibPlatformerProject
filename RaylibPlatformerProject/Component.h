#pragma once
#include <string>
#include "Entity.h"
#include "Vec2.h"
class Entity;
class Component {
public:

    Entity* parent;
    std::string compoName = "basic";
    Component();
    virtual void start();
    virtual void update(float fElapsedTime);
    virtual void onRemove();
    virtual void draw();
    virtual void drawDebugging();
    virtual void drawUI();

};

class CompCamera : public Component {
public:
    bool followPlayer = true;
    bool changingScreens = false;
    float t = 0;
    Vec2 tranStart;
    Vec2 tranEnd;
    Entity* player;
    float xt = 0;

    int levelHeight;
    int levelWidth;
    Vec2 DesiredLocation = { 0,0 };
    //int camHeight = screenHeight - 100;
    //int camWidth = screenWidth - 100;
    int camHeight;
    int camWidth;
    bool& freezeTime;
    int virtualScreenWidth;
    int natrualZoom;
    Camera2D& worldSpaceCamera;
    CompCamera(int virtualScreenWidth, int virtualScreenHeight, int natrualZoom, bool& freezeTime, Camera2D& worldSpaceCamera);
    virtual void start();
    virtual void update(float fElapsedTime);
};