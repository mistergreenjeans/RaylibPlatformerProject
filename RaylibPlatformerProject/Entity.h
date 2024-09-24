#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Layer.h"
#include "Component.h"
#include "Vec2.h"
#include "Room.h"


using std::string;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::vector;

class Component;
class Room;
class Entity {
public:
    bool global = false;
    string type;
    Room* scene;
    layer myLayer;
    Vec2 spawnPos;
    Vec2 pos;
    Vec2 size;

    Vec2 vel = { 0,0 };

    bool removeMe = false;
    bool updateOffScreen = false;
    bool isOnScreen = false;
    vector<Component*> myComponents;
    Entity(Vec2 p, Vec2 s, layer mLayer = BASIC,
        vector<Component*> mComp = {}, string ty = "NOSAVE",
        bool updateOScreen = false);
    Entity();
    void addComponent(Component* myComp);
    Component* getComponent(string compName);
    virtual void start();
    virtual void update(float fElapsedTime);
    virtual void onRemove();
    virtual void draw();
    virtual void drawUI();
    virtual void drawDebugging();
    Vec2 getPos();
    virtual void saveToTXT(ofstream& outStream);


};