
#pragma once
#include <memory.h>;
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <corecrt_math.h>
#include "raylib.h"
#include "Entity.h"
#include "Component.h"
#include "Vec2.h"
#include "Tile.h"
#include "Vec2.h"
#include "Room.h"
#include "Level.h"
#include "DukeMath.h"


#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))
using namespace std;

const int screenWidth = 1600;
const int screenHeight = 900;

const int natrualZoom = 1;
const int virtualScreenWidth = 480*natrualZoom;
const int virtualScreenHeight = 270*natrualZoom;

const float virtualRatio = (float)screenWidth / (float)virtualScreenWidth;

bool win = false;

float scale;

string currentSaveFile = "extraSave";
Rectangle sourceRec;
Rectangle destRec;


int tileSize = 8;
float fElapsedTime = 0;
bool freezeTime = false;
float speedRunTimer = 0;
float worldTimer = 0;

int sgn(float temp) {
    if (temp > 0) {
        return 1;
    }
    else if (temp < 0) {
        return -1;
    }
    return 0;
}
int stringToInt(string str) {
    int temp = 0;
    int neg = 1;
    for (int i = 0; i < str.length(); i++) {
        if (str.at(i) == '-') {
            neg = -1;
            continue;
        }
        temp *= 10;
        temp += (str[i] - '0');
    }
    return temp * neg;
}

Vec2 mouse(0, 0);
Vec2 virtualMouse(0, 0);

Vec2 playerSaveTemp(0, 0);
struct enemyDef {
    string type;
    //outStream << myLayer << endl;
    Vec2 pos;

    bool updateOffScreen;



};



int KEYBIND_JUMP = KEY_Z;
int KEYBIND_UP = KEY_UP;
int KEYBIND_LEFT = KEY_LEFT;
int KEYBIND_DOWN = KEY_DOWN;
int KEYBIND_RIGHT = KEY_RIGHT;

int KEYBIND_ACTION1 = KEY_X;
int KEYBIND_ACTION2 = KEY_A;

Camera2D worldSpaceCamera = { 0 };  // Game world camera

Camera2D screenSpaceCamera = { 0 }; // Smoothing camera








vector<string> tileTexturePath = { "GrassTop.png","GrassTile.png","DirtTile.png",

"DarkDirt.png","MudTile.png","StoneOne.png",
"StoneTwo.png", "StoneGround.png", "SmoothStone.png",
"Brick.png","SmoothLeft.png","SmoothRight.png",
"Salag.png", "WoodHor.png","WoodVer.png","WoodCross.png",
"Vine.png","VineEnd.png","PlatMid.png","SpikeUp.png","SpikeDown.png","SpikeRight.png","SpikeLeft.png"};
vector<Texture2D> tileTextures(tileTexturePath.size());

class button {
public:
    Vec2 pos;
    float w;
    float h;
    bool isDown = false;
    bool wasDown = false;
    bool pressed = false;
    float sizeIncrease;
    Color unHigh;
    Color high;
    Color current;
    float lineThickness;
    button(Vec2 position, float width, float height, Color unH, Color hi, float sizeIncreasee = 5, float lineThinknesss = 2) {
        pos = position;
        w = width;
        h = height;

        unHigh = unH;
        high = hi;
        current = unH;

        sizeIncrease = sizeIncreasee;
        lineThickness = lineThinknesss;
    }
    button() {
        pos = { 0,0 };
        w = 10;
        h = 10;

        unHigh = WHITE;
        high = GREEN;
        current = WHITE;

        sizeIncrease = 10;
        lineThickness = 5;
    }
    void update() {
        wasDown = isDown;
        Vector2 mp = GetMousePosition();
        if (mp.x<pos.x + w && mp.x>pos.x && mp.y<pos.y + h && mp.y>pos.y) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                isDown = true;
            }
            else {
                isDown = false;
            }
            current = high;
        }
        else {
            isDown = false;
            current = unHigh;
        }

        if (isDown && !wasDown) {
            pressed = true;
        }
        else {
            pressed = false;
        }
    }
    void update(Vec2 mp) {
        wasDown = isDown;
        
        if (mp.x<pos.x + w && mp.x>pos.x && mp.y<pos.y + h && mp.y>pos.y) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                isDown = true;
            }
            else {
                isDown = false;
            }
            current = high;
        }
        else {
            isDown = false;
            current = unHigh;
        }

        if (isDown && !wasDown) {
            pressed = true;
        }
        else {
            pressed = false;
        }
    }
    void draw() {
        Rectangle temp;
        if (isDown) {
            temp = { pos.x - sizeIncrease, pos.y - sizeIncrease, w + sizeIncrease * 2, h + sizeIncrease * 2 };
            DrawRectangleLinesEx(temp, lineThickness, current);
        }
        else {
            temp = { pos.x, pos.y, w, h };
            DrawRectangleLinesEx(temp, lineThickness, current);
        }

    }
};








vector<Tile*> allTiles  = {new Tile(' ', TILE_RULE_background),
                            new SpriteTile(',', "GrassTop.png", WHITE, TILE_RULE_background),
                            new SpriteTile('a', "GrassTile.png", WHITE, TILE_RULE_solid),
                            new SpriteTile('b', "DirtTile.png", WHITE, TILE_RULE_solid),
                            new SpriteTile('c', "DarkDirt.png", WHITE, TILE_RULE_background),
                            new SpriteTile('C', "DarkDirt.png", {150,150,150,255}, TILE_RULE_background),
                            new SimpleTile('D',BLACK, TILE_RULE_background),
                            new SpriteTile('d', "MudTile.png", WHITE, TILE_RULE_solid),
                            new SpriteTile('e', "StoneOne.png", WHITE, TILE_RULE_solid),
                            new SpriteTile('f', "StoneTwo.png", WHITE, TILE_RULE_solid),
                            new SpriteTile('f', "StoneTwo.png", {100,100,100,255}, TILE_RULE_solid),
                            new SpriteTile('g', "StoneGround.png", WHITE, TILE_RULE_solid),
                            new SpriteTile('G', "StoneGround.png", {120,120,120,255}, TILE_RULE_solid),
                            new SpriteTile('h', "SmoothStone.png", WHITE, TILE_RULE_solid),
                            new SpriteTile('i', "Brick.png", {190,190,190,255}, TILE_RULE_solid),
                            new SpriteTile('I', "Brick.png", {80,80,80,255}, TILE_RULE_background),
                            new SpriteTile('-', "PlatMid.png",WHITE, TILE_RULE_platformBulPass, {0,0,1,.333 }),
                            new SpriteTile('j', "SmoothLeft.png", WHITE, TILE_RULE_background),
                            new SpriteTile('k', "SmoothRight.png", WHITE, TILE_RULE_background),

                            new SpriteTile('l', "Salag.png", WHITE, TILE_RULE_background),
                            new SpriteTile('m', "WoodHor.png", WHITE, TILE_RULE_solid),
                            new SpriteTile('n', "WoodVer.png", WHITE, TILE_RULE_solid),
                            new SpriteTile('o', "WoodCross.png", WHITE, TILE_RULE_solid),
                            new SpriteTile('M', "WoodHor.png", {100,100,100,255}, TILE_RULE_background),
                            new SpriteTile('N', "WoodVer.png", {100,100,100,255}, TILE_RULE_background),
                            new SpriteTile('O', "WoodCross.png", {100,100,100,255}, TILE_RULE_background),
                            new SpriteTile('p', "Vine.png", WHITE, TILE_RULE_background),
                            new SpriteTile('q', "VineEnd.png", WHITE, TILE_RULE_background),
                            new SimpleTile('#', GREEN , TILE_RULE_solid),

                            new SimpleTile('+', DARKGREEN, TILE_RULE_solidBulPass),
                            new SimpleTile('_', {0,50,0,255}, TILE_RULE_background),
                            new SimpleTile('O', { 130,10,10,255 }, TILE_RULE_background),
                            new SpriteTile('<', "SpikeLeft.png", WHITE,TILE_RULE_leftSpike,{5 / 8.0f,.1,3 / 8.0f,1-.2}),
                            new SpriteTile('>', "SpikeRight.png", WHITE,TILE_RULE_rightSpike,{0,.1,3 / 8.0f,1-.2}),
                            new SpriteTile('^', "SpikeUp.png", WHITE,TILE_RULE_upSpike,{.1,5 / 8.0f,1-.2f,3 / 8.0f}),
                            new SpriteTile('v', "SpikeDown.png", WHITE,TILE_RULE_downSpike,{.1,0,1-.2,3 / 8.0f}),




};

Tile* errorTile = new Tile('?');


Tile* charToTile(char c) {
    for (int i = 0; i < allTiles.size(); i++) {
        if (c == allTiles.at(i)->tileType) {
            return allTiles.at(i);
        }
    }
    return errorTile;
}



class Level;
class Room;
class Entity;
class Component;






Entity* TXTtoEntity(ifstream& inStream);

Entity* createPlayer(Vec2 pos);
Entity* createCameraHolder(Vec2 pos);
Vec2 playerPos;
Vec2 playerVel;




bool RectTileCollision(Rectangle rec, Room grid, TileProperties collCheck, bool Debugging = false, Color color1 = ORANGE, Color color2 = YELLOW);


void loadRoom(Room& mLevel, string RoomName);
void saveRoom(Room& mLevel, string RoomName);
void loadLevel(Level& mLevel, string levelName);
void saveLevelAs(Level& mLevel, string levelName);
struct RayHit {
    Vec2 hitPos;
    Vec2 hitNormal;
    char objType;
};
class Ray2D {
public:
    Vec2 start;
    Vec2 dir;
    Ray2D(Vec2 s, Vec2 d) {
        start = s;
        dir = d;
    }

    RayHit intersect(Room map, float maxLength = 100) {
        Vec2 tempStart(start.x / tileSize - map.pos.x, start.y / tileSize - map.pos.y);
        maxLength /= tileSize;
        bool hitObject = false;

        float curLength = 0;

        Vec2 rayDir = dir.normalize();

        RayHit re = { Vec2(0,0),Vec2(0,0),1 };

        float dx = rayDir.x / rayDir.y;
        float dy = rayDir.y / rayDir.x;
        Vec2 rayUnitStepSize = { sqrt(dy * dy + 1),sqrt(dx * dx + 1) };

        int tileCheckX = tempStart.x;
        int tileCheckY = tempStart.y;

        Vec2 rayLength;
        int stepx = 0;
        int stepy = 0;

        bool xNorm = true;
        if (rayDir.x < 0) {
            stepx = -1;
            rayLength.x = (tempStart.x - (float)tileCheckX) * rayUnitStepSize.x;
        }
        else {
            stepx = 1;
            rayLength.x = ((float)tileCheckX + 1 - (tempStart.x)) * rayUnitStepSize.x;
        }
        if (rayDir.y < 0) {
            stepy = -1;
            rayLength.y = (tempStart.y - (float)tileCheckY) * rayUnitStepSize.y;
        }
        else {
            stepy = 1;
            rayLength.y = ((float)tileCheckY + 1 - (tempStart.y)) * rayUnitStepSize.y;
        }

        while (!hitObject && curLength < maxLength) {
            //DrawCircle(((rayDir * rayLength.x).x + tempStart.x) * tileSize, (tempStart.y + (rayDir * rayLength.x).y) * tileSize, 5, GREEN);
            //DrawCircle(((rayDir * rayLength.y).x + tempStart.x) * tileSize, (tempStart.y + (rayDir * rayLength.y).y) * tileSize, 5, RED);

            if (rayLength.x < rayLength.y) {
                curLength = rayLength.x;
                tileCheckX += stepx;
                rayLength.x += rayUnitStepSize.x;
                xNorm = true;
            }
            else {
                curLength = rayLength.y;
                tileCheckY += stepy;
                rayLength.y += rayUnitStepSize.y;
                xNorm = false;
            }

            Rectangle temp = { tileSize * (tileCheckX + .25), tileSize * (tileCheckY + .25), tileSize / 2,tileSize / 2 };
            //DrawRectangleLinesEx(temp, 5, PURPLE);
            if (tileCheckX >= 0 && tileCheckX < map.tileSet.at(0).size() && tileCheckY >= 0 && tileCheckY < map.tileSet.size() && curLength < maxLength) {
                if (xNorm) {
                    if (stepx > 0) {
                        if (map.tileSet.at(tileCheckY).at(tileCheckX)->myProperties.solidLeft) {
                            re.objType = map.tileSet.at(tileCheckY).at(tileCheckX)->tileType;
                            re.hitPos = (tempStart + rayDir * curLength+ map.pos) *  tileSize;
                            re.hitNormal = Vec2(-stepx, 0);
                            hitObject = true;
                            return re;
                        }
                    }
                    else if (stepx < 0) {
                        if (map.tileSet.at(tileCheckY).at(tileCheckX)->myProperties.solidRight) {
                            re.objType = map.tileSet.at(tileCheckY).at(tileCheckX)->tileType;
                            re.hitPos = (tempStart + rayDir * curLength + map.pos) * tileSize;
                            re.hitNormal = Vec2(-stepx, 0);
                            hitObject = true;
                            return re;
                        }
                    }
                }
                else {
                    if (stepy > 0) {
                        if (map.tileSet.at(tileCheckY).at(tileCheckX)->myProperties.solidTop) {
                            re.objType = map.tileSet.at(tileCheckY).at(tileCheckX)->tileType;
                            re.hitPos = (tempStart + rayDir * curLength + map.pos) * tileSize;
                            re.hitNormal = Vec2(0, -stepy);
                            hitObject = true;
                            return re;
                        }
                    }
                    else if (stepy < 0) {
                        if (map.tileSet.at(tileCheckY).at(tileCheckX)->myProperties.solidBottom) {
                            re.objType = map.tileSet.at(tileCheckY).at(tileCheckX)->tileType;
                            re.hitPos = (tempStart + rayDir * curLength + map.pos) * tileSize;
                            re.hitNormal = Vec2(0, -stepy);
                            hitObject = true;
                            return re;
                        }
                    }
                }


            }
        }
        return { (tempStart + rayDir * maxLength + map.pos) * tileSize,{0,0},-1 };
        //Rectangle temp2 = { ((start + rayDir * curLength).x) * tileSize -5,((start + rayDir * curLength).y) * tileSize -5 ,10,10 };
        //DrawRectangleLinesEx(temp2, 3, ORANGE);









    }
};






class CompGravity : public Component {
public:
    float str;
    CompGravity(float strength) {
        str = strength;
        compoName = "CompGravity";
    }

    void update(float fElapsedTime) {
        parent->vel.y += str * fElapsedTime;
    }


};
class CompGroundCol : public Component {
public:

    Vec2 collisionDir = { 0,0 };
    Vec2 resDir = { 0,0 };

    vector<Tile*> curTileCol;
    CompGroundCol() : Component() {
        compoName = "CompGroundCol";
    }
    void update(float fElapsedTime) {
        Vec2 xStep = { parent->pos.x + parent->vel.x * fElapsedTime,parent->pos.y };
        Vec2 yStep = { parent->pos.x                       ,parent->pos.y + parent->vel.y * fElapsedTime };

        float leftX = xStep.x - parent->size.x / 2;
        float rightX = xStep.x + parent->size.x / 2;

        float topY = yStep.y - parent->size.y / 2;
        float bottomY = yStep.y + parent->size.y / 2;

        /*if (vel.x > 0) {
            rightX += vel.x * fElapsedTime;
        }
        else if (vel.x < 0) {
            leftX += vel.x * fElapsedTime;
        }
        if (vel.y > 0) {
            bottomY += vel.y * fElapsedTime;
        }
        else if (vel.x < 0) {
            topY += vel.y * fElapsedTime;
        }*/
        Rectangle pHitbox = { parent->pos.x - parent->size.x / 2,parent->pos.y - parent->size.y / 2, parent->size.x,parent->size.y };
        Rectangle xHitbox = { xStep.x - parent->size.x / 2,xStep.y - parent->size.y / 2, parent->size.x,parent->size.y };
        Rectangle yHitbox = { yStep.x - parent->size.x / 2,yStep.y - parent->size.y / 2, parent->size.x,parent->size.y };
        resDir = { 0,0 };
        curTileCol.clear();
        for (int i = topY / tileSize - parent->scene->pos.y; i < bottomY / tileSize - parent->scene->pos.y; i++) {
            for (int j = leftX / tileSize - parent->scene->pos.x; j < rightX / tileSize - parent->scene->pos.x; j++) {
                
                collisionDir = { 0,0 };
                if (i > -1 && i<parent->scene->tileSet.size() && j >-1 && j < parent->scene->tileSet.at(0).size()) {
                    Rectangle hTemp = parent->scene->tileSet.at(i).at(j)->hitBox;
                    hTemp.x += j * tileSize;
                    hTemp.y += i * tileSize;
                    hTemp.x += parent->scene->pos.x * tileSize;
                    hTemp.y += parent->scene->pos.y * tileSize;
                   


                    if (RectRectCollision(xHitbox, hTemp)) {
                        if (parent->vel.x < 0) {


                            collisionDir.x = 1;

                        }
                        else if (parent->vel.x > 0) {



                            collisionDir.x = -1;

                        }

                    }
                    else if (RectRectCollision(yHitbox, hTemp)) {
                        if (parent->vel.y < 0) {
                            

                            collisionDir.y = 1;

                        }
                        else if (parent->vel.y > 0) {



                            collisionDir.y = -1;


                        }

                    }



                    if (collisionDir.x != 0 || collisionDir.y != 0) {




                        collisionResponse(parent->scene->tileSet.at(i).at(j), j, i);
                    }
                }
            }
        }


        /*for (int i = topY / tileSize; i < bottomY / tileSize; i++) {
            for (int j = leftX / tileSize; j < rightX / tileSize; j++) {
                if (i > -1 && i<currLevel->tileSet.size() && j>-1 && j < currLevel->tileSet.at(0).size()) {
                    Rectangle temp = { j * tileSize , i * tileSize, tileSize,tileSize };
                    if (currLevel->tileSet.at(i).at(j)->tileType == '#') {

                        DrawRectangleLinesEx(temp, 4, ORANGE);


                    }
                    else {
                        DrawRectangleLinesEx(temp, 4, { 100,100,100,50 });
                    }
                }

            }
        }
        */
    }
    virtual void collisionResponse(Tile* type, int x, int y) {
        if (parent->myLayer != BULLET && parent->myLayer != PBULLET) {
            if (collisionDir.x > 0 && type->myProperties.solidRight) {

                parent->vel.x = 0;
                parent->pos.x = (x)*tileSize + type->hitBox.width + type->hitBox.x + parent->size.x / 2 + parent->scene->pos.x * tileSize;
                resDir.x = collisionDir.x;
                curTileCol.push_back(type);
                return;
            }
            if (collisionDir.x < 0 && type->myProperties.solidLeft) {

                parent->vel.x = 0;
                parent->pos.x = x * tileSize + type->hitBox.x - parent->size.x / 2 + parent->scene->pos.x * tileSize;
                resDir.x = collisionDir.x;
                curTileCol.push_back(type);
                return;
            }
            if (collisionDir.y > 0 && type->myProperties.solidBottom) {

                parent->vel.y = 0;
                parent->pos.y = (y)*tileSize + type->hitBox.height + type->hitBox.y + parent->size.y / 2 + parent->scene->pos.y * tileSize;
                
                resDir.y = collisionDir.y;
                curTileCol.push_back(type);
                return;
            }
            if (collisionDir.y < 0 && type->myProperties.solidTop && !(parent->myLayer == PLAYER && IsKeyDown(KEYBIND_DOWN) && IsKeyDown(KEYBIND_JUMP) && type->myProperties.platPassThru)) {

                parent->vel.y = 0;
                parent->pos.y = y * tileSize + type->hitBox.y - parent->size.y / 2 + parent->scene->pos.y*tileSize;
                resDir.y = collisionDir.y;
                curTileCol.push_back(type);
                return;
            }
        }
        else {
            if (collisionDir.x > 0 && type->myProperties.stopBulletRight) {
                parent->vel.x = 0;
                parent->pos.x = (x)*tileSize + type->hitBox.width + type->hitBox.x + parent->size.x / 2 + parent->scene->pos.x * tileSize;
                resDir.x = collisionDir.x;
                curTileCol.push_back(type);
                return;
            }
            if (collisionDir.x < 0 && type->myProperties.stopBulletLeft) {
                parent->vel.x = 0;
                parent->pos.x = x * tileSize + type->hitBox.x - parent->size.x / 2 + parent->scene->pos.x * tileSize;
                resDir.x = collisionDir.x;
                curTileCol.push_back(type);
                return;
            }
            if (collisionDir.y > 0 && type->myProperties.stopBulletBottom) {
                parent->vel.y = 0;
                parent->pos.y = (y)*tileSize + type->hitBox.height + type->hitBox.y + parent->size.y / 2 + parent->scene->pos.y * tileSize;

                resDir.y = collisionDir.y;
                curTileCol.push_back(type);
                return;
            }
            if (collisionDir.y < 0 && type->myProperties.stopBulletTop) {
                parent->vel.y = 0;
                parent->pos.y = y * tileSize + type->hitBox.y - parent->size.y / 2 + parent->scene->pos.y * tileSize;
                resDir.y = collisionDir.y;
                curTileCol.push_back(type);
                return;

            }
        }
        if (type->myProperties.isSpike) {
            
                curTileCol.push_back(type);
            

        }
        



    }
};

class CompRemoveTimer :public Component {
public:
    float timer;
    CompRemoveTimer(float time) {
        timer = time;
        compoName = "CompRemoveTimer";
    }
    void update(float fElapsedTime) {
        timer -= fElapsedTime;
        if (timer < 0) {
            parent->removeMe = true;
        }
    }

};
class CompSquareHitBox : public Component {
public:
    Rectangle hitbox;
    Rectangle worldHitBox = { 0,0,0,0 };
    CompSquareHitBox(float localX, float localY, float width, float height) {
        hitbox = { localX,localY,width,height };
        compoName = "CompSquareHitBox";
    }
    void update(float fElapsedTime) {
        worldHitBox = hitbox;
        worldHitBox.x += parent->pos.x;
        worldHitBox.y += parent->pos.y;

    }
    void drawDebugging() {

        DrawRectangleLinesEx(worldHitBox, 1, RAYWHITE);

    }
};
class CompBasicEntityCol :public Component {
public:

    vector<Entity*> onCol;
    vector<layer> checkLayers;
    CompBasicEntityCol(vector<layer> checkLayer) {
        checkLayers = checkLayer;
        compoName = "CompBasicEntityCol";
    }
    void update(float fElapsedTime) {
        onCol.clear();
        vector<Entity*> temp = parent->scene->eList;
        for (int i = 0; i < temp.size(); i++) {
            if (temp.at(i) == parent) {
                continue;
            }
            if (!temp.at(i)->isOnScreen) {
                continue;
            }
            bool skipCalc = true;
            for (int j = 0; j < checkLayers.size(); j++) {

                if (temp.at(i)->myLayer == checkLayers.at(j)) {
                    skipCalc = false;
                }
            }
            if (skipCalc) {
                continue;
            }


            CompSquareHitBox* yourHit = dynamic_cast<CompSquareHitBox*>(temp.at(i)->getComponent("CompSquareHitBox"));
            if (yourHit) {
                Rectangle mi = { parent->pos.x - parent->size.x / 2,parent->pos.y - parent->size.y / 2,parent->size.x,parent->size.y };
                Rectangle te = yourHit->worldHitBox;

                if (RectRectCollision(mi, te)) {
                    onCol.push_back(parent->scene->eList.at(i));
                    

                    return;
                }


            }
            else {
                Rectangle mi = { parent->pos.x - parent->size.x / 2,parent->pos.y - parent->size.y / 2,parent->size.x,parent->size.y };
                Rectangle te = { parent->scene->eList.at(i)->pos.x - parent->scene->eList.at(i)->size.x / 2,parent->scene->eList.at(i)->pos.y - parent->scene->eList.at(i)->size.y / 2,parent->scene->eList.at(i)->size.x,parent->scene->eList.at(i)->size.y };
                if (RectRectCollision(mi, te)) {
                    onCol.push_back(parent->scene->eList.at(i));
                    return;
                }
            }

        }
    }
};
class CompCircleEntityCol : public CompBasicEntityCol {
public:

    CompCircleEntityCol(vector<layer> checkLayer) : CompBasicEntityCol(checkLayer) {
        compoName = "CompCircleEntityCol";
    }
    void update(float fElapsedTime) {
        onCol.clear();
        vector<Entity*> temp = parent->scene->eList;
       
        for (int i = 0; i < temp.size(); i++) {

            CompSquareHitBox* yourHit = dynamic_cast<CompSquareHitBox*>(temp.at(i)->getComponent("CompSquareHitBox"));;
            if (yourHit) {

                Rectangle te = yourHit->worldHitBox;

                if ((temp.at(i) != parent) && RectCircleCollision(te, parent->pos, parent->size.getMagnitude() / 2)) {
                    onCol.push_back(parent->scene->eList.at(i));
                    
                    


                    continue;
                }


            }
            else {

                Rectangle te = { parent->scene->eList.at(i)->pos.x - parent->scene->eList.at(i)->size.x / 2,parent->scene->eList.at(i)->pos.y - parent->scene->eList.at(i)->size.y / 2,parent->scene->eList.at(i)->size.x,parent->scene->eList.at(i)->size.y };
                if ((temp.at(i) != parent) && RectCircleCollision(te, parent->pos, parent->size.getMagnitude() / 2)) {
                    onCol.push_back(parent->scene->eList.at(i));

                    continue;
                }
            }

        }

    }
    void drawDebugging() {
        DrawCircleLines(parent->pos.x,parent->pos.y, parent->size.getMagnitude() / 2, RED);
    }
};

class CompDrawDamage : public Component {
public:
    int drawNum = 0;
    Entity* oldPar;
    bool nu = true;
    CompDrawDamage(int damageNum, Entity* oldP) {
        drawNum = damageNum;
        oldPar = oldP;
        compoName = "CompDrawDamage";
    }
    void update(float fElapsedTime) {
        if (nu) {
            nu = false;
            return;
        }
        for (int i = 0; i < parent->scene->eList.size(); i++) {
            if (parent->scene->eList.at(i) == parent) {
                continue;
            }
            if (!parent->scene->eList.at(i)->removeMe) {
                CompDrawDamage* other = dynamic_cast<CompDrawDamage*>(parent->scene->eList.at(i)->getComponent("CompDrawDamage"));
                if (other) {
                    if (RectRectCollision({ parent->pos.x,parent->pos.y,parent->size.x,parent->size.y }, { parent->scene->eList.at(i)->pos.x,parent->scene->eList.at(i)->pos.y,parent->scene->eList.at(i)->size.x,parent->scene->eList.at(i)->size.y }))
                    {
                        if (other->oldPar == oldPar) {
                            other->drawNum += drawNum;
                            parent->removeMe = true;
                        }

                    }
                }

            }


        }
    }
    void draw() {
        DrawText(TextFormat("%i", drawNum), parent->pos.x + 2, parent->pos.y - 13, 4, { 100,0,0,255 });
        DrawText(TextFormat("%i", drawNum), parent->pos.x + 1, parent->pos.y - 14, 4, RED);
    }
};
class CompHealth : public Component {
public:
    int maxHP;
    int health;

    int iF = 0;
    float iFrameCount = 0;
    float iFrameTimer = 0;

    float timeSinceLastHit = 10;
    int recentDamage = 0;
    bool removeOnDeath;
    CompHealth(int maxHp, float Iframes = 0, bool removeondeath = true) {
        maxHP = maxHp;
        health = maxHP;
        compoName = "CompHealth";
        removeOnDeath = removeondeath;
        iF = (int)(Iframes * 100);
        iFrameCount = iF / 100.0f;
    }
    void update(float fElapsedTime) {
        if (iFrameTimer >= 0) {
            iFrameTimer -= fElapsedTime;

        }
        timeSinceLastHit += fElapsedTime;
    }
    void takeDamage(int dmg) {
        if (iFrameTimer < 0) {
            health -= dmg;
            iFrameTimer = iFrameCount;
            timeSinceLastHit = 0;
            recentDamage -= dmg;
            Entity* temp = new Entity(parent->pos + Vec2(0, -parent->size.y), { 40,40 }, DECOR, { new CompRemoveTimer(1), new CompDrawDamage(dmg, parent) });
            temp->scene = parent->scene;
            temp->start();
            parent->scene->addEntity(temp);
        }



        if (removeOnDeath && health <= 0) {
            parent->removeMe = true;
        }
    }
    void forceDamage(int dmg) {
        health -= dmg;
    }
    void onRemove() {

    }
    void draw() {
        if (timeSinceLastHit < 1) {
            //DrawText(TextFormat("%i", recentDamage), parent->pos.x + 1, parent->pos.y - parent->size.y / 2 - 11, 4, { 100,0,0,255 });
            //DrawText(TextFormat("%i", recentDamage), parent->pos.x, parent->pos.y - parent->size.y / 2 - 12, 4, RED);

        }
        else {
            recentDamage = 0;
        }
    }
    void heal(int heal) {
        health += heal;
        if (health > maxHP) {
            health = maxHP;
        }
    }


};
class CompHurtOnContact : public Component {
public:
    CompBasicEntityCol* myECol;
    vector<layer> targetLayers;
    int damage;
    bool removeOnHit = false;
    CompHurtOnContact(vector<layer> targetLayer, int damage1 = 1, bool removeOnContact = false) {
        targetLayers = targetLayer;
        compoName = "CompHurtOnContact";
        damage = damage1;
        removeOnHit = removeOnContact;
    }


    void start() {
        myECol = dynamic_cast<CompBasicEntityCol*>(parent->getComponent("CompBasicEntityCol"));
        if (myECol) {

        }
        else {
            myECol = dynamic_cast<CompCircleEntityCol*>(parent->getComponent("CompCircleEntityCol"));
        }
    }
    void update(float fElapsedTime) {

        if (myECol) {
            for (int i = 0; i < myECol->onCol.size(); i++) {
                bool wGamer = false;
                for (int j = 0; j < targetLayers.size(); j++) {
                    if (targetLayers.at(j) == myECol->onCol.at(i)->myLayer) {
                        wGamer = true;
                    }
                }
                if (wGamer == true) {
                    CompHealth* yourHealth = dynamic_cast<CompHealth*>(myECol->onCol.at(i)->getComponent("CompHealth"));;
                    if (yourHealth) {
                        if (removeOnHit) {
                            parent->removeMe = true;
                        }

                        yourHealth->takeDamage(1);
                    }
                }

            }
        }

    }

};
class CompBomb : public Component {
public:
    float endSize = 100;
    float curSize = 0;
    float timeToExpand = .3;
    float timeAtMax = 0;
    float timeToRetract = .5;
    float timer = 0;
    int stage = 0;
    CompBomb(float size, float expandTime, float stayTime, float retractTime) {
        compoName = "CompBomb";
        endSize = size;
        timeToExpand = expandTime;
        timeAtMax = stayTime;
        timeToRetract = retractTime;
    }
    void update(float fElapsedTime) {
        timer += fElapsedTime;
        if (stage == 0) {
            curSize = endSize * (timer / timeToExpand);
            if (timer >= timeToExpand) {
                stage++;
                timer = 0;
                curSize = endSize;
            }
        }
        else if (stage == 1) {

            if (timer >= timeAtMax) {
                stage++;
                
            }
        }
        else if (stage == 2) {
            curSize = endSize - ((timer / timeToRetract) * endSize);
            if (timer >= timeToRetract) {
                curSize = 0;
                timer = 0;
                stage++;
            }
        }
        else if (stage == 3) {
            parent->removeMe = true;
        }

        parent->size.x = curSize;
        parent->size.y = 0;
        
    }
    void draw() {
        DrawCircle(parent->pos.x, parent->pos.y, curSize / 2, BLACK);
        DrawCircleLines(parent->pos.x, parent->pos.y, curSize / 2, RED);
    }
};
class CompExplodeOnDeath : public Component {
public:
    float endSize = 100;
    float timeToExpand = .3;
    float timeAtMax = 0;
    float timeToRetract = .5;
    CompExplodeOnDeath(float size, float expandTime, float stayTime, float retractTime) {
        endSize = size;
        timeToExpand = expandTime;
        timeAtMax = stayTime;
        timeToRetract = retractTime;
        compoName = "CompExplodeOnDeath";
    }
    void onRemove() {

        Entity* temp = new Entity(parent->pos, { 0,0 }, BULLET, { new CompBomb(endSize,timeToExpand,timeAtMax,timeToRetract), new CompCircleEntityCol({PLAYER}) }, "NOSAVE", true);
        CompHurtOnContact* myHurt = dynamic_cast<CompHurtOnContact*>(parent->getComponent("CompHurtOnContact"));
        if (myHurt) {

            temp->addComponent(new CompHurtOnContact(myHurt->targetLayers, myHurt->damage, false)); //##############################################################################################################################add circle compatability
        }
        temp->scene = parent->scene;
        temp->start();
        parent->scene->addEntity(temp);
    }
};



class CompParticleSystem : public Component {
public:
    vector<Entity*> myParticles;

    CompParticleSystem() {

    }
    virtual void start() {
        for (int i = 0; i < myParticles.size(); i++) {
            myParticles.at(i)->scene = parent->scene;
            myParticles.at(i)->start();
        }
    }
    virtual void update(float fElapsedTime) {
        for (int i = 0; i < myParticles.size(); i++) {
            myParticles.at(i)->update(fElapsedTime);
            if (myParticles.at(i)->removeMe) {
                myParticles.erase(myParticles.begin() + i);
                i--;
                continue;
            }
        }

    }
    virtual void draw() {
        for (int i = 0; i < myParticles.size(); i++) {
            myParticles.at(i)->draw();
        }
    }
};
class CompParticleThrust : public CompParticleSystem {
public:
    Vec2 dir = { 0, -1 };
    bool on = true;
    float speed = 180;
    Color myColor = RED;
    vector<float> timeAlive;
    CompParticleThrust(Vec2 myDir) {
        dir = myDir;
        compoName = "CompParticleThrust";
    }

    virtual void update(float fElapsedTime) {
        if (on) {
            myParticles.push_back(new Entity(parent->pos + Vec2(rand() % 3 - 2, rand() % 3 - 2), { 0,0 }, DECOR, {}, "NOSAVE", true));
            myParticles.at(myParticles.size() - 1)->vel = dir.normalize().rotate((rand() % 628 / 100.0f - 3.14) / 10) * speed + parent->vel / 2;
            myParticles.at(myParticles.size() - 1)->scene = parent->scene;
            myParticles.at(myParticles.size() - 1)->start();
            timeAlive.push_back((rand() % 5) / 20.0f);
        }
        for (int i = 0; i < timeAlive.size(); i++) {
            timeAlive.at(i) -= fElapsedTime;
            if (timeAlive.at(i) < 0) {
                timeAlive.erase(timeAlive.begin() + i);
                myParticles.erase(myParticles.begin() + i);
            }
        }


        CompParticleSystem::update(fElapsedTime);
    }
    virtual void draw() {
        for (int i = 0; i < myParticles.size(); i++) {

            unsigned char temp2 = (timeAlive.at(i) * 1300 / 2 + 155);

            DrawRectangle(myParticles.at(i)->pos.x, myParticles.at(i)->pos.y, 3, 3, { myColor.r,myColor.g,myColor.b,temp2 });
        }
    }
};

class CompParticleImplode:public CompParticleSystem {
public:
    bool powering = true;
    float offSet= 10;
    CompParticleImplode() {
        compoName = "CompParticleImplode";
    }
    void start() {
        for (int i = 0; i < 40; i++) {
            float ang = rand() % 360 / 180.0f * PI;
            Vec2 dir = Vec2(cos(ang), sin(ang));
            
            myParticles.push_back(new Entity(parent->pos+(dir*offSet) , {0,0}, DECOR, {new CompRemoveTimer(.3f)}, "NOSAVE", true));
            myParticles.at(myParticles.size() - 1)->vel = dir * -50;
            myParticles.at(myParticles.size() - 1)->scene = parent->scene;
            myParticles.at(myParticles.size() - 1)->start();
        }
    }
    void update(float fElapsedTime) {
        
        if (powering) {
            for (int i = 0; i < 2; i++) {
                float ang = rand() % 360 / 180.0f * PI;
                Vec2 dir = Vec2(cos(ang), sin(ang));

                myParticles.push_back(new Entity(parent->pos + (dir * offSet), { 0,0 }, DECOR, { new CompRemoveTimer(.3f) }, "NOSAVE", true));
                myParticles.at(myParticles.size() - 1)->vel = dir * -50;
                myParticles.at(myParticles.size() - 1)->scene = parent->scene;
                myParticles.at(myParticles.size() - 1)->start();
            }
            
            
        }
        CompParticleSystem::update(fElapsedTime);
    }
    void draw() {
        for (int i = 0; i < myParticles.size(); i++) {
            DrawPixel(myParticles.at(i)->pos.x, myParticles.at(i)->pos.y, RED);
        }
        
        
    }

};
class CompParticleBul : public CompParticleSystem {
public:
    Color myColor = MAGENTA;
    vector<float> timeAlive;
    CompParticleBul() {
        
        compoName = "CompParticleBul";
    }
    void start() {
        for (int i = 0; i < 40; i++) {
            Vec2 dir = Vec2(rand() % 10-5, rand() % 10-5).normalize();
            if (dir == Vec2(0, 0)) {
                dir = { 1,1 };
            }
            myParticles.push_back(new Entity(parent->pos + Vec2(rand() % 3 - 2, rand() % 3 - 2), { 0,0 }, DECOR, {new CompRemoveTimer(.15f)}, "NOSAVE", true));
            myParticles.at(myParticles.size() - 1)->vel = dir*50;
            myParticles.at(myParticles.size() - 1)->scene = parent->scene;
            myParticles.at(myParticles.size() - 1)->start();
        }
        
        
    }
    void draw() {
        for (int i = 0; i < myParticles.size(); i++) {
            DrawPixel(myParticles.at(i)->pos.x, myParticles.at(i)->pos.y, myColor);
        }
        
    }
};
class CompParicleBulTemp : public Component {
public:
    CompParicleBulTemp() {

    }
    void onRemove() {
        Entity* temp = new Entity(parent->pos, parent->size, DECOR, { new CompParticleBul(), new CompRemoveTimer(1)}, "NOSAVE", true);
        temp->scene = parent->scene;
        temp->start();
        parent->scene->addEntity(temp);
    }

};
class CompRemoveOnHit : public Component {
public:
    CompBasicEntityCol* myECol;
    CompRemoveOnHit() {
        compoName = "CompRemoveOnHit";
    }
    void start() {

        myECol = dynamic_cast<CompBasicEntityCol*>(parent->getComponent("CompBasicEntityCol"));






    }
    void update(float fElapsedTime) {
        if (myECol->onCol.size() != 0) {
            parent->removeMe = true;;
        }
    }
};
class CompRemoveOnGroundHit : public Component {
public:
    CompGroundCol* myGCol;
    CompRemoveOnGroundHit() {
        compoName = "CompRemoveOnGroundHit";
    }
    void start() {

        myGCol = dynamic_cast<CompGroundCol*>(parent->getComponent("CompGroundCol"));






    }
    void update(float fElapsedTime) {
        if (myGCol->resDir.getMagnitude() != 0) {
            parent->removeMe = true;;
        }
    }
};
class CompJumpTrail :public Component {
public:
    vector<Vec2> lineTemp;
    vector<Color>lineColor;
    float frameskip = 0.0f;
    CompJumpTrail() {

    }
    void update() {
        if (frameskip <= 0) {
            frameskip = 1;

            lineTemp.push_back(parent->pos);
            if (parent->vel.y > 0) {
                lineColor.push_back(RED);
            }
            else {
                lineColor.push_back(GREEN);
            }
        }
        frameskip -= fElapsedTime * 60;


        if (lineTemp.size() > 50) {
            lineTemp.erase(lineTemp.begin());
            lineColor.erase(lineColor.begin());
        }

        for (int i = 0; i < lineTemp.size() - 1; i++) {
            DrawLine(lineTemp.at(i).x, lineTemp.at(i).y, lineTemp.at(i + 1).x, lineTemp.at(i + 1).y, lineColor.at(i));
        }
    }
};


class CompDrawTurret :public Component {
public:
    CompDrawTurret() {

    }
    void draw() {

    }
};

class CompRoll : public Component {
public:
    int wallBounceLeft;
    CompGroundCol* myGCol;
    Vec2 tempVel = { 0,0 };
    CompRoll(int WallBounceNum) {
        wallBounceLeft = WallBounceNum;
        compoName = "CompRoll";
    }
    void start() {
        myGCol = dynamic_cast<CompGroundCol*>(parent->getComponent("CompGroundCol"));
        tempVel = parent->vel;
    }
    void update(float fElapsedTime) {

        if (wallBounceLeft < 1) {
            if (myGCol->resDir.x != 0) {
                parent->removeMe = true;
            }
        }
        else {
            if (myGCol->resDir.x != 0) {
                wallBounceLeft--;
                parent->vel.x = tempVel.x * -1;
            }
        }
        if (parent->vel == Vec2(0, 0) && myGCol->resDir.y != 0) {
            parent->removeMe = true;
        }
        tempVel = parent->vel;
    }
};
vector<Texture2D> entityTextures = { };
vector<string> entityTexturePath = { "Player.png","SmallShot.png","SadFace.png","Snail.png",
"Pellet.png", "Dragonfly.png", "Frog.png", "Bat.png","FunnyFace.png", "StupidCat.png", "AngerDog.png",
"Key.png", "BigLock.png", "OrangeSpike.png", "SpiralNotebook.png", "WBug.png"};
class CompSprite : public Component {
public:
    Vec2 offSet;
    int indexNum;
    Texture2D* mySprite;

    Color myTint;
    bool isSad;
    float sizeMult;
    CompSprite(string pathToSprite, Vec2 offSeT, Color tint = WHITE, float size = 1) {
        isSad = true;

        for (int i = 0; i < entityTexturePath.size(); i++) {

            if (entityTexturePath.at(i) == pathToSprite) {
                indexNum = i;
                isSad = false;

                break;
            }
        }
        sizeMult = size;
        myTint = tint;
        offSet = offSeT;
        compoName = "CompSprite";

    }

    virtual void start() {

        if (!isSad) {
            mySprite = &entityTextures.at(indexNum);
        }
    }
    virtual void draw() {
        if (!isSad) {

            int frameWidth = mySprite->width;
            int frameHeight = mySprite->height;
            Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
            Rectangle destRec = { parent->pos.x + offSet.x, parent->pos.y + offSet.y, frameWidth*sizeMult, frameHeight*sizeMult };
            DrawTexturePro(*mySprite, sourceRec, destRec, { (float)(frameWidth*sizeMult / 2),(float)(frameHeight*sizeMult / 2)}, 0, myTint);

        }

    }
};
class CompSpriteFaceVel : public CompSprite {
public:
    Vec2 prevVel = { 0,0 };
    bool trackX;
    bool trackY;
    CompSpriteFaceVel(string pathToSprite, Vec2 offSeT, bool trackXVel, bool trackYVel, Color tint = WHITE, float size =1) :CompSprite(pathToSprite, offSeT, tint, size) {
        trackX = trackXVel;
        trackY = trackYVel;
        compoName = "CompSpriteFaceVel";

    }

    virtual void draw() {

        if (!(parent->vel == Vec2(0, 0))) {
            prevVel = parent->vel;
        }
        if (trackX && trackY) {
            if (!isSad) {
                int frameWidth = mySprite->width;
                int frameHeight = mySprite->height;
                Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
                Rectangle destRec = { parent->pos.x + offSet.x, parent->pos.y + offSet.y, frameWidth * sizeMult, frameHeight * sizeMult };
                DrawTexturePro(*mySprite, sourceRec, destRec, { (float)(frameWidth * sizeMult / 2),(float)(frameHeight * sizeMult / 2) }, (prevVel.getAngle() / PI) * 180, myTint);

            }
        }
        else if (trackX) {
            if (mySprite) {

            }
            else {
                return;
            }
            if (parent->vel.x < 0) {

                int frameWidth = mySprite->width;
                int frameHeight = mySprite->height;
                Rectangle sourceRec = { 0.0f, 0.0f, -(float)frameWidth, (float)frameHeight };
                Rectangle destRec = { parent->pos.x + offSet.x, parent->pos.y + offSet.y, frameWidth * sizeMult, frameHeight * sizeMult };
                DrawTexturePro(*mySprite, sourceRec, destRec, { (float)(frameWidth * sizeMult / 2),(float)(frameHeight * sizeMult / 2) }, 0, myTint);
            }
            else {

                int frameWidth = mySprite->width;
                int frameHeight = mySprite->height;
                Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
                Rectangle destRec = { parent->pos.x + offSet.x, parent->pos.y + offSet.y, frameWidth * sizeMult, frameHeight * sizeMult };
                DrawTexturePro(*mySprite, sourceRec, destRec, { (float)(frameWidth * sizeMult / 2),(float)(frameHeight * sizeMult / 2) }, 0, myTint);
            }
        }



    }
};
class CompSpriteFacePlayer : public CompSprite {
public:
    Vec2 prevVel = { 0,0 };
    bool trackX;
    bool trackY;
    CompSpriteFacePlayer(string pathToSprite, Vec2 offSeT, bool trackXPlayer, bool trackYPlayer, Color tint = WHITE) :CompSprite(pathToSprite, offSeT, tint) {
        trackX = trackXPlayer;
        trackY = trackYPlayer;
        compoName = "CompSpriteFaceVel";

    }

    virtual void draw() {


        if (trackX && trackY) {
            if (!isSad) {
                int frameWidth = mySprite->width;
                int frameHeight = mySprite->height;
                Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
                Rectangle destRec = { parent->pos.x + offSet.x, parent->pos.y + offSet.y, frameWidth, frameHeight };
                DrawTexturePro(*mySprite, sourceRec, destRec, { (float)(frameWidth / 2),(float)(frameHeight / 2) }, ((playerPos - parent->pos).getAngle() / PI) * 180, myTint);

            }
        }
        else if (trackX) {
            if (mySprite) {

            }
            else {
                return;
            }
            if ((playerPos - parent->pos).x < 0) {

                int frameWidth = mySprite->width;
                int frameHeight = mySprite->height;
                Rectangle sourceRec = { 0.0f, 0.0f, -(float)frameWidth, (float)frameHeight };
                Rectangle destRec = { parent->pos.x + offSet.x, parent->pos.y + offSet.y, frameWidth, frameHeight };
                DrawTexturePro(*mySprite, sourceRec, destRec, { (float)(frameWidth / 2),(float)(frameHeight / 2) }, 0, myTint);
            }
            else {

                int frameWidth = mySprite->width;
                int frameHeight = mySprite->height;
                Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
                Rectangle destRec = { parent->pos.x + offSet.x, parent->pos.y + offSet.y, frameWidth, frameHeight };
                DrawTexturePro(*mySprite, sourceRec, destRec, { (float)(frameWidth / 2),(float)(frameHeight / 2) }, 0, myTint);
            }
        }



    }
};

Entity* createBullet(Vec2 pos, Vec2 size, Vec2 vel, vector<layer> targetLayers, float timeAlive) {
    Entity* temp = new Entity(pos, size, BULLET, { new CompRemoveOnGroundHit(),new CompBasicEntityCol(targetLayers),new CompHurtOnContact(targetLayers), new CompRemoveTimer(timeAlive), new CompGroundCol(), new CompSprite("Pellet.png",{0,0}) }, "NOSAVE", true);
    temp->vel = vel;
    return temp;
}
Entity* createRocket(Vec2 pos, Vec2 projectileSize, Vec2 startVel, vector<layer> targetLayer, float timeAlive, float explosionSize, float explodeGrowTime, float explodeStayTime, float explodeShrinkTime) {
    Entity* temp = new Entity(pos, projectileSize, BULLET, { new CompRemoveOnGroundHit(), new CompExplodeOnDeath(explosionSize,explodeGrowTime,explodeStayTime,explodeShrinkTime),new CompBasicEntityCol(targetLayer),new CompHurtOnContact(targetLayer,1,true), new CompRemoveTimer(timeAlive), new CompGroundCol(),new CompSprite("Pellet.png",{0,0})}, "NOSAVE", true);
    temp->vel = startVel;
    temp->addComponent(new CompParticleThrust(startVel.normalize() * -1));
    return temp;
}
Entity* createRollingBullet(Vec2 pos, Vec2 size, Vec2 vel, vector<layer> targetLayers, float timeAlive, float gravityStrength, int wallBounceNum) {
    Entity* temp = new Entity(pos, size, BULLET, { new CompRoll(wallBounceNum), new CompBasicEntityCol(targetLayers),new CompHurtOnContact(targetLayers), new CompRemoveTimer(timeAlive),new CompGravity(gravityStrength), new CompGroundCol(),new CompSprite("Pellet.png",{0,0},ORANGE) }, "NOSAVE", true);
    temp->vel = vel;
    return temp;
}
class CompBasicGun : public Component {
public:
    float coolDownTime = .6;
    float coolDownTimer = 0;


    float burstTime = .2;
    float burstTimer = 0;

    int burstNum = 3;
    int burstCount = 0;

    bool isShooting = true;

    float bulletSpeed;

    bool aimAtPlayerX;
    bool aimAtPlayerY;

    bool FixedBurst;
    float secondsAhead;
    Vec2* targetPos;
    Vec2* targetVel;
    Vec2 aimDir;

    int shotType;
    CompBasicGun(float CDTime, float bulletSpeedd, int bulletType = 0, float BTime = 0, int burstNumber = 1, float aimSecondsAheadPlayer = 0, Vec2 aimDIR = { 0,0 }, bool targetPlayerX = true, bool targetPlayerY = true, bool burstFixed = false) {
        targetPos = &playerPos;
        targetVel = &playerVel;
        coolDownTime = CDTime;
        burstTime = BTime;
        burstNum = burstNumber;
        bulletSpeed = bulletSpeedd;
        compoName = "CompBasicGun";
        aimDir = aimDIR.normalize();
        aimAtPlayerX = targetPlayerX;
        aimAtPlayerY = targetPlayerY;

        FixedBurst = burstFixed;
        secondsAhead = aimSecondsAheadPlayer;
        shotType = bulletType;
    }

    void start() {
        targetPos = &playerPos;
        targetVel = &playerVel;
    }

    virtual void update(float fElapsedTime) {

        aimCalc();


        if (burstCount <= 0) {
            coolDownTimer -= fElapsedTime;
        }

        if (isShooting && coolDownTimer < 0) {
            coolDownTimer = coolDownTime;

            burstCount = burstNum;
            burstTimer = 0;
        }


        burstTimer -= fElapsedTime;
        if (burstCount > 0 && burstTimer < 0) {


            burstCount--;
            burstTimer = burstTime;

            fire();
        }


    }
    virtual void aimCalc() {
        if (FixedBurst && burstCount > 0) {
            return;
        }
        Vec2 towardPlayer = playerPos - parent->pos;
        if (aimAtPlayerX && aimAtPlayerY) {
            if (secondsAhead > 0) {
                aimDir = ((*targetPos + *targetVel * secondsAhead) - parent->pos);

                aimDir = aimDir.normalize();
            }
            else {
                aimDir = (*targetPos - parent->pos).normalize();
            }
        }

        if (aimAtPlayerX && !aimAtPlayerY) {
            aimDir = { abs(aimDir.x) * sgn(towardPlayer.x),aimDir.y };
        }
        else if (aimAtPlayerY && !aimAtPlayerX) {
            aimDir = { aimDir.x,abs(aimDir.y) * sgn(towardPlayer.y) };
        }



    }
    virtual void drawDebugging() {

        DrawLine(parent->pos.x, parent->pos.y, parent->pos.x + aimDir.x * parent->size.x / 2, parent->pos.y + aimDir.y * parent->size.y / 2, RED);
    }
    virtual void fire() {
        // parent->scene->addEntity(createBullet(parent->pos, { 4,4 }, aimDir * 100, { PLAYER }, 10));
        if (shotType == 0) {
            parent->scene->addEntity(createBullet(parent->pos, { 4,4 }, aimDir * bulletSpeed, { PLAYER }, 5));
        }
        else if (shotType == 1) {
            parent->scene->addEntity(createRollingBullet(parent->pos, { 8,8 }, aimDir * bulletSpeed, { PLAYER }, 20, 300, 3));
        }
        else if (shotType == 2) {
            parent->scene->addEntity(createRocket(parent->pos, { 9,9 }, aimDir * bulletSpeed, { PLAYER }, 20, 100, .3,0,.5));
        }
    }
};


class CompSpreadGun : public CompBasicGun {
public:
    int spreadNum;
    float ang = PI / 6;
    CompSpreadGun(float CDTime, float bulllSpeed, int spreadNumber, int MshotType, float angleBetween, float BTime = 0, float burstNumber = 1) :CompBasicGun(CDTime, bulllSpeed, MshotType, BTime, burstNumber) {
        targetPos = &playerPos;
        spreadNum = spreadNumber;

        ang = angleBetween;
        compoName = "CompSpreadGun";
    }

    virtual void fire() {

        Vec2 aimTemp = { 0,0 };

        for (int i = 0; i < spreadNum; i++) {
            aimTemp = aimDir.rotate((i - ((spreadNum - 1) / 2)) * ang);
            if (shotType == 0) {
                parent->scene->addEntity(createBullet(parent->pos, { 4,4 }, aimTemp * bulletSpeed, { PLAYER }, 5));
            }
            else if (shotType == 1) {
                parent->scene->addEntity(createRollingBullet(parent->pos, { 8,8 }, aimTemp * bulletSpeed, { PLAYER }, 20, 300, 3));
            }
            else if (shotType == 2) {
                parent->scene->addEntity(createRocket(parent->pos, { 9,9 }, aimTemp * bulletSpeed, { PLAYER }, 20, 100, .3, 0, .5));
            }
        }

    }
};

class CompZigZagAI : public Component {
public:
    float t = 0;
    Vec2 orPos = { 0,0 };

    int amplitude = 40;
    CompZigZagAI() {
        amplitude = 40;
        compoName = "CompZigZagAI";
    }
    void start() {
        orPos = parent->pos;
    }
    void drawDebugging() {
        DrawLine(parent->pos.x + 5, parent->pos.y + amplitude, parent->pos.x - 5, parent->pos.y + amplitude, { 255,0,0,100 });
        DrawLine(parent->pos.x + 5, parent->pos.y - amplitude, parent->pos.x - 5, parent->pos.y - amplitude, { 255,0,0,100 });

    }


    void update(float fElapsedTime) {

        parent->pos.y = orPos.y + (cos(worldTimer) * amplitude);
    }
};
class CompBatAI : public Component {
public:
    CompGroundCol* myGCol;


    float flightHeight = 75;

    float curH = 15;
    bool up = false;;


    Vec2 dirTarget = { 0,0 };
    float timer = 0;


    bool onPlayer = false;

    float groundHeight = 0;
    CompBatAI(int hoverHeight) {
        flightHeight = hoverHeight;
        compoName = "CompBatAI";

    }

    void start() {
        myGCol = dynamic_cast<CompGroundCol*>(parent->getComponent("CompGroundCol"));
    }
    void update(float fElapsedTime) {
        Ray2D groundCheck(parent->pos, { 0,1 });
        RayHit ground = groundCheck.intersect(*parent->scene, flightHeight + curH);
        float height = 0;



        if (ground.objType != -1) {
            height = ground.hitPos.y - flightHeight;
            groundHeight = ground.hitPos.y;
            if (parent->pos.y < height - curH) {
                up = false;
            }
            if (parent->pos.y > height + curH) {
                up = true;
            }
        }
        else {
            up = false;
        }
        if (myGCol->resDir.y < 0) {
            up = true;
        }
        if (myGCol->resDir.y > 0) {
            up = false;
        }
        if (myGCol->resDir.x != 0)
        {
            dirTarget.x = -dirTarget.x;
        }

        if (up) {

            parent->vel.y -= fElapsedTime * 300;
        }
        else {

            parent->vel.y += fElapsedTime * 300;
        }




        parent->vel.y -= parent->vel.y * fElapsedTime * 3;

        parent->vel.x -= parent->vel.x * fElapsedTime;
        parent->vel.x -= sgn(parent->vel.x) * fElapsedTime;



        timer -= fElapsedTime;
        if (timer < 0) {
            timer = 2;
            dirTarget = (playerPos - parent->pos).normalize();
        }
        
        parent->vel.x += sgn(dirTarget.x) * fElapsedTime * 100;

    }
    void drawDebugging() {
        DrawLine(parent->pos.x, parent->pos.y, parent->pos.x, parent->pos.y + flightHeight + curH, { 255,161,0,100 });
        DrawCircle(parent->pos.x, groundHeight, 2, ORANGE);

    }
};
class CompWalkAI :public Component {
public:
    bool walkOffLedge;
    CompGroundCol* myGCol;
    int walkDir = -1;
    float drag;
    int walkSpeed;
    int rangeCheck;
    CompWalkAI(int wSpeed, float dragg, int range = 0) {
        compoName = "CompWalkAI";
        walkSpeed = wSpeed;
        drag = dragg;
        rangeCheck = range;
    }

    void start() {
        myGCol = dynamic_cast<CompGroundCol*>(parent->getComponent("CompGroundCol"));
    }
    void update(float fElapsedTime) {
        Ray2D groundCheck(parent->pos + Vec2(parent->size.x / 2 * walkDir, 0), { 0,parent->size.y });
        RayHit ground = groundCheck.intersect(*parent->scene, parent->size.getMagnitude() / 2 + .5 + rangeCheck);

        if (ground.objType == -1 || myGCol->resDir.x != 0) {
            walkDir = -walkDir;
        }
        parent->vel.x += walkDir * walkSpeed * fElapsedTime;
        parent->vel.x -= (parent->vel.x * drag) * fElapsedTime;

    }

};
class CompEyeAI : public Component {
public:
    CompGroundCol* myGCol;
    float speed;

    Vec2 tempVel;
    CompEyeAI(float sped) {
        speed = sped;

        compoName = "CompEyeAI";
    }

    void start() {
        myGCol = dynamic_cast<CompGroundCol*>(parent->getComponent("CompGroundCol"));
    }
    void update(float fElapsedTime) {


        parent->vel += (playerPos - parent->pos).normalize() * speed * fElapsedTime;
    }
};
class CompDashAI : public Component {
public:

    float dashCoolDown;
    float dashTimer;
    float dashPower;

    bool aimAtPlayerX;
    bool aimAtPlayerY;
    bool isDashing = true;
    Vec2 dashDir;
    CompDashAI(float coolDown, float speed, bool aimPlayerX, bool aimPlayerY, Vec2 baseDir) {
        dashCoolDown = coolDown;
        dashTimer = coolDown;
        dashPower = speed;
        aimAtPlayerX = aimPlayerX;
        aimAtPlayerY = aimPlayerY;
        dashDir = baseDir.normalize();
        compoName = "CompDashAI";
    }

    void update(float fElapsedTime) {
        calcDashDir();
        if (isDashing) {
            dashTimer -= fElapsedTime;
            if (dashTimer < 0) {
                dashTimer = dashCoolDown;
                parent->vel += dashDir * dashPower;
            }
        }
    }
    void calcDashDir() {
        Vec2 towardPlayer = playerPos - parent->pos;
        if (aimAtPlayerX && !aimAtPlayerY) {
            dashDir = { abs(dashDir.x) * sgn(towardPlayer.x),dashDir.y };
        }
        else if (aimAtPlayerY && !aimAtPlayerX) {
            dashDir = { dashDir.x,abs(dashDir.y) * sgn(towardPlayer.y) };
        }
        else if (aimAtPlayerX && aimAtPlayerY) {
            dashDir = towardPlayer.normalize();
        }

    }


};
class CompSave : public Component {
public:
    float tempTimer = 0;
    CompSave() {
        compoName = "CompSave";
    }
    void update(float fElapsedTime) {
        tempTimer -= fElapsedTime;
        if (tempTimer > 0) {
            DrawCircle(parent->pos.x, parent->pos.y, 10, ORANGE);
        }
        if (IsKeyPressed(KEYBIND_DOWN) && (playerPos - parent->pos).getMagnitude() < 20) {
            tempTimer = 1;
            saveLevelAs(*parent->scene->inLevel, currentSaveFile);
        }
    }
    void draw() {
        DrawText("Press down", parent->pos.x - 30, parent->pos.y - 30, 1, WHITE);
        if (tempTimer > 0) {
            DrawRectangle(parent->pos.x - 40 / 2, parent->pos.y - 40 / 2, 40, 40, RED);
        }
        
    }
};
class CompPhysic : public Component {
public:
    CompGroundCol* myGCol;
    float airDrag;
    float airFriction;

    float groundDrag;
    float groundFriction;

    float bounce;
    bool bounceGround;
    bool bounceWall;

    bool grounded = false;

    Vec2 tempVel = { 0,0 };
    CompPhysic(float aDrag, float aFric, float gDrag, float gFric, float bouncyNess, bool bounceWalll, bool bounceGroundd) {
        airDrag = aDrag;
        airFriction = aFric;
        groundDrag = gDrag;
        groundFriction = gFric;
        grounded = false;
        bounceGround = bounceGroundd;
        bounceWall = bounceWalll;
        bounce = bouncyNess;
        compoName = "CompPhysic";
    }

    void start() {
        myGCol = dynamic_cast<CompGroundCol*>(parent->getComponent("CompGroundCol"));
    }
    void update(float fElapsedTime) {
        if (myGCol) {
            float tempY = parent->vel.y;
            float tempX = parent->vel.x;
            if (bounceGround && myGCol->resDir.y != 0) {
                tempY = tempVel.y * -bounce;
            }
            if (bounceWall && myGCol->resDir.x != 0) {
                tempX = tempVel.x * -bounce;
            }
            parent->vel = { tempX,tempY };
            if (myGCol->resDir.y == -1) {
                grounded = true;
            }
            else {
                grounded = false;
            }

        }
        if (grounded) {
            parent->vel.x -= parent->vel.x * groundDrag * fElapsedTime;
            parent->vel.x -= parent->vel.x * groundFriction * fElapsedTime;
        }
        else {
            parent->vel -= parent->vel * airDrag * fElapsedTime;
            parent->vel -= parent->vel.normalize() * airFriction * fElapsedTime;
        }
        tempVel = parent->vel;
    }
};
class CompTreatEntityAsGround : public Component {
public:
    Vec2 resDir;
    vector<layer> mLayers;
    CompTreatEntityAsGround(vector<layer> myLayers) {
        mLayers = myLayers;
        compoName = "CompTreatEntityAsGround";
    }
    void start() {

    }
    void update(float fElapsedTime) {
        resDir = { 0,0 };
        for (int i = 0; i < parent->scene->eList.size(); i++) {
            if (parent->scene->eList.at(i) == parent) {
                continue;
            }
            bool skipCalc = true;
            for (int j = 0; j < mLayers.size(); j++) {

                if (parent->scene->eList.at(i)->myLayer == mLayers.at(j)) {
                    skipCalc = false;
                }
            }
            if (skipCalc) {
                continue;
            }
            Entity* temp = parent->scene->eList.at(i);

            Rectangle h2 = { temp->pos.x - temp->size.x / 2, temp->pos.y - temp->size.y / 2, temp->size.x,temp->size.y };
            Rectangle h1 = { parent->pos.x - parent->size.x / 2, parent->pos.y - parent->size.y / 2, parent->size.x,parent->size.y };

            Rectangle h1X = { h1.x + parent->vel.x * fElapsedTime,h1.y,h1.width,h1.height };
            Rectangle h1Y = { h1.x,h1.y + parent->vel.y * fElapsedTime,h1.width,h1.height };

            if (RectRectCollision(h1X, h2)) {

                if (parent->vel.x > 0) {
                    parent->pos.x = h2.x - h1.width / 2;
                    parent->vel.x = 0;
                    resDir.x = -1;
                }
                if (parent->vel.x < 0) {
                    parent->pos.x = h2.x + h2.width + h1.width / 2;
                    parent->vel.x = 0;
                    resDir.x = 1;
                }
            }
            else if (RectRectCollision(h1Y, h2)) {
                if (parent->vel.y > 0) {
                    parent->pos.y = h2.y - h1.height / 2;
                    parent->vel.y = 0;
                    resDir.y = -1;
                }
                if (parent->vel.y < 0) {
                    parent->pos.y = h2.y + h2.height + h1.height / 2;
                    parent->vel.y = 0;
                    resDir.y = 1;
                }
            }




        }

    }
};
class CompLockedDoor : public Component {
public:
    int range = 5;
    CompLockedDoor() {

    }
    void start() {


    }
    void update(float fElapsedTime) {
        for (int i = 0; i < parent->scene->eList.size(); i++) {
            if (parent->scene->eList.at(i)->type == "Key") {
                Vec2 tempDist = (parent->scene->eList.at(i)->pos - parent->pos);

                if (abs(tempDist.x) < range && abs(tempDist.y) < range) {
                    parent->removeMe = true;
                    parent->scene->eList.at(i)->removeMe = true;
                    break;

                }
            }
            if (parent->scene->eList.at(i)->type == "Player") {

            }
        }
    }
    void drawDebugging() {
        DrawRectangleLines(parent->pos.x - (range * 2) / 2, parent->pos.y - (+range * 2) / 2, (range * 2), (range * 2), { 255,255,255,100 });
    }
};
class CompKey : public Component {
public:
    float pickupDist = 10;
    float minDist = 30;
    float findDoorDist = 100;
    bool linkedToPlayer = false;
    CompKey() {

    }
    void update(float fElapsedTime) {
        for (int i = 0; i < parent->scene->eList.size(); i++) {
            if (parent->scene->eList.at(i)->type == "LockedDoor") {
                Vec2 tempDist = (parent->scene->eList.at(i)->pos + Vec2(0, 4) - parent->pos);
                if (abs(tempDist.x) < parent->size.x / 2 + findDoorDist && abs(tempDist.y) < parent->size.y / 2 + findDoorDist) {
                    parent->vel = { 0,0 };
                    parent->vel = tempDist * 5;
                    break;
                }

            }
            if (parent->scene->eList.at(i)->type == "Player") {
                Vec2 tempDist = (parent->scene->eList.at(i)->pos - parent->pos);

                if (!linkedToPlayer && abs(tempDist.x) < parent->size.x / 2 + pickupDist && abs(tempDist.y) < parent->size.y / 2 + pickupDist) {
                    linkedToPlayer = true;
                }
                if (linkedToPlayer && !(abs(tempDist.x) < parent->size.x / 2 + minDist && abs(tempDist.y) < parent->size.y / 2 + minDist)) {
                    parent->vel = (parent->scene->eList.at(i)->pos - parent->pos) * 4;

                }
                else {
                    if (parent->vel.getMagnitude() > 800 * fElapsedTime) {
                        parent->vel -= parent->vel.normalize() * 800 * fElapsedTime;
                    }
                    else {
                        parent->vel = { 0,0 };
                    }

                }

            }
        }

    }
    void drawDebugging() {
        DrawRectangleLines(parent->pos.x - (parent->size.x + pickupDist * 2) / 2, parent->pos.y - (parent->size.y + pickupDist * 2) / 2, (parent->size.x + pickupDist * 2), (parent->size.y + pickupDist * 2), { 255,255,255,100 });
        DrawRectangleLines(parent->pos.x - (parent->size.x + minDist * 2) / 2, parent->pos.y - (parent->size.y + minDist * 2) / 2, (parent->size.x + minDist * 2), (parent->size.y + minDist * 2), { 255,255,255,100 });
        DrawRectangleLines(parent->pos.x - (parent->size.x + findDoorDist * 2) / 2, parent->pos.y - (parent->size.y + findDoorDist * 2) / 2, (parent->size.x + findDoorDist * 2), (parent->size.y + findDoorDist * 2), { 255,255,255,100 });
    }
};
class CompPlayer : public Component {
public:

    CompGroundCol* myGCol;
    CompHealth* myHealth;
    CompParticleThrust* thrustAnimation;
    CompTreatEntityAsGround* myEGround;
    Vec2 input = Vec2(0, 0);




    bool facingLeft = false;
    //Ground
    float groundSpeed = 1400;
    float groundFriction = 900;
    float groundDrag = .015;



    //Air
    float airSpeed = 700;
    float airFrictionX = 300;
    float airDragX = .01;

    float airFrictionYUp = 300;
    float airFrictionYDown = 100;

    float airDragYUpSpace = 0.006;
    float airDragYUpNoSpace = 0.04;
    float airDragYDown = 0.005;

    float gravityDown = 900;
    float gravityUp = 900;
    float gravityJump = 200;


    //Jump
    float jumpForgiveTime = .07;
    float coyoteTimer = 0;
    float jumpBuffer = 0;

    float jumpPower = 300;
    bool onWallLeft = false;
    float leftCTimer = 0;
    float rightCTimer = 0;
    bool onWallRight = false;
    bool wasLeftRight = false;

    Vec2 gameCam = { 0,0 };


    float attackCoolDown = .2;
    float attackCDTimer = 0;
    float attackActive = .1;
    float attackActiveTimer = 0;
    float attackBuffer = .1;
    float attackBufferTimer = 0;
    bool hitEnemy = false;



    float respawnTimer = 0;
    float respawnTime = 1.5;
    CompPlayer() {
        compoName = "CompPlayer";
    }
    void start() {
        myGCol = dynamic_cast<CompGroundCol*>(parent->getComponent("CompGroundCol"));
        myHealth = dynamic_cast<CompHealth*>(parent->getComponent("CompHealth"));
        thrustAnimation = dynamic_cast<CompParticleThrust*>(parent->getComponent("CompParticleThrust"));
        myEGround = dynamic_cast<CompTreatEntityAsGround*>(parent->getComponent("CompTreatEntityAsGround"));

    }
    void controller() {
        input = { 0,0 };

        if (IsKeyDown(KEYBIND_RIGHT)) {
            input.x++;
            if (!IsKeyDown(KEYBIND_LEFT)) {
                facingLeft = false;
            }

        }

        if (IsKeyDown(KEYBIND_LEFT)) {
            input.x--;
            if (!IsKeyDown(KEYBIND_RIGHT)) {
                facingLeft = true;
            }
        }
        if (IsKeyDown(KEYBIND_UP)) {
            input.y--;
        }
        if (IsKeyDown(KEYBIND_DOWN)) {
            input.y++;
        }
        jumpBuffer -= fElapsedTime;
        if (IsKeyPressed(KEYBIND_JUMP)) {
            if (IsKeyDown(KEYBIND_DOWN)) {
                bool stupid = false;
                for (int i = 0; i < myGCol->curTileCol.size(); i++) {

                    if (!myGCol->curTileCol.at(i)->myProperties.platPassThru) {
                        stupid = true;
                        break;
                    }
                }
                if (stupid) {
                    jumpBuffer = jumpForgiveTime;
                }
            }
            else {
                jumpBuffer = jumpForgiveTime;
            }

        }
        coyoteTimer -= fElapsedTime;
        if (myGCol->resDir.y == -1 || myEGround->resDir.y == -1) {


            coyoteTimer = jumpForgiveTime;
        }


        Rectangle h1;
        Rectangle h2;
        attackBufferTimer -= fElapsedTime;
        attackCDTimer -= fElapsedTime;
        attackActiveTimer -= fElapsedTime;
        if (IsKeyDown(KEYBIND_ACTION1)) {
            attackBufferTimer = attackBuffer;

        }
        if (attackBufferTimer > 0 && attackCDTimer < 0) {

            attackActiveTimer = attackActive;
            hitEnemy = false;

            float bulSpeed = 400;
            Entity* temp = new Entity(parent->pos, { 10,10 }, PBULLET, { new CompParicleBulTemp(),new CompBasicEntityCol({ENEMY}),new CompHurtOnContact({ENEMY},1,true), new CompRemoveTimer(.25), new CompGroundCol(),new CompRemoveOnGroundHit(), new CompSpriteFaceVel("SmallShot.png",{0,0},true,true,WHITE)}, "NOSAVE", true);

            if (input.y == 1) {
                temp->vel.y = 350;
            }
            else if (input.y == -1) {
                temp->vel.y = -350;
            }
            else if (facingLeft) {
                temp->vel.x = -350;
            }
            else {
                temp->vel.x = 350;
            }

            parent->scene->addEntity(temp);
            if (!hitEnemy) {
            }

            if (attackActiveTimer > 0) {
                attackCDTimer = attackCoolDown;
                if (input.y == -1) {

                    h1 = { parent->pos.x - 8, parent->pos.y - 40, 16, 40 };
                }
                else if (input.y == 1) {

                    h1 = { parent->pos.x - 8, parent->pos.y, 16, 40 };
                }
                else if (input == Vec2(1, 0)) {

                    h1 = { parent->pos.x, parent->pos.y - 8, 40, 16 };
                }
                else if (input == Vec2(-1, 0)) {

                    h1 = { parent->pos.x - 40, parent->pos.y - 8, 40, 16 };
                }
                else if (facingLeft) {

                    h1 = { parent->pos.x - 40, parent->pos.y - 8, 40, 16 };

                }
                else {

                    h1 = { parent->pos.x, parent->pos.y - 8, 40, 16 };
                }
                //DrawRectangle(h1.x,h1.y,h1.width,h1.height, RED);


                    /*
                    for (int i = 0; i < parent->scene->eList.size(); i++) {
                        if (parent->scene->eList.at(i) == parent || parent->scene->eList.at(i)->myLayer != ENEMY) {
                            continue;
                        }
                        if (RectRectCollision(h1, { parent->scene->eList.at(i)->pos.x - parent->scene->eList.at(i)->size.x / 2,parent->scene->eList.at(i)->pos.y - parent->scene->eList.at(i)->size.y / 2 , parent->scene->eList.at(i)->size.x, parent->scene->eList.at(i)->size.y })) {
                            hitEnemy = true;
                            CompHealth* yourHealth;
                            if (dynamic_cast<CompHealth*>(parent->scene->eList.at(i)->getComponent("CompHealth"))) {
                                yourHealth = dynamic_cast<CompHealth*>(parent->scene->eList.at(i)->getComponent("CompHealth"));
                                yourHealth->takeDamage(1);
                            }
                        }
                    }
                    */
            }
        }


    }

    void movement() {
        float curSpeed;
        float curFricX;
        float curDragX;

        float curFricY = 0;
        float curDragY = 0;
        if (myGCol->resDir.y == -1 || myEGround->resDir.y == -1) {
            curSpeed = groundSpeed;
            curFricX = groundFriction;
            curDragX = groundDrag;
        }
        else {
            curSpeed = airSpeed;
            curFricX = airFrictionX;
            curDragX = airDragX;

            if (parent->vel.y > 0) {
                curFricY = airFrictionYDown;
            }
            else {
                curFricY = airFrictionYUp;
            }
            if (parent->vel.y > 0) {
                curDragY = airDragYDown;
            }
            else {
                if (IsKeyDown(KEYBIND_JUMP)) {
                    curDragY = airDragYUpSpace;
                }
                else {
                    curDragY = airDragYUpNoSpace;
                }

            }

        }
        if (myGCol->resDir.x != 0&&parent->vel.y>0) {
            curDragY = airDragYDown * 20;
            
        }
        parent->vel.x += input.x * curSpeed * fElapsedTime;
        parent->vel.x -= curDragX * parent->vel.x * abs(parent->vel.x) * fElapsedTime;
        if (curFricX * fElapsedTime > abs(parent->vel.x)) {
            parent->vel.x = 0;

        }
        else {
            parent->vel.x -= curFricX * fElapsedTime * sgn(parent->vel.x);
        }

        parent->vel.y -= curDragY * parent->vel.y * abs(parent->vel.y) * fElapsedTime;
        if (curFricY * fElapsedTime > abs(parent->vel.y)) {
            parent->vel.y = 0;

        }
        else {
            parent->vel.y -= curFricY * fElapsedTime * sgn(parent->vel.y);
        }




        

        if (jumpBuffer > 0 && coyoteTimer > 0) {
            jumpBuffer = 0;
            coyoteTimer = 0;
            if (parent->vel.y > 0) {
                parent->vel.y = 0;
            }
            parent->vel.y -= jumpPower;
        }
        Rectangle rightWallCol = { parent->pos.x+3,parent->pos.y-5,5,12 };

        rightCTimer -= fElapsedTime;
        if (RectTileCollision(rightWallCol, *parent->scene, TILE_RULE_solid)) {
            onWallRight = true;
            rightCTimer = jumpForgiveTime;
        }
        else {
            onWallRight = false;
        }

        Rectangle leftWallCol = { parent->pos.x-8,parent->pos.y-5,5,12 };
        leftCTimer -= fElapsedTime;
        if (RectTileCollision(leftWallCol, *parent->scene, TILE_RULE_solid)) {
            onWallLeft = true;
            leftCTimer = jumpForgiveTime;
        }
        else {
            onWallLeft = false;
        }

        if (jumpBuffer > 0 && (leftCTimer>0||rightCTimer>0)&&coyoteTimer<=0) {
            jumpBuffer = 0;
            coyoteTimer = 0;
            if (parent->vel.y > 0) {
                parent->vel.y = 0;
            }
            parent->vel.y -= jumpPower*.9;
            if (leftCTimer>0) {
                parent->vel.x = 150;
                leftCTimer = 0;
            }
            else {
                parent->vel.x = -150;
                rightCTimer = 0;
            }
            
        }
        
        if (wasLeftRight && !((RectTileCollision({ parent->pos.x - 9,parent->pos.y - 5,16,12 }, *parent->scene, TILE_RULE_solid)))) {
            if (parent->vel.y > 0) {
                parent->vel.y = 0;
            }
        }
        wasLeftRight = (RectTileCollision({ parent->pos.x - 9,parent->pos.y - 5,16,12 }, *parent->scene, TILE_RULE_solid));



        //gravity
        if (IsKeyDown(KEYBIND_JUMP) && parent->vel.y < 0) {

            parent->vel.y += gravityJump * fElapsedTime;
        }
        else if (parent->vel.y < 0) {
            parent->vel.y += gravityUp * fElapsedTime;
        }
        else {
            parent->vel.y += gravityDown * fElapsedTime;
        }
        
    }

    void attackManager() {

    }
    void onDeath() {
        respawnTimer += GetFrameTime();
        freezeTime = true;
        myHealth->iFrameTimer = 0;
        if (respawnTimer > respawnTime) {
            freezeTime = false;
            respawnTimer = respawnTime;
            //parent->scene->inLevel->LoadLevel();
            loadLevel(*parent->scene->inLevel, currentSaveFile);
            
        }
        parent->vel = { 0,0 };
    }
    virtual void drawDebugging() {
        if (facingLeft) {
            DrawLine(parent->pos.x, parent->pos.y + 2, parent->pos.x - parent->size.x / 2 + 1, parent->pos.y + 2, WHITE);
        }
        else {
            DrawLine(parent->pos.x, parent->pos.y + 2, parent->pos.x + parent->size.x / 2, parent->pos.y + 2, WHITE);
        }
        if (myHealth->health <= 0) {
            DrawCircle(parent->pos.x, parent->pos.y, (respawnTimer * respawnTimer * 1500), RED);
        }
    }
    virtual void draw() {
        
    }

    virtual void update(float fElapsedTime) {


        playerPos = parent->pos;
        playerVel = parent->vel;
        for (int i = 0; i < myGCol->curTileCol.size(); i++) {
            if (myGCol->curTileCol.at(i)->myProperties.isSpike) {
                if ((myGCol->resDir.x == 1) && myGCol->curTileCol.at(i)->myProperties.solidRight) {
                    myHealth->takeDamage(214);
                    

                }
                if ((myGCol->resDir.x == -1) && myGCol->curTileCol.at(i)->myProperties.solidLeft) {
                    myHealth->takeDamage(214);

                   
                }
                if ((myGCol->resDir.y == 1) && myGCol->curTileCol.at(i)->myProperties.solidBottom) {
                    myHealth->takeDamage(214);


                   
                }
                if ((myGCol->resDir.y == -1) && myGCol->curTileCol.at(i)->myProperties.solidTop) {
                    myHealth->takeDamage(214);


                    
                }

            }
        }
        controller();
        movement();
        

        


        if (parent->pos.y > (parent->scene->tileSet.size()+parent->scene->pos.y + 5) * tileSize) {
            myHealth->health = 0;
        }

        if (myHealth->health <= 0) {
            onDeath();
        }
    }
};
class CompHealthBar : public Component {
public:
    CompHealth* myHealth;
    Vec2 pos;
    Vec2 size;
    bool drawNum = true;
    CompHealthBar(Vec2 mpos, Vec2 msize) {
        pos = mpos;
        size = msize;
    }
    void start() {
        myHealth = dynamic_cast<CompHealth*>(parent->getComponent("CompHealth"));
    }
    void drawUI() {
        int offSet = 25; 
        DrawRectangle(pos.x, pos.y+size.y, offSet, size.y, {100,0,0,255});
        DrawText(TextFormat("Health:"), pos.x+1, pos.y+1, size.y, BLACK);
        DrawText(TextFormat("Health:"), pos.x, pos.y, size.y, WHITE);
        DrawText(TextFormat("%i", myHealth->health), pos.x+13, pos.y + 1 + size.y, size.y, BLACK);
        DrawText(TextFormat("%i", myHealth->health), pos.x+12, pos.y + 0 + size.y, size.y, WHITE);
        DrawRectangle(pos.x +     offSet, pos.y + size.y, size.x, size.y, WHITE);
        DrawRectangle(pos.x + 1 + offSet, pos.y + 1 + size.y, size.x - 2, size.y - 2, BLACK);

        DrawRectangle(pos.x + 1 + offSet, pos.y + 1 + size.y, (size.x - 2) * myHealth->health / myHealth->maxHP, size.y - 2, { 150,0,0,255 });
        DrawRectangle(pos.x + 1 + offSet, pos.y + 1 + size.y, (size.x - 2) * myHealth->health / myHealth->maxHP, size.y - 6, RED);
    }
};
class CompBossHealthBar : public Component {
public:
    CompHealth* myHealth;
    Vec2 pos;
    Vec2 size;
    bool drawNum = true;
    CompBossHealthBar() {

        pos = { virtualScreenWidth / 2 - 100,virtualScreenHeight - 40 };
        size ={ 200,25 };
    }
    void start() {
        myHealth = dynamic_cast<CompHealth*>(parent->getComponent("CompHealth"));
    }
    void drawUI() {
        if (!parent->isOnScreen) {
            return;
        }
       
        
        
        
        DrawRectangle(pos.x, pos.y , size.x, size.y, WHITE);
        DrawRectangle(pos.x + 1, pos.y + 1 , size.x - 2, size.y - 2, BLACK);

        DrawRectangle(pos.x + 1, pos.y + 1 , (size.x - 2) * myHealth->health / myHealth->maxHP, size.y - 2, { 150,0,0,255 });
        DrawRectangle(pos.x + 1, pos.y + 1 , (size.x - 2) * myHealth->health / myHealth->maxHP, size.y - 6, RED);
        
        //DrawText(TextFormat("BossHealth"), pos.x + 11, pos.y + 4, 20, BLACK);
        //DrawText(TextFormat("BossHealth"), pos.x +10, pos.y + 3, 20, WHITE);
    }
};
class CompMinion : public Component {
public:
    Entity* summonedBy;
    float hoverTime = 1;
    float oSet;
    bool oneOff = true;
    CompMinion(Entity* parent, float offSet) {
        summonedBy = parent;
        oSet = offSet;
    }
    void update(float fElapsedTime) {
        hoverTime -= fElapsedTime;
        
        if (hoverTime > 0) {
            parent->pos = summonedBy->pos + Vec2(cos(hoverTime*PI + oSet), sin(hoverTime*PI + oSet)) *(1-hoverTime)* 20;
        }
        if (hoverTime < 0 && oneOff) {
            oneOff = false;
            parent->vel = Vec2(sin(hoverTime*PI + oSet), -cos(hoverTime*PI + oSet)) * 50;
        }
        if (oneOff == false&&parent->vel.getMagnitude()<10) {
            parent->removeMe = true;
        }
    }
};
class CompMinionSpawner : public Component {
public:
    float waitTime = 3;
    CompMinionSpawner() {

    }
    void update(float fElapsedTime) {
        waitTime -= fElapsedTime;
        if (waitTime < 0) {
            waitTime = 6;
            parent->scene->addEntity(new Entity(parent->pos, { 8,8 }, ENEMY, { new CompPhysic(0,0,0,0,1,true,true),new CompHealth(2),new CompMinion(parent,+(rand() % 360) / 180.0f * PI), new CompGroundCol(),new CompBasicEntityCol({PLAYER}), new CompHurtOnContact({PLAYER}),new CompSprite("SadFace.png",{0,0},GREEN) }));
            parent->scene->addEntity(new Entity(parent->pos, { 8,8 }, ENEMY, { new CompPhysic(0,0,0,0,1,true,true),new CompHealth(2),new CompMinion(parent,+(rand() % 360) / 180.0f * PI), new CompGroundCol(),new CompBasicEntityCol({PLAYER}), new CompHurtOnContact({PLAYER}),new CompSprite("SadFace.png",{0,0},GREEN) }));
            parent->scene->addEntity(new Entity(parent->pos, { 8,8 }, ENEMY, { new CompPhysic(0,0,0,0,1,true,true),new CompHealth(2),new CompMinion(parent,+(rand() % 360) / 180.0f * PI), new CompGroundCol(),new CompBasicEntityCol({PLAYER}), new CompHurtOnContact({PLAYER}),new CompSprite("SadFace.png",{0,0},GREEN) }));

        }
    }
};
class CompAccel : public Component {
public:
    float a;
    CompAccel(float acc) {
        a = acc;
    }
    void update(float fElapsedTime) {
        parent->vel += parent->vel.normalize() * a*fElapsedTime;
    }
};
class CompWin :public Component {
public:
    CompWin() {

    }
    void update(float fElapsedTime) {
        if ((playerPos - parent->pos).getMagnitude() < 10) {
            win = true;
        }
    }
};
class CompWBug : public Component {
public:
    Vec2 arenaCenter;
    Texture2D* mySprite;

    Color myTint = WHITE;;
    bool isSad;
    float maxSize = 1;
    float sizeMult = 0;
    
    Vec2 lookDir = {1,0};

    float timer = 2;
    float timer2 = 0;
    float timer3 = 0;
    float timer4 = 0;
    float timer5 = 0;
    float timer6 = 0;
    float spawnTimer = 0;
    float timeForSpawn = 1;
    int phase = 0;
    int side = 0;
    int beamSide = 1;
    Vec2 targetPoint = {0,0};
    bool reached = false;
    int dashNum = 0;
    int modeType = 0;
    Vec2 beamEnd = { 0,0 };
    CompParticleImplode* myParticle;
    CompHealth* myHealth;
    CompWBug(Vec2 arenaC) {
        arenaCenter = arenaC;
        

    }

    virtual void start() {

        
            mySprite = &entityTextures.at(15);
            myParticle = dynamic_cast<CompParticleImplode*>(parent->getComponent("CompParticleImplode"));
            myHealth = dynamic_cast<CompHealth*>(parent->getComponent("CompHealth"));
            
    }
    virtual void update(float fElapsedTime) {
        timer += fElapsedTime;
        if (phase == 0) {
            spawnTimer += fElapsedTime;
            
            lookDir = { cos(timer*2*PI),sin(timer*2*PI) };
            myParticle->offSet = sizeMult * 5 + 10;
            sizeMult = spawnTimer / timeForSpawn * maxSize;
            if (spawnTimer > timeForSpawn) {
                phase++;
                timer = 100;
                
            }
        }
        else {
            myParticle->powering = false;
            sizeMult = maxSize;
        }
        if (phase == 1) {
            if (timer > 12) {
                timer = 0;
                targetPoint = playerPos+ Vec2(cos(rand() % 360 / 2 * PI), sin(rand() % 360 / 2 * PI))*50;
                reached = false;
            }
            if (timer < 6) {
                targetPoint = playerPos;


                parent->vel -= parent->vel * .6 * fElapsedTime;
                parent->vel -= parent->vel.normalize() * 30 * fElapsedTime;
                parent->vel += (targetPoint - parent->pos).normalize() * 150 * fElapsedTime;

                lookDir = (parent->vel);
                timer2 = 0;
            }
            else {
                targetPoint = playerPos + Vec2(130 * sgn(parent->pos.x - playerPos.x), 0);

                parent->vel -= parent->vel * .8 * fElapsedTime;
                parent->vel -= parent->vel.normalize() * 180 * fElapsedTime;
                parent->vel += (targetPoint - parent->pos).normalize() * 400 * fElapsedTime;
                
              

                lookDir = Vec2(-sgn(parent->pos.x - playerPos.x), 0);
                
                timer2 += fElapsedTime;
                if (timer2 > 1) {
                    timer2 = 0;
                    Entity* temp = new Entity(parent->pos, {4,4}, BULLET, { new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(5), new CompSprite("Pellet.png",{0,0}) }, "NOSAVE", true);
                    temp->vel = Vec2(sgn(playerPos.x - parent->pos.x)*80,0);
                    parent->scene->addEntity(temp);
                    temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(5), new CompSprite("Pellet.png",{0,0}) }, "NOSAVE", true);
                    temp->vel = Vec2(sgn(playerPos.x - parent->pos.x) * 160, 0);
                    parent->scene->addEntity(temp);
                    temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(5), new CompSprite("Pellet.png",{0,0}) }, "NOSAVE", true);
                    temp->vel = Vec2(sgn(playerPos.x - parent->pos.x) * 240, 0);
                    parent->scene->addEntity(temp);
                }
            }
            if (myHealth->health < myHealth->maxHP - 17) {
                phase++;
                
                timer = 0;
                
            }
        }
        if (phase == 2) {
            parent->vel -=parent->vel*5*fElapsedTime;
            if (timer > .5) {
                for (int i = 0; i < 20; i++) {
                    Entity* temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompAccel(100),new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(5), new CompSprite("Pellet.png",{0,0}) }, "NOSAVE", true);
                    temp->vel = Vec2(cos((i+.5) * PI / 10), sin((i+.5) * PI / 10)) * 10;
                    parent->scene->addEntity(temp);
                }
                phase++;
                timer = 0;
            }
            
        }
        if (phase == 3) {
            if (timer > .5) {
                for (int i = 0; i < 20; i++) {
Entity* temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompAccel(100),new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(5), new CompSprite("Pellet.png",{0,0}) }, "NOSAVE", true);
temp->vel = Vec2(cos((i)*PI / 10), sin((i)*PI / 10)) * 10;
parent->scene->addEntity(temp);
                }
                phase++;
                timer = 0;
            }

        }
        if (phase == 4) {
            if (timer > .5) {
                for (int i = 0; i < 20; i++) {
                    Entity* temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompAccel(100),new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(5), new CompSprite("Pellet.png",{0,0}) }, "NOSAVE", true);
                    temp->vel = Vec2(cos((i + .5) * PI / 10), sin((i + .5) * PI / 10)) * 10;
                    parent->scene->addEntity(temp);
                }
                phase++;
                timer = 0;
            }

        }
        if (phase == 5) {
            if (modeType == 0) {
                targetPoint = playerPos + Vec2(150 * sgn(parent->pos.x - playerPos.x), -100);

                if (timer < 3) {
                    parent->vel -= parent->vel * .7 * fElapsedTime;
                    parent->vel -= parent->vel.normalize() * 140 * fElapsedTime;
                    parent->vel += (targetPoint - parent->pos).normalize() * 400 * fElapsedTime;


                }
                else if (timer < 10) {
                    timer3 += fElapsedTime;

                    timer2 += fElapsedTime;

                    if (timer2 > .7 && dashNum < 5) {
                        myParticle->start();
                        if (dashNum == 0) {
                            side = -sgn(parent->pos.x - playerPos.x);
                            parent->vel = Vec2((rand() % 5 / 2.0f + .75f) * side, 4).normalize() * 300;

                        }
                        else if (dashNum == 4) {

                        }
                        else {

                            parent->vel = Vec2(parent->vel.x, parent->vel.y * -1);
                        }
                        timer3 = 0;
                        Entity* temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(7), new CompSprite("Pellet.png",{0,0},WHITE,1) }, "NOSAVE", true);
                        temp->vel = { 0,0 };
                        parent->scene->addEntity(temp);
                        for (int i = 0; i < 8; i++) {
                            Entity* temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompAccel(20),new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(5), new CompSprite("Pellet.png",{0,0}) }, "NOSAVE", true);
                            temp->vel = Vec2(cos((i)*PI / 4), sin((i)*PI / 4)) * 10;
                            parent->scene->addEntity(temp);
                        }
                        timer3 = 0;
                        
                        timer2 = 0;
                        dashNum++;
                    }

                    myParticle->powering = dashNum == 0;

                    if (timer3 > .13 && dashNum != 0) {

                        Entity* temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompAccel(100),new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(7), new CompSprite("Pellet.png",{0,0},WHITE,1) }, "NOSAVE", true);
                        temp->vel = { 0,0 };
                        parent->scene->addEntity(temp);
                        timer3 = 0;
                    }
                    if (dashNum >= 5) {
                        dashNum = 0;
                        timer = 0;
                        timer2 = 0;
                        timer3 = 0;
                        modeType = 1;
                        reached = false;
                    }


                }
            }
            else if (modeType == 1) {
                if (!reached) {
                    parent->vel = ((playerPos + playerVel * fElapsedTime) - parent->pos).normalize() * 100;
                    reached = true;
                }

                if (timer > 2) {
                    timer = 0;
                    timer2 = 0;
                    timer3 = 0;
                    modeType = 2;
                }
            }
            else if(modeType == 2){
                targetPoint = playerPos;


                parent->vel -= parent->vel * .8 * fElapsedTime;
                parent->vel -= parent->vel.normalize() * 30 * fElapsedTime;
                parent->vel += (targetPoint - parent->pos).normalize() * 300 * fElapsedTime;

                lookDir = (parent->vel);
                
                if (timer > 10) {
                    timer = 0;
                    timer2 = 0;
                    timer3 = 0;
                    modeType = 0;
                }
            }           
            if (myHealth->health < myHealth->maxHP - 40) {
                phase++;
           }
        }
        if (phase == 6) {
           

            if (timer2 > 3) {
                targetPoint = playerPos + Vec2(0, -100);
                parent->vel -= parent->vel * 3 * fElapsedTime;
                parent->vel -= parent->vel.normalize() * 300 * fElapsedTime;
                parent->vel += (targetPoint - parent->pos).normalize() * 900 * fElapsedTime;
            }
            else {
                targetPoint = playerPos;
                parent->vel -= parent->vel * .5 * fElapsedTime;
                parent->vel -= parent->vel.normalize() * 30 * fElapsedTime;
                parent->vel += (targetPoint - parent->pos).normalize() * 150 * fElapsedTime;
            }
            

            lookDir = (parent->vel);
            timer2 += fElapsedTime;
            timer3 += fElapsedTime;
            
            if (timer2 > 6) {

                if (timer3 > .3) {
                    

                    dashNum++;
                    Entity* temp = new Entity(parent->pos, { 8,8 }, BULLET, { new CompGravity(240), new CompAccel(20), new CompRoll(2),new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER},1,true), new CompRemoveTimer(20), new CompGroundCol(),new CompSprite("Pellet.png",{0,0}, WHITE)}, "NOSAVE", true);
                    temp->vel = Vec2(rand()%5-2,-rand() % 11-30  );
                    
                    
                    
                    parent->scene->addEntity(temp);
                    
                    
                    if (dashNum >20) {
                        for (int i = 0; i < 20; i++) {
                            Entity* temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompAccel(100),new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(5), new CompSprite("Pellet.png",{0,0}) }, "NOSAVE", true);
                            temp->vel = Vec2(cos((i + .5) * PI / 10), sin((i + .5) * PI / 10)) * 10;
                            parent->scene->addEntity(temp);
                        }
                        parent->vel.y = 0;
                        parent->vel.y -= 90;

                        dashNum = 0;
                        timer2 = 0;
                    }
                    timer3 = 0;
                }
                
            }
            if (myHealth->health == 1) {
                myHealth->iFrameTimer = 40;
                phase++;
            }
        }
        if (phase == 7) {
            targetPoint = arenaCenter;
            parent->vel -= parent->vel * .6 * fElapsedTime;
            parent->vel -= parent->vel.normalize() * 10 * fElapsedTime;
            parent->vel += (targetPoint - parent->pos)*5 * fElapsedTime;
           
            if ((targetPoint - parent->pos).getMagnitude()<5) {
                phase++;
                timer = 0;
                timer2 = 0;
                timer3 = 0;
                timer4 = 0;
                timer5 = 0;
                timer6 = 0;
                parent->vel = { 0,0 };
                lookDir = { 0,1 };
                side = 1;
                myHealth->iFrameTimer = 40;
            }
        }
        if (phase == 8) {
            timer3 += fElapsedTime;
            timer2 += fElapsedTime;
            timer4 += fElapsedTime;
            timer5 += fElapsedTime;
            timer6 += fElapsedTime;
            DrawCircleLines(parent->pos.x, parent->pos.y, 300, WHITE);
            if ((timer4 > .3&& timer > 25)|| (timer4 > .5 && timer > 10)|| (timer4 > .7)) {
                float ang = Vec2(0,1).getAngle() + (rand() % 100 / 100.0f - .5) * PI;
                Entity* temp = new Entity(parent->pos+ Vec2(cos(ang), sin(ang))*300, { 8,8 }, BULLET, { new CompAccel(50), new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(3.5), new CompSprite("Pellet.png",{0,0},WHITE,2) }, "NOSAVE", true);
                
                temp->vel = Vec2(cos(ang), sin(ang)) * -1;
                parent->scene->addEntity(temp);

                temp = new Entity(parent->pos + Vec2(0, 185) , { 8,8 }, BULLET, { new CompRoll(2), new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(8), new CompGroundCol(), new CompSprite("Pellet.png",{0,0},WHITE,2)}, "NOSAVE", true);

                temp->vel = Vec2(100, 0);
                parent->scene->addEntity(temp);
                timer4 = 0;
            }
            if (timer3 > 2) {
                timer3 = 0;
                side *= -1;
            }
            if (((timer2 > .15&&timer>25)||(timer2 > .4 && timer > 10) || (timer2 > .6)) && timer3>1.5) {
                Entity* temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(7), new CompSprite("Pellet.png",{0,0},WHITE,1) }, "NOSAVE", true);
                temp->vel = Vec2(cos(timer * side *2),sin(timer * side *2))*100;
                parent->scene->addEntity(temp);

                temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(7), new CompSprite("Pellet.png",{0,0},WHITE,1) }, "NOSAVE", true);
                temp->vel = Vec2(cos(timer * side * 2+PI/2), sin(timer*side * 2 + PI / 2)) * 100;
                parent->scene->addEntity(temp);

                temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(7), new CompSprite("Pellet.png",{0,0},WHITE,1) }, "NOSAVE", true);
                temp->vel = Vec2(cos(timer * side * 2 + PI), sin(timer * side * 2 + PI)) * 100;
                parent->scene->addEntity(temp);

                temp = new Entity(parent->pos, { 4,4 }, BULLET, { new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompRemoveTimer(7), new CompSprite("Pellet.png",{0,0},WHITE,1) }, "NOSAVE", true);
                temp->vel = Vec2(cos(timer * side * 2 + PI*3/2), sin(timer * side * 2 + PI*3/2)) * 100;
                parent->scene->addEntity(temp);
                timer2 = 0;
            }
            if (timer > 10) {
                if (timer6 > 10) {
                    timer6 = 0;
                    timer5 = 0;
                }
                if (timer6 >4) {
                    myParticle->powering = false;
                    
                    if (beamSide == 1) {
                        lookDir = lookDir.rotate(fElapsedTime/4.0f);
                    }
                    else{
                        lookDir = lookDir.rotate(-fElapsedTime/4.0f);
                    }
                    
                    Ray2D beam(parent->pos, lookDir);
                    RayHit beamHit = beam.intersect(*parent->scene, 300);

                    Vec2 U = playerPos - parent->pos;
                    Vec2 U1 = U.project(lookDir);
                    Vec2 U2 = U - U1;
                    float d = U2.getMagnitude();
                    if (d < 7) {
                        for (int i = 0; i < parent->scene->eList.size(); i++) {
                            if (parent->scene->eList.at(i)->type == "Player") {
                                CompHealth* yourHealth = dynamic_cast<CompHealth*>(parent->scene->eList.at(i)->getComponent("CompHealth"));
                                yourHealth->takeDamage(1);
                            }
                        }
                    }
                    
                    beamEnd = beamHit.hitPos;
                }
                else {
                    myParticle->powering = true;
                    lookDir = Vec2(sgn(playerPos.x - parent->pos.x),  -.1).normalize();
                    beamSide = sgn(playerPos.x - parent->pos.x);
                }
            }
            else {
                
                lookDir = (playerPos - parent->pos).normalize();
            }
        }
        
    }
    virtual void draw() {
        if (timer6 > 4&& timer > 10) {
            DrawCircle(beamEnd.x, beamEnd.y,5, RED);
            DrawLineEx(parent->pos.rayVec2(), (beamEnd).rayVec2(), 6, RED);
            DrawCircle(beamEnd.x, beamEnd.y, 3, WHITE);
            DrawLineEx(parent->pos.rayVec2(), (beamEnd).rayVec2(), 4, WHITE);
        }
            

            int frameWidth = mySprite->width;
            int frameHeight = mySprite->height;
            Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
            Rectangle destRec = { parent->pos.x, parent->pos.y, frameWidth * sizeMult, frameHeight * sizeMult };
            DrawTexturePro(*mySprite, sourceRec, destRec, { (float)(frameWidth * sizeMult / 2),(float)(frameHeight * sizeMult / 2) }, (lookDir.getAngle())/PI*180+90, myTint);

            
    }
    void drawDebugging() {
        
            DrawCircle(targetPoint.x, targetPoint.y, 5, ORANGE);
        
    }
    virtual void drawUI() {
        Vec2 pos = { virtualScreenWidth / 2 - 100,virtualScreenHeight - 20 };
        Vec2 size = { 200,25 };
        DrawRectangle(pos.x, pos.y, size.x, size.y, WHITE);
        DrawRectangle(pos.x + 1, pos.y + 1, size.x - 2, size.y - 2, BLACK);

        DrawRectangle(pos.x + 1, pos.y + 1, (size.x - 2) * myHealth->health / myHealth->maxHP, size.y - 2, { 150,0,0,255 });
        DrawRectangle(pos.x + 1, pos.y + 1, (size.x - 2) * myHealth->health / myHealth->maxHP, size.y - 6, RED);
        if (phase == 8) {
            DrawRectangle(pos.x + 1, pos.y + 1, (size.x - 2) * (40 - timer)/40, size.y - 2, { 0,0,150,255 });
            DrawRectangle(pos.x + 1, pos.y + 1, (size.x - 2) * (40 - timer)/40, size.y - 6, BLUE);
        }
    }
};
class CompWBugShrine : public Component {
public:
    bool used = false;
    CompWBugShrine() {

    }
    void update(float fElapsedTime) {
        if (!used) {
            if (IsKeyPressed(KEYBIND_DOWN) && (playerPos - parent->pos).getMagnitude() < 20) {
                Entity* temp = new Entity(parent->pos + Vec2(0, -70), { 26,26 }, ENEMY, { new CompWBug(parent->pos+Vec2(0,-190)),new CompHealth(100), new CompParticleImplode(), new CompCircleEntityCol({PLAYER}), new CompHurtOnContact({PLAYER}) }, "WBug");
                temp->updateOffScreen = true;
                parent->scene->addEntity(temp);
                used = true;
            }
        }
        
    }
    void drawDebugging() {
        DrawCircle(parent->pos.x,parent->pos.y-150,4,PURPLE);
    }
    void draw() {
        if (!used) {
            DrawRectangle(parent->pos.x - parent->size.x / 2, parent->pos.y - parent->size.y / 2, parent->size.x, parent->size.y, PURPLE);
            DrawText("Press down", parent->pos.x - 20, parent->pos.y - 20, 1, WHITE);
            
        }
        
    }
};



class CompPlayerSprite : public CompSprite {
public:
    CompPlayer* playerCom;
    Vec2 tempOffSet = {0,0};
    Vec2 tempVel = {0,0};
    CompPlayerSprite(Vec2 offSeT) : CompSprite("Player.png", offSeT) {

        compoName = "CompPlayerSprite";

    }
    void start() {
        CompSprite::start();

        playerCom = dynamic_cast<CompPlayer*>(parent->getComponent("CompPlayer"));
    }
    void draw() {
        if (playerCom->myHealth->health > 0) {
            if (playerCom->myHealth->iFrameTimer > 0) {
                if (playerCom->facingLeft) {

                    DrawTextureRec(*mySprite, { 0,0,-15,20 }, { (parent->pos.x - parent->size.x / 2 + offSet.x), (parent->pos.y - parent->size.y / 2 + offSet.y) }, { 255,150,150,130 });
                }
                else {

                    DrawTexture(*mySprite, (parent->pos.x - parent->size.x / 2 + offSet.x), (parent->pos.y - parent->size.y / 2 + offSet.y), { 255,150,150,130 });
                }
            }
            else {
                if (playerCom->facingLeft) {

                    DrawTextureRec(*mySprite, { 0,0,-15,20 }, { (parent->pos.x - parent->size.x / 2 + offSet.x), (parent->pos.y - parent->size.y / 2 + offSet.y) }, WHITE);
                }
                else {

                    DrawTexture(*mySprite, (parent->pos.x - parent->size.x / 2 + offSet.x), (parent->pos.y - parent->size.y / 2 + offSet.y), WHITE);
                }
            }
            tempVel = Vec2(0, -50);
        }
        else {
            int frameWidth = mySprite->width;
            int frameHeight = mySprite->height;
            Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
            Rectangle destRec = { parent->pos.x + offSet.x+tempOffSet.x, parent->pos.y + offSet.y+tempOffSet.y, frameWidth * sizeMult, frameHeight * sizeMult };
            DrawTexturePro(*mySprite, sourceRec, destRec, { (float)(frameWidth * sizeMult / 2),(float)(frameHeight * sizeMult / 2) }, -90, myTint);
            tempOffSet += tempVel * GetFrameTime();
            tempVel += Vec2(0, 320) * GetFrameTime();
            
        }
        


    }
    void drawUI() {
        DrawRectangle(0, 0, virtualScreenWidth, virtualScreenHeight, {0,0,0,(unsigned char)(255*((playerCom->respawnTimer / playerCom->respawnTime)* (playerCom->respawnTimer / playerCom->respawnTime))) });

    }
};

Entity* createTestEntity(Vec2 pos) {

    return new Entity(pos, { 31,31 }, ENEMY, { new CompSpreadGun(2,100,3,1,PI / 4), new CompDrawTurret(), new CompBasicEntityCol({PLAYER}), new CompHurtOnContact({PLAYER},1),new CompHealth(3),new CompGravity(10), new CompGroundCol() }, "UtroW");
}
Entity* createEasyShooter(Vec2 pos) {
    return new Entity(pos, { 31,31 }, ENEMY, { new CompBasicGun(2,100,0,0,1), new CompDrawTurret(), new CompBasicEntityCol({PLAYER}), new CompHurtOnContact({PLAYER},1),new CompHealth(3),new CompGravity(10), new CompGroundCol(), new CompSpriteFacePlayer("StupidCat.png",{0,0},true,false,WHITE) }, "EasyShoot");
}
Entity* createTripleShooter(Vec2 pos) {
    return new Entity(pos, { 31,31 }, ENEMY, { new CompBasicGun(3,100,0,.5,3), new CompDrawTurret(), new CompBasicEntityCol({PLAYER}), new CompHurtOnContact({PLAYER},1),new CompHealth(3),new CompGravity(10), new CompGroundCol(), new CompSpriteFacePlayer("StupidCat.png",{0,0},true,false,BLUE) }, "TriShoot");
}
Entity* createRocketShooter(Vec2 pos) {
    return new Entity(pos, { 31,31 }, ENEMY, { new CompBasicGun(3,150,2,0,1), new CompDrawTurret(), new CompBasicEntityCol({PLAYER}), new CompHurtOnContact({PLAYER},1),new CompHealth(3),new CompGravity(10), new CompGroundCol(), new CompSpriteFacePlayer("StupidCat.png",{0,0},true,false,RED) }, "RocketShoot");

}

Entity* createZagEntity(Vec2 pos) {

    return new Entity(pos, { 11,11 }, ENEMY, { new CompZigZagAI(),new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER},1),new CompHealth(3), new CompGroundCol(), new CompSprite("SadFace.png",{0,0}) }, "Zag", true);
}
Entity* createBatEntity(Vec2 pos) {

    return new Entity(pos, { 9,9 }, ENEMY, { new CompBatAI(75),new CompHealth(3),new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER},1), new CompGroundCol(), new CompSpriteFaceVel("Bat.png",{0,0},true,false) }, "Bat");

}
Entity* createShootingBat(Vec2 pos) {
    return new Entity(pos, { 12,12 }, ENEMY, { new CompBatAI(95), new CompBasicGun(5,70),new CompHealth(3),new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER},1), new CompGroundCol(), new CompSprite("OrangeSpike.png",{0,0}) }, "ShootingBat");
}
Entity* createPlayer(Vec2 pos) {

    return new Entity(pos, { 13, 18 }, PLAYER, { new CompSquareHitBox(-3,-6,6,12),new CompHealth(3,.5, false), new CompPlayer(),new CompGroundCol(),new CompBasicEntityCol({GROUND}), new CompTreatEntityAsGround({GROUND}), new CompPlayerSprite({-1,-1}),new CompHealthBar(Vec2(20,20),Vec2(70,10)) }, "Player", true);
}
Entity* createCameraHolder(Vec2 pos) {
    return new Entity(pos, { 2,2 }, BASIC, { new CompCamera(virtualScreenWidth,virtualScreenHeight, natrualZoom, freezeTime, worldSpaceCamera) }, "Camera", true);
}
Entity* createSaveBox(Vec2 pos) {
    return new Entity(pos, { (float)tileSize,(float)tileSize }, INTERACT, { new CompSave(), new CompSprite("SpiralNotebook.png",{0,0}) }, "SaveStation");
}
Entity* createWalker(Vec2 pos) {
    return new Entity(pos, { 24,24 }, ENEMY, { new CompWalkAI(300,10),new CompGravity(9.8), new CompGroundCol(), new CompHurtOnContact({PLAYER},1),new CompHealth(3),new CompBasicEntityCol({PLAYER}), new CompSpriteFaceVel("Snail.png",{0,0},true,false) }, "Walker");
}
Entity* createSmallWalker(Vec2 pos) {
    return new Entity(pos, { 12,12 }, ENEMY, { new CompWalkAI(400,10),new CompGravity(9.8), new CompGroundCol(), new CompHurtOnContact({PLAYER},1),new CompHealth(2),new CompBasicEntityCol({PLAYER}),new CompSpriteFaceVel("AngerDog.png",{0,0},true,false) }, "WalkerSmall");

}
Entity* createEye(Vec2 pos) {
    return new Entity(pos, { 12,12 }, ENEMY, { new CompEyeAI(70), new CompPhysic(.3,.4,0,0,1,true,true), new CompGroundCol(), new CompHurtOnContact({PLAYER},1),new CompHealth(4),new CompBasicEntityCol({PLAYER}),new CompSprite("FunnyFace.png",{0,0}) }, "Crow");

}
Entity* createFrog(Vec2 pos) {
    return new Entity(pos, { 14,14 }, ENEMY, { new CompPhysic(0,0,5,1,.2,true,false),new CompDashAI(2,150,true,false,{1,-3}), new CompGravity(200), new CompGroundCol(), new CompHurtOnContact({PLAYER},1),new CompHealth(4),new CompBasicEntityCol({PLAYER}), new CompSpriteFaceVel("Frog.png",{0,0},true,false) }, "Frog");

}
Entity* createFrogStatue(Vec2 pos) {
    return new Entity(pos, { 31,31 }, ENEMY, { new CompBasicGun(3,150,1,1,3,0,{1,-1.5},true,false, true), new CompDrawTurret(), new CompBasicEntityCol({PLAYER}), new CompHurtOnContact({PLAYER},1),new CompHealth(3),new CompGravity(10), new CompGroundCol() }, "FrogStatue");

}
Entity* createLockedDoor(Vec2 pos) {
    return new Entity(pos, { 32,32 }, GROUND, { new CompLockedDoor(), new CompSpriteFacePlayer("BigLock.png",{0,0},true,false) }, "LockedDoor");

}
Entity* createKey(Vec2 pos) {
    return new Entity(pos, { 4,4 }, INTERACT, { new CompKey(), new CompSpriteFaceVel("Key.png",{0,0},true, false) }, "Key");
}
Entity* createWBugShrine(Vec2 pos) {
    return new Entity(pos, { 16,16 }, INTERACT, { new CompWBugShrine()}, "Shrine");
}
class CompDropKeyOnDeath :public Component {
public:
    CompDropKeyOnDeath() {

    }
    void onRemove() {
        parent->scene->addEntity(createKey(parent->pos));
    }
};
Entity* createMiniBoss(Vec2 pos) {
    return new Entity(pos, { 32,24 }, ENEMY, { new CompBossHealthBar(), new CompDropKeyOnDeath(),new CompSpreadGun(7,40,5,0,PI / 6,1.5,2), new CompPhysic(.5,0,1,.2,1,true,true), new CompMinionSpawner(),new CompHealth(50),new CompGravity(180), new CompDashAI(5,200,true,false,{1,-3}),new CompGroundCol(),new CompBasicEntityCol({PLAYER}),new CompHurtOnContact({PLAYER}), new CompSpriteFaceVel("Frog.png",{0,-4},true, false,YELLOW,2) }, "MiniBoss");
}

Entity* TXTtoEntity(ifstream& inStream) {
    
    string next;
    int line = 1;
    int eNum = 0;
    Vec2 pos(0, 0);
    string name;
    bool compCycle = false;
    bool upOffScreen = false;
    while (getline(inStream, next)) {
        


        if (line == 1) {

            name = next;



        }
        if (line == 2) {


            pos.x = stringToInt(next);

        }
        if (line == 3) {


            pos.y = stringToInt(next);



        }
        if (line == 4) {
            upOffScreen = stringToInt(next);

        }
        if (next == "###END OF ENTITY###") {

            if (name == "Zag") {
                Entity* tempEnt;
                tempEnt = createZagEntity(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return tempEnt;
            }
            else if (name == "Player") {
               
                Entity* tempEnt;
                tempEnt = createPlayer(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "UtroW") {
                Entity* tempEnt;
                tempEnt = createTestEntity(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "Camera") {
                Entity* tempEnt;
                tempEnt = createCameraHolder(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "Bat") {
                Entity* tempEnt;
                tempEnt = createBatEntity(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "ShootingBat") {
                Entity* tempEnt;
                tempEnt = createShootingBat(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "SaveStation") {
                Entity* tempEnt;
                tempEnt = createSaveBox(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "Walker") {
                Entity* tempEnt;
                tempEnt = createWalker(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "WalkerSmall") {
                Entity* tempEnt;
                tempEnt = createSmallWalker(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "Crow") {
                Entity* tempEnt;
                tempEnt = createEye(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "Frog") {
                Entity* tempEnt;
                tempEnt = createFrog(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "FrogStatue") {
                Entity* tempEnt;
                tempEnt = createFrogStatue(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "EasyShoot") {
                Entity* tempEnt;
                tempEnt = createEasyShooter(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "LockedDoor") {
                Entity* tempEnt;
                tempEnt = createLockedDoor(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "Key") {
                Entity* tempEnt;
                tempEnt = createKey(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "TriShoot") {
                Entity* tempEnt;
                tempEnt = createTripleShooter(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "RocketShoot") {
                Entity* tempEnt;
                tempEnt = createRocketShooter(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "MiniBoss") {
                Entity* tempEnt;
                tempEnt = createMiniBoss(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
            else if (name == "Shrine") {
                Entity* tempEnt;
                tempEnt = createWBugShrine(pos);
                tempEnt->updateOffScreen = upOffScreen;
                return (tempEnt);
            }
        }
        line++;
        if (next.size() > 0) {
            if (next.at(0) == '#') {
                line = 1;
                eNum++;


                continue;

            }
        }
    }
}
void saveRoom(Room& mLevel, string RoomName) {
    
    ofstream outStream;
    outStream.open(RoomName);
    outStream << mLevel.roomName << endl;
    outStream << "origin"<<endl;
    outStream << (int)mLevel.pos.x << endl;
    outStream << (int)mLevel.pos.y << endl;
    outStream << "Ground" << endl;
    for (int i = 0; i < mLevel.tileSet.size(); i++) {
        for (int j = 0; j < mLevel.tileSet.at(i).size(); j++) {
            outStream << mLevel.tileSet.at(i).at(j)->tileType;
        }
        outStream << endl;
    }
    outStream << "BACKGROUND:" << endl;
    for (int i = 0; i < mLevel.background.size(); i++) {
        for (int j = 0; j < mLevel.background.at(i).size(); j++) {
            outStream << mLevel.background.at(i).at(j)->tileType;
        }
        outStream << endl;
    }
    
    outStream << "ENTITIES:" << endl;
    for (int i = 0; i < mLevel.eList.size(); i++) {
        if (mLevel.eList.at(i)->type != "NOSAVE"&& mLevel.eList.at(i)->type != "Player"&& mLevel.eList.at(i)->type != "Camera") {
            outStream << "#" << i << endl;
            mLevel.eList.at(i)->saveToTXT(outStream);

        }

    }

    outStream.close();
}
void loadRoom(Room& mLevel, string RoomName) {
    

    ifstream inStream;
    inStream.open(RoomName);
    
    mLevel.eList.clear();
    mLevel.tileSet.clear();
    mLevel.background.clear();
    int j = 0;
    string next;
    getline(inStream, next);
    mLevel.roomName = next;
    getline(inStream, next);

    if (next == "origin") {
        int x1;
        int y1;
        
        getline(inStream, next);
        x1 = stringToInt(next);
        
        getline(inStream, next);
        y1 = stringToInt(next);
        
        mLevel.pos = Vec2(x1, y1);
    }
    getline(inStream, next);
    
    while (getline(inStream, next)) {
        
        if (next == "BACKGROUND:") {
            break;
        }
        mLevel.tileSet.push_back({});
        for (int i = 0; i < next.size(); i++) {
            mLevel.tileSet.at(j).push_back(charToTile(next.at(i)));
        }
        j++;

    }
    
    mLevel.width = mLevel.tileSet.at(0).size();
    
    mLevel.height = mLevel.tileSet.size();
    j = 0;
    while (getline(inStream, next)) {
        if (next == "ENTITIES:") {
            break;
        }
        mLevel.background.push_back({});
        for (int i = 0; i < next.size(); i++) {
            mLevel.background.at(j).push_back(charToTile(next.at(i)));
        }
        j++;

    }
    int line = 0;
    int eNum = 0;
    Vec2 pos(0, 0);
    string name;
    bool compCycle = false;
    bool upOffScreen = false;

    while (getline(inStream, next)) {



        if (line == 1) {

            name = next;



        }
        if (line == 2) {


            pos.x = stringToInt(next);

        }
        if (line == 3) {


            pos.y = stringToInt(next);



        }
        if (line == 4) {
            upOffScreen = stringToInt(next);

        }
        if (next == "###END OF ENTITY###") {

            if (name == "Zag") {
                Entity* tempEnt;
                tempEnt = createZagEntity(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "Player") {

                Entity* tempEnt;
                tempEnt = createPlayer(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "UtroW") {
                Entity* tempEnt;
                tempEnt = createTestEntity(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "Camera") {
                Entity* tempEnt;
                tempEnt = createCameraHolder(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "Bat") {
                Entity* tempEnt;
                tempEnt = createBatEntity(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "ShootingBat") {
                Entity* tempEnt;
                tempEnt = createShootingBat(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "SaveStation") {
                Entity* tempEnt;
                tempEnt = createSaveBox(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "Walker") {
                Entity* tempEnt;
                tempEnt = createWalker(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "WalkerSmall") {
                Entity* tempEnt;
                tempEnt = createSmallWalker(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "Crow") {
                Entity* tempEnt;
                tempEnt = createEye(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "Frog") {
                Entity* tempEnt;
                tempEnt = createFrog(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "FrogStatue") {
                Entity* tempEnt;
                tempEnt = createFrogStatue(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "EasyShoot") {
                Entity* tempEnt;
                tempEnt = createEasyShooter(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "LockedDoor") {
                Entity* tempEnt;
                tempEnt = createLockedDoor(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "Key") {
                Entity* tempEnt;
                tempEnt = createKey(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "TriShoot") {
                Entity* tempEnt;
                tempEnt = createTripleShooter(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "RocketShoot") {
                Entity* tempEnt;
                tempEnt = createRocketShooter(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "MiniBoss") {
                Entity* tempEnt;
                tempEnt = createMiniBoss(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
            else if (name == "Shrine") {
                Entity* tempEnt;
                tempEnt = createWBugShrine(pos);
                tempEnt->updateOffScreen = upOffScreen;
                mLevel.addEntity(tempEnt);
            }
        }
        line++;
        if (next.size() > 0) {
            if (next.at(0) == '#') {
                line = 1;
                eNum++;


                continue;

            }
        }
    }
    inStream.close();
}
void loadRoom(Room& mLevel, vector<string> tileMap) {
    mLevel.tileSet.clear();
    for (int i = 0; i < tileMap.size(); i++) {
        mLevel.tileSet.push_back({});

        for (int j = 0; j < tileMap.at(i).size(); j++) {
            mLevel.tileSet.at(i).push_back(charToTile(tileMap.at(i).at(j)));
        }
    }
}
void saveLevelAs(Level& mLevel, string name) {
    if (name == "NOSAVE") {
        playerSaveTemp = mLevel.player->pos;
        cout << "done" << endl;
        return;
    }
    ofstream outStream;
    outStream.open(name);
    outStream << "Room Names:" << endl;
    for (int i = 0; i < mLevel.rooms.size(); i++) {
        outStream << name + "-" + to_string(i) << endl;
    }
    outStream << "Global Entities:"<<endl;
    mLevel.player->spawnPos = mLevel.player->pos;
    mLevel.player->saveToTXT(outStream);
    mLevel.camera->spawnPos = mLevel.camera->pos;
    mLevel.camera->saveToTXT(outStream);
    mLevel.globalEntities.push_back(mLevel.player);
    mLevel.globalEntities.push_back(mLevel.camera);
    outStream.close();
    for (int i = 0; i < mLevel.rooms.size(); i++) {
        saveRoom(*(mLevel.rooms.at(i)), name+"-"+to_string(i));

    }
    
}
void loadLevel(Level& mLevel, string name) {
    if (name == "NOSAVE") {
        loadLevel(mLevel, "LevelOneBeta");
        if (!(playerSaveTemp == Vec2(0, 0))) {
            mLevel.player->pos = playerSaveTemp;
            mLevel.camera->pos = playerSaveTemp;
            for (int i = 0; i < mLevel.rooms.size(); i++) {
                if (RectRectCollision({ mLevel.player->pos.x / tileSize,mLevel.player->pos.y / tileSize,0,0 }, { mLevel.rooms.at(i)->pos.x, mLevel.rooms.at(i)->pos.y,  (float)mLevel.rooms.at(i)->width, (float)mLevel.rooms.at(i)->height })) {
                    mLevel.currentRoom = mLevel.rooms.at(i);
                    break;
                }
            }
            mLevel.currentRoom->addEntity(mLevel.player);
            mLevel.currentRoom->addEntity(mLevel.camera);
            mLevel.player->scene = mLevel.currentRoom;
            mLevel.camera->scene = mLevel.currentRoom;
            mLevel.lastSaveRoom = mLevel.currentRoom;
        }
        mLevel.levelName = "NOSAVE";
        return;
    }
    mLevel.rooms.clear();
    mLevel.globalEntities.clear();
    ifstream inStream;
    inStream.open(name);
    string next;
    getline(inStream, next);

    while (getline(inStream, next)) {
        if (next == "Global Entities:") {
            break;
        }
        mLevel.rooms.push_back(new Room(next));
        
    }
    
    mLevel.currentRoom = mLevel.rooms.at(0);
    
    mLevel.player = TXTtoEntity(inStream);
    mLevel.camera = TXTtoEntity(inStream);
    mLevel.camera->pos = mLevel.player->pos;
    mLevel.globalEntities.push_back(mLevel.player);
    mLevel.globalEntities.push_back(mLevel.camera);
    inStream.close();
    for (int i = 0; i < mLevel.rooms.size(); i++) {
        loadRoom(*mLevel.rooms.at(i), mLevel.rooms.at(i)->roomName);
        mLevel.rooms.at(i)->inLevel = &mLevel;
    }
    for (int i = 0; i < mLevel.rooms.size(); i++) {
        if (RectRectCollision({ mLevel.player->pos.x / tileSize,mLevel.player->pos.y / tileSize,0,0 }, { mLevel.rooms.at(i)->pos.x, mLevel.rooms.at(i)->pos.y,  (float)mLevel.rooms.at(i)->width, (float)mLevel.rooms.at(i)->height })) {
            mLevel.currentRoom = mLevel.rooms.at(i);
            break;
        }
    }
    int j = 0;
    

    mLevel.currentRoom->addEntity(mLevel.player);
    mLevel.currentRoom->addEntity(mLevel.camera);
    mLevel.player->scene = mLevel.currentRoom;
    mLevel.camera->scene = mLevel.currentRoom;

    mLevel.lastSaveRoom = mLevel.currentRoom;
}








bool RectTileCollision(Rectangle rec, Room grid, TileProperties collCheck, bool Debugging, Color color1, Color color2) {
    rec.x -= grid.pos.x*tileSize;
    rec.y -= grid.pos.y*tileSize;
    float leftX = rec.x;
    float rightX = rec.x + rec.width;

    float topY = rec.y;
    float bottomY = rec.y + rec.height;
    Rectangle temp = { rec.x+grid.pos.x*tileSize ,rec.y + grid.pos.y*tileSize ,rec.width ,rec.height};
    if (Debugging) {
        DrawRectangleLinesEx(temp, 3, color1);
    }
    for (int i = topY / tileSize; i < bottomY / tileSize; i++) {
        for (int j = leftX / tileSize; j < rightX / tileSize; j++) {

            if (i > -1 && i<grid.tileSet.size() && j >-1 && j < grid.tileSet.at(0).size()) {

                
                
                if (grid.tileSet.at(i).at(j)->myProperties == collCheck) {
                
                    
                    if (RectRectCollision(rec, { (float)j*tileSize,(float)i*tileSize,(float)tileSize,(float)tileSize })) {
                        
                        if (Debugging) {
                            DrawRectangleLinesEx(temp, 3, color2);
                        }

                        return true;
                    }


                }

            }

        }
    }
    
    return false;
}





class LevelEditor {
public:

    int page = 0;

    float scrollSpeed = 200;
    Room* currentRoom;
    Level* currentLevel;
    Vec2 cameraPosition;

    Vec2 mouseWorldPos = { 0,0 };
    Vec2 mouseTilePos = { 0,0 };
    Vec2 mouseRoomTilePos = { 0,0 };

    int curIndex = 0;
    int specialIndex = -1;
    vector<button> tileSel;
    vector<button> specialSel;
    button save;
    button swapMode;
    button xUp;
    button xDown;
    button yUp;
    button yDown;


    vector<Entity*> eSave;

    bool tileMode = true;

    int tileSizeMult = 6;

    float UIXpos = 70;

    Vec2 cursorSize = { 1,1 };

    Vec2 areaTL = { 0,0 };
    Vec2 areaBR = { 0,0 };
    vector<vector<Tile*>> copied;
    bool pasting = false;
    bool drawDebug = false;
    bool editBackground = false;
    LevelEditor() {
        currentRoom = new Room();
        cameraPosition = { 0,0 };

        int x = 0;
        int y = 0;
        for (int i = 0; i < 20; i++) {
            y = i % 10;

            tileSel.push_back(button({ screenWidth - 285.0f + x * tileSize * 1.5f, y * tileSize * 1.5f + 95.0f }, tileSize + 10, tileSize + 10, WHITE, GREEN));
            if (y == 9) {
                x++;
            }
        }
    }
    LevelEditor(Level* levelIn, Room* RoomIn) {
        currentLevel = levelIn;
        currentRoom = RoomIn;
        cameraPosition = { 0,0 };
        int x = 0;
        int y = 0;
        for (int i = 0; i < 20; i++) {
            y = i % 10;

            tileSel.push_back(button({ 0,0 }, tileSize * tileSizeMult + 30, tileSize * tileSizeMult + 30, WHITE, GREEN, 5, 5));
            if (y == 9) {
                x++;
            }
        }
        specialSel.push_back(button({ 0,0 }, tileSize * tileSizeMult + 30, tileSize * tileSizeMult + 30, WHITE, GREEN, 5, 5));
        save = button({ 0,0 }, 500, 100, WHITE, GREEN, 10, 10);
        swapMode = button({ 0,0 }, 500, 100, WHITE, GREEN, 10, 10);
        xUp = button();
        xDown = button();
        yUp = button();
        yDown = button();

        xUp.unHigh = { 200,200,200,255 };
        yUp.unHigh = { 200,200,200,255 };
        xDown.unHigh = { 100,100,100,255 };
        yDown.unHigh = { 100,100,100,255 };
    }

    void copyArea(Vec2 TL, Vec2 BR) {
        copied.clear();



        int copi = -1;
        for (int i = TL.y; i < BR.y; i++) {
            copied.push_back({});
            copi++;
            for (int j = TL.x; j < BR.x; j++) {
                copied.at(copi).push_back(currentRoom->tileSet.at(i).at(j));
            }
        }
    }
    void paste(Vec2 pos) {
        for (int i = 0; i < copied.size(); i++) {
            for (int j = 0; j < copied.at(i).size(); j++) {
                if (i + pos.y < currentRoom->tileSet.size() && j + pos.x < currentRoom->tileSet.at(0).size() && i + pos.y >= 0 && j + pos.x >= 0) {
                    currentRoom->tileSet.at(i + pos.y).at(j + pos.x) = copied.at(i).at(j);
                }
            }
        }
    }

    void controller() {

        //shmovement
        if (IsKeyDown(KEY_LEFT_CONTROL)) {
            if (IsKeyPressed(KEY_UP)) {
                currentRoom->pos.y--;
                for (int i = 0; i < currentRoom->eList.size(); i++) {
                    currentRoom->eList.at(i)->pos.y -= tileSize;
                    currentRoom->eList.at(i)->spawnPos.y -= tileSize;
                }
            }
            if (IsKeyPressed(KEY_LEFT)) {
                currentRoom->pos.x--;
                for (int i = 0; i < currentRoom->eList.size(); i++) {
                    currentRoom->eList.at(i)->pos.x -= tileSize;
                    currentRoom->eList.at(i)->spawnPos.x -= tileSize;
                }
            }
            if (IsKeyPressed(KEY_DOWN)) {
                currentRoom->pos.y++;
                for (int i = 0; i < currentRoom->eList.size(); i++) {
                    currentRoom->eList.at(i)->pos.y += tileSize;
                    currentRoom->eList.at(i)->spawnPos.y += tileSize;
                }
            }
            if (IsKeyPressed(KEY_RIGHT)) {
                currentRoom->pos.x++;
                for (int i = 0; i < currentRoom->eList.size(); i++) {
                    currentRoom->eList.at(i)->pos.x += tileSize;
                    currentRoom->eList.at(i)->spawnPos.x += tileSize;
                }
            }
            return;
        }
        if (IsKeyPressed(KEY_G)) {
            drawDebug = !drawDebug;
        }
        if (IsKeyPressed(KEY_RIGHT)) {
            page++;
        }
        if (IsKeyPressed(KEY_LEFT) && page > 0) {
            page--;
        }
        if (IsKeyPressed(KEY_ONE)) {
            scrollSpeed -= 30;
        }
        else if (IsKeyPressed(KEY_TWO)) {
            scrollSpeed += 30;
        }
        if (IsKeyDown(KEY_W)) {
            cameraPosition.y -= fElapsedTime * scrollSpeed;
        }
        if (IsKeyDown(KEY_A)) {
            cameraPosition.x -= fElapsedTime * scrollSpeed;
        }
        if (IsKeyDown(KEY_S)) {
            cameraPosition.y += fElapsedTime * scrollSpeed;
        }
        if (IsKeyDown(KEY_D)) {
            cameraPosition.x += fElapsedTime * scrollSpeed;
        }
        if (IsKeyDown(KEY_O)) {
            worldSpaceCamera.zoom -= fElapsedTime;
        }
        if (IsKeyDown(KEY_P)) {
            worldSpaceCamera.zoom += fElapsedTime;
        }
        if (IsKeyDown(KEY_I)) {
            worldSpaceCamera.zoom = natrualZoom;
        }
        if (IsKeyPressed(KEY_B)) {
            editBackground = !editBackground;
        }

        //end 
        // 
        //mousePositioning
        mouseWorldPos = Vec2(GetScreenToWorld2D(virtualMouse.rayVec2(), worldSpaceCamera));
        mouseTilePos = (Vec2(mouseWorldPos.x, mouseWorldPos.y) / tileSize);
        mouseRoomTilePos = mouseTilePos - currentRoom->pos;
        if (mouseRoomTilePos.x <= 0) {
            mouseRoomTilePos.x--;
        }
        if (mouseRoomTilePos.y <= 0) {
            mouseRoomTilePos.y--;
        }
        mouseRoomTilePos = Vec2((int)mouseRoomTilePos.x, (int)mouseRoomTilePos.y);
        //end
        if (IsKeyDown(KEY_R) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            string aiya = "";
            
            Room* tempRoom = new Room(currentLevel->levelName + "-" + to_string(currentLevel->rooms.size()));
            tempRoom->pos = Vec2((int)mouseTilePos.x,(int)mouseTilePos.y);
            tempRoom->tileSet = { { charToTile(' '), charToTile(' '), charToTile(' ')} ,{ charToTile(' '), charToTile(' '), charToTile(' ')} ,{ charToTile(' '), charToTile(' '), charToTile(' ')} };
            tempRoom->height = 3;
            tempRoom->width = 3;
            currentLevel->addRoom(tempRoom);
            currentRoom == tempRoom;
            
        }
        if (IsKeyDown(KEY_R) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            for (int i = 0; i < currentLevel->rooms.size(); i++) {
                if (RectRectCollision({ mouseTilePos.x,mouseTilePos.y,0,0 }, { currentLevel->rooms.at(i)->pos.x,currentLevel->rooms.at(i)->pos.y,(float)currentLevel->rooms.at(i)->width,(float)currentLevel->rooms.at(i)->height })) {
                    currentLevel->rooms.erase(currentLevel->rooms.begin() + i);
                    i--;
                }
            }
            

        }
        //Editor
        while (currentRoom->background.size() < currentRoom->tileSet.size()) {
            currentRoom->background.push_back({});

        } 
        while (currentRoom->background.size() > currentRoom->tileSet.size()) {
            currentRoom->background.erase(currentRoom->background.begin() + currentRoom->tileSet.size() - 1);
        }
        for (int i = 0; i < currentRoom->background.size(); i++) {
            if (currentRoom->background.at(i).size() < currentRoom->tileSet.at(i).size()) {
                currentRoom->background.at(i).push_back(allTiles.at(0));
            }
            if (currentRoom->background.at(i).size() > currentRoom->tileSet.at(i).size()) {
                currentRoom->background.at(i).erase(currentRoom->background.at(i).begin() + currentRoom->tileSet.at(i).size() - 1);
                i--;
            }
        }
        //important
        if (GetMousePosition().x < destRec.x + destRec.width - (135 - UIXpos) * scale) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                for (int i = 0; i < currentLevel->rooms.size(); i++) {
                    if (RectRectCollision({ mouseTilePos.x, mouseTilePos.y, 0, 0 }, { currentLevel->rooms.at(i)->pos.x,currentLevel->rooms.at(i)->pos.y,(float)currentLevel->rooms.at(i)->width,(float)currentLevel->rooms.at(i)->height })) {
                        currentRoom = currentLevel->rooms.at(i);
                    }
                }
                
            }
            if (curIndex != -1) {

                if (tileMode && curIndex < allTiles.size()) {
                    
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                        
                        if (mouseRoomTilePos.x >= - 1 && mouseRoomTilePos.x <= + currentRoom->width && mouseRoomTilePos.y >= - 1 && mouseRoomTilePos.y <= currentRoom->height) {
                            if (mouseRoomTilePos.x == - 1) {
                                
                                for (int i = 0; i < currentRoom->tileSet.size(); i++) {
                                    currentRoom->tileSet.at(i).insert(currentRoom->tileSet.at(i).begin(), allTiles.at(0));
                                    currentRoom->background.at(i).insert(currentRoom->background.at(i).begin(), allTiles.at(0));
                                }
                                currentRoom->pos.x--;
                            }
                            else if (mouseRoomTilePos.x == currentRoom->width) {
                                currentRoom->tileSet.at(0).push_back(allTiles.at(0));
                                for (int i = 1; i < currentRoom->tileSet.size(); i++) {
                                    while (currentRoom->tileSet.at(i).size() < currentRoom->tileSet.at(0).size()) {
                                        currentRoom->tileSet.at(i).push_back(allTiles.at(0));
                                    }
                                }
                                //currentRoom->pos.x++;
                            }
                            else if (mouseRoomTilePos.y == - 1) {
                                

                                currentRoom->tileSet.insert(currentRoom->tileSet.begin(), { allTiles.at(0) });
                                currentRoom->background.insert(currentRoom->background.begin(), { allTiles.at(0) });
                                for (int i = 1; i < currentRoom->tileSet.at(1).size(); i++) {
                                    currentRoom->tileSet.at(0).push_back(allTiles.at(0));
                                    currentRoom->background.at(0).push_back(allTiles.at(0));
                                }
                                currentRoom->pos.y--;
                            }
                            else if (mouseRoomTilePos.y == currentRoom->height) {
                                currentRoom->tileSet.push_back({});
                                for (int i = 0; i < currentRoom->tileSet.at(0).size(); i++) {
                                    currentRoom->tileSet.at(currentRoom->tileSet.size() - 1).push_back(allTiles.at(0));
                                }
                            }
                        }
                        currentRoom->width = currentRoom->tileSet.at(0).size();
                        currentRoom->height = currentRoom->tileSet.size();

                

                        if (mouseRoomTilePos.x >= 0 && mouseRoomTilePos.y >= 0 && mouseRoomTilePos.y < currentRoom->tileSet.size() && mouseRoomTilePos.x < currentRoom->tileSet.at(0).size()) {
                            for (int i = 0; i < cursorSize.y; i++) {
                                for (int j = 0; j < cursorSize.x; j++) {
                                    if (mouseRoomTilePos.y - (int)(cursorSize.y / 2) + i > -1 && mouseRoomTilePos.y - (int)(cursorSize.y / 2) + i < currentRoom->tileSet.size()) {
                                        if (mouseRoomTilePos.x - (int)(cursorSize.x / 2) + j > -1 && mouseRoomTilePos.x - (int)(cursorSize.x / 2) + j < currentRoom->tileSet.at(0).size()) {
                                            if (editBackground) {
                                                currentRoom->background.at(mouseRoomTilePos.y - (int)(cursorSize.y / 2) + i).at(mouseRoomTilePos.x - (int)(cursorSize.x / 2) + j) = allTiles.at(curIndex);
                                            }
                                            else {
                                                currentRoom->tileSet.at(mouseRoomTilePos.y - (int)(cursorSize.y / 2) + i).at(mouseRoomTilePos.x - (int)(cursorSize.x / 2) + j) = allTiles.at(curIndex);
                                            }
                                            
                                        }
                                    }

                                }
                            }


                        }



                    }
                    else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                        if (mouseRoomTilePos.x >=  - 1 && mouseRoomTilePos.x <= currentRoom->width && mouseRoomTilePos.y >= - 1 && mouseRoomTilePos.y <= + currentRoom->height) {
                            if (currentRoom->tileSet.at(0).size() > 1) {
                                if (mouseRoomTilePos.x == - 1) {
                                    
                                    for (int i = 0; i < currentRoom->tileSet.size(); i++) {
                                        currentRoom->tileSet.at(i).erase(currentRoom->tileSet.at(i).begin());
                                        currentRoom->background.at(i).erase(currentRoom->background.at(i).begin());
                                    }
                                    currentRoom->pos.x++;
                                }
                                else if (mouseRoomTilePos.x == currentRoom->width) {
                                    currentRoom->tileSet.at(0).erase(currentRoom->tileSet.at(0).begin() + currentRoom->tileSet.at(0).size() - 1);//here
                                    for (int i = 1; i < currentRoom->tileSet.size(); i++) {
                                        while (currentRoom->tileSet.at(i).size() > currentRoom->tileSet.at(0).size()) {
                                            currentRoom->tileSet.at(i).erase(currentRoom->tileSet.at(i).begin() + currentRoom->tileSet.at(i).size() - 1);
                                            currentRoom->background.at(i).erase(currentRoom->background.at(i).begin() + currentRoom->background.at(i).size() - 1);
                                        }
                                    }
                                }
                            }

                            if (currentRoom->tileSet.size() > 1) {
                                if (mouseRoomTilePos.y == - 1) {
                                    
                                    currentRoom->tileSet.erase(currentRoom->tileSet.begin());
                                    currentRoom->background.erase(currentRoom->background.begin());
                                    currentRoom->pos.y++;
                                }
                                else if (mouseRoomTilePos.y ==  currentRoom->height) {
                                    currentRoom->tileSet.erase(currentRoom->tileSet.begin() + currentRoom->tileSet.size() - 1);
                                    currentRoom->background.erase(currentRoom->background.begin() + currentRoom->background.size() - 1);
                                }
                            }
                        }
                        currentRoom->width = currentRoom->tileSet.at(0).size();
                        currentRoom->height = currentRoom->tileSet.size();

                       


                    }
                }
                else if (!tileMode) {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                        for (int i = 0; i < currentRoom->eList.size(); i++) {
                            if ((mouseWorldPos - currentRoom->eList.at(i)->pos).getMagnitude() < 6) {
                                currentRoom->eList.at(i)->pos = mouseWorldPos;
                                currentRoom->eList.at(i)->spawnPos = mouseWorldPos;
                                break;
                            }
                        }
                        for (int i = 0; i < currentLevel->globalEntities.size(); i++) {
                            if ((mouseWorldPos - currentLevel->globalEntities.at(i)->pos).getMagnitude() < 6) {
                                currentLevel->globalEntities.at(i)->pos = mouseWorldPos;
                                currentLevel->globalEntities.at(i)->spawnPos = mouseWorldPos;
                                currentLevel->globalEntities.at(i)->scene = currentRoom;
                                break;
                            }
                        }
                        if (curIndex == 0) {
                            currentRoom->addEntity(createCameraHolder(mouseWorldPos));
                        }
                        if (curIndex == 1) {
                            currentRoom->addEntity(createTestEntity(mouseWorldPos));
                        }
                        if (curIndex == 2) {
                            currentRoom->addEntity(createZagEntity(mouseWorldPos));
                        }
                        if (curIndex == 3) {
                            currentRoom->addEntity(createBatEntity(mouseWorldPos));
                        }
                        if (curIndex == 4) {
                            currentRoom->addEntity(createSaveBox(mouseWorldPos));
                        }
                        if (curIndex == 5) {
                            currentRoom->addEntity(createEasyShooter(mouseWorldPos));
                        }
                        if (curIndex == 6) {
                            currentRoom->addEntity(createWalker(mouseWorldPos));
                        }
                        if (curIndex == 7) {
                            currentRoom->addEntity(createShootingBat(mouseWorldPos));
                        }
                        if (curIndex == 8) {
                            currentRoom->addEntity(createSmallWalker(mouseWorldPos));
                        }
                        if (curIndex == 9) {
                            currentRoom->addEntity(createEye(mouseWorldPos));
                        }
                        if (curIndex == 10) {
                            currentRoom->addEntity(createFrog(mouseWorldPos));
                        }
                        if (curIndex == 11) {
                            currentRoom->addEntity(createFrogStatue(mouseWorldPos));
                        }
                        if (curIndex == 12) {
                            currentRoom->addEntity(createLockedDoor(mouseWorldPos));
                        }
                        if (curIndex == 13) {
                            currentRoom->addEntity(createKey(mouseWorldPos));
                        }
                        if (curIndex == 14) {
                            currentRoom->addEntity(createTripleShooter(mouseWorldPos));
                        }
                        if (curIndex == 15) {
                            currentRoom->addEntity(createRocketShooter(mouseWorldPos));
                        }
                        if (curIndex == 16) {
                            currentRoom->addEntity(createMiniBoss(mouseWorldPos));
                        }
                        if (curIndex == 17) {
                            currentRoom->addEntity(createWBugShrine(mouseWorldPos));
                        }
                        curIndex = -2;
                    }
                    else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                        for (int i = 0; i < currentRoom->eList.size(); i++) {
                            if ((mouseWorldPos - currentRoom->eList.at(i)->pos).getMagnitude() < 5) {
                                currentRoom->eList.erase(currentRoom->eList.begin() + i);
                                i--;
                                break;
                            }
                        }

                    }
                    else if (IsKeyPressed(KEY_Q)) {
                        for (int i = 0; i < currentRoom->eList.size(); i++) {
                            if ((mouseWorldPos - currentRoom->eList.at(i)->pos).getMagnitude() < 6) {
                                currentRoom->eList.at(i)->updateOffScreen = !currentRoom->eList.at(i)->updateOffScreen;

                            }
                        }
                    }
                }


            }
            std::cout << mouseRoomTilePos.x << std::endl;
            if (specialIndex == 0) {
                if (!pasting) {


                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && areaTL == areaBR) {
                        areaTL = mouseRoomTilePos;
                        areaBR = mouseRoomTilePos + Vec2(1, 1);
                        
                    }
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                        if (abs(mouseWorldPos.x - areaTL.x * tileSize) < 3) {
                            areaTL.x--;
                        }
                        if (abs(mouseWorldPos.y - areaTL.y * tileSize) < 3) {
                            areaTL.y--;
                        }
                        if (abs(mouseWorldPos.x - areaBR.x * tileSize) < 3) {
                            areaBR.x++;
                        }
                        if (abs(mouseWorldPos.y - areaBR.y * tileSize) < 3) {
                            areaBR.y++;
                        }
                    }
                    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                        if (abs(mouseWorldPos.x - areaTL.x * tileSize) < 3 && areaTL.x < areaBR.x - 1) {
                            areaTL.x++;
                        }
                        if (abs(mouseWorldPos.y - areaTL.y * tileSize) < 3 && areaTL.y < areaBR.y - 1) {
                            areaTL.y++;
                        }
                        if (abs(mouseWorldPos.x - areaBR.x * tileSize) < 3 && areaTL.x < areaBR.x - 1) {
                            areaBR.x--;
                        }
                        if (abs(mouseWorldPos.y - areaBR.y * tileSize) < 3 && areaTL.y < areaBR.y - 1) {
                            areaBR.y--;
                        }
                    }
                    if (areaTL.y < 0) {
                        areaTL.y = 0;
                    }
                    if (areaTL.x < 0) {
                        areaTL.x = 0;
                    }
                    if (areaBR.y > currentRoom->tileSet.size()) {
                        areaBR.y = currentRoom->tileSet.size();
                    }
                    if (areaBR.x > currentRoom->tileSet.at(0).size()) {
                        areaBR.x = currentRoom->tileSet.at(0).size();
                    }
                    if (IsKeyPressed(KEY_C)) {
                        copyArea(areaTL, areaBR);
                    }
                    if (IsKeyPressed(KEY_V)) {
                        pasting = true;

                    }
                }
                else {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        pasting = false;
                        paste(mouseRoomTilePos);
                    }
                }

            }
            else {
                areaBR = { 0,0 };
                areaTL = { 0,0 };
            }

        }
    }
    void update(float fElapsedTime) {
        controller();
    }
    void draw() {
        
        DrawCircle(0, 0, 15, BLACK);
        DrawCircle(0, 0, 10, WHITE);
        /*int tempLeft = (worldSpaceCamera.target.x - virtualScreenWidth / 2) / tileSize - 1;
        int tempRight = (worldSpaceCamera.target.x + virtualScreenWidth / 2) / tileSize + 1;
        int tempTop = (worldSpaceCamera.target.y - virtualScreenHeight / 2) / tileSize - 1;
        int tempBottom = (worldSpaceCamera.target.y + virtualScreenHeight / 2) / tileSize + 1;*/

        int tempLeft = (worldSpaceCamera.target.x - virtualScreenWidth / 2 / worldSpaceCamera.zoom) / tileSize-1;
        int tempRight = ((worldSpaceCamera.target.x + virtualScreenWidth / 2/ worldSpaceCamera.zoom) / tileSize + 1) ;
        int tempTop = (worldSpaceCamera.target.y - virtualScreenHeight / 2/ worldSpaceCamera.zoom) / tileSize -1;
        int tempBottom = ((worldSpaceCamera.target.y + virtualScreenHeight / 2/ worldSpaceCamera.zoom) / tileSize + 1) ;
        DrawCircle(tempLeft * tileSize, tempTop * tileSize, 2, WHITE);
        DrawCircle(tempRight * tileSize, tempBottom * tileSize, 2, ORANGE);

        currentLevel->drawLevel(worldSpaceCamera, virtualScreenWidth, virtualScreenHeight);
        //currentRoom->drawLevel(drawDebug);
        for (int i = 0; i < currentLevel->rooms.size(); i++) {
            DrawRectangleLines(currentLevel->rooms.at(i)->pos.x * tileSize, currentLevel->rooms.at(i)->pos.y * tileSize, currentLevel->rooms.at(i)->width * tileSize, currentLevel->rooms.at(i)->height * tileSize, PURPLE);
        }
        DrawRectangleLines(currentRoom->pos.x*tileSize, currentRoom->pos.y*tileSize, currentRoom->width * tileSize, currentRoom->height * tileSize, YELLOW);
        if (pasting) {
            for (int i = 0; i < copied.size(); i++) {
                for (int j = 0; j < copied.at(i).size(); j++) {
                    copied.at(i).at(j)->draw((mouseRoomTilePos.x + j) * tileSize, (mouseRoomTilePos.y + i) * tileSize);
                }
            }
            if (copied.size() > 0) {
                DrawRectangle(mouseTilePos.x * tileSize, mouseTilePos.y * tileSize, copied.at(0).size() * tileSize, copied.size() * tileSize, { 100,100,100,50 });
            }

        }


        


        for (int i = 0; i < cursorSize.y; i++) {
            for (int j = 0; j < cursorSize.x; j++) {
                int shiftX = sgn(mouseTilePos.x);
                int shiftY = sgn(mouseTilePos.y);

                if (shiftX > 0) {
                    shiftX = 0;
                }
                if (shiftY > 0) {
                    shiftY = 0;
                }
                DrawRectangle(((int)mouseTilePos.x+shiftX - (int)(cursorSize.x / 2) + j) * tileSize, ((int)mouseTilePos.y + shiftY - (int)(cursorSize.y / 2) + i) * tileSize, tileSize, tileSize, { 100,200,100,100 });
            }
        }


        if (!tileMode) {
            for (int i = 0; i < currentRoom->eList.size(); i++) {
                DrawCircle(currentRoom->eList.at(i)->pos.x, currentRoom->eList.at(i)->pos.y, 2, WHITE);
                DrawCircleLines(currentRoom->eList.at(i)->pos.x, currentRoom->eList.at(i)->pos.y, 2, ORANGE);
            }
        }
        DrawCircle(areaTL.x * tileSize, areaTL.y * tileSize, 3, ORANGE);
        DrawCircle(areaBR.x * tileSize, areaBR.y * tileSize, 3, BLUE);
        DrawRectangleLinesEx({ areaTL.x * tileSize,areaTL.y * tileSize,(areaBR.x - areaTL.x) * tileSize,(areaBR.y - areaTL.y) * tileSize }, 2, WHITE);
        for (int i = 0; i < currentLevel->globalEntities.size(); i++) {
            currentLevel->globalEntities.at(i)->draw();
        }

    }
    void drawUI() {

        int tempLeft = (worldSpaceCamera.target.x - virtualScreenWidth / 2) / tileSize / worldSpaceCamera.zoom;
        int tempRight = ((worldSpaceCamera.target.x + virtualScreenWidth / 2) / tileSize + 1) / worldSpaceCamera.zoom;
        int tempTop = (worldSpaceCamera.target.y - virtualScreenHeight / 2) / tileSize / worldSpaceCamera.zoom;
        int tempBottom = ((worldSpaceCamera.target.y + virtualScreenHeight / 2) / tileSize + 1) / worldSpaceCamera.zoom;


        if (worldSpaceCamera.zoom >= 1) {
            int aiyax = (worldSpaceCamera.target.x - worldSpaceCamera.offset.x /worldSpaceCamera.zoom);
            int aiyay = (worldSpaceCamera.target.y - worldSpaceCamera.offset.y / worldSpaceCamera.zoom);

            aiyax %= tileSize;
            aiyay %= tileSize;
            for (int i = 0; i < sourceRec.width / tileSize / worldSpaceCamera.zoom; i++) {
                Vector2 start = { destRec.x + i * scale*worldSpaceCamera.zoom * tileSize - aiyax * scale * worldSpaceCamera.zoom,destRec.y };
                Vector2 end = { destRec.x + i * scale * worldSpaceCamera.zoom * tileSize - aiyax * scale * worldSpaceCamera.zoom,destRec.y + destRec.height };
                DrawLineEx(start, end, 5, { 100,100,100,100 });

            }
            for (int i = 0; i < -sourceRec.height / tileSize / worldSpaceCamera.zoom; i++) {
                Vector2 start = { destRec.x,                 destRec.y + i * scale * worldSpaceCamera.zoom * tileSize - aiyay * scale * worldSpaceCamera.zoom };
                Vector2 end = { destRec.x + destRec.width,destRec.y + i * scale*worldSpaceCamera.zoom * tileSize - aiyay * scale * worldSpaceCamera.zoom };
                DrawLineEx(start, end, 5, { 100,100,100,100 });
            }
        }

        

        DrawRectangle(destRec.x + destRec.width - (135 - UIXpos) * scale, destRec.y, destRec.y + 150 * scale, destRec.height, WHITE);
        DrawRectangle(destRec.x + destRec.width - (130 - UIXpos) * scale, destRec.y, destRec.y + 140 * scale, destRec.height, BLACK);
        if (tileMode) {
            if (editBackground) {
                DrawText("Tiles B", destRec.x + destRec.width - (125 - UIXpos) * scale, destRec.y + 5 * scale, 10 * scale, BLUE);
            }
            else {
                DrawText("Tiles R", destRec.x + destRec.width - (125 - UIXpos) * scale, destRec.y + 5 * scale, 10 * scale, WHITE);
            }
            
        }
        else {
            DrawText(TextFormat("Entities:%i", currentRoom->eList.size()), destRec.x + destRec.width - (125 - UIXpos) * scale, destRec.y + 5 * scale, 10 * scale, WHITE);
        }
        DrawText(TextFormat("Page:%i", page), destRec.x + destRec.width - (125 - UIXpos) * scale, destRec.y + 15 * scale, 10 * scale, WHITE);

        DrawCircle(GetMousePosition().x, GetMousePosition().y, 10, GREEN);

        int x = 0;
        int y = 0;
        for (int i = 0; i < 20; i++) {
            y = i % 10;

            tileSel.at(i).w = 16 * scale;
            tileSel.at(i).h = 16 * scale;
            Vec2 pos(destRec.x + destRec.width - (125 - UIXpos) * scale + x * (tileSel.at(i).w + 5), destRec.y + 27 * scale + y * (tileSel.at(i).h + 5));
            tileSel.at(i).pos = pos;

            if (y == 9) {
                x++;
            }


            if (tileMode) {
                if (i + page * 20 < allTiles.size()) {
                    allTiles.at(i + page * 20)->draw(pos.x + 5 * scale, pos.y + 5 * scale, scale );
                }
            }
            else {
                if (i + page * 20 == 6) {
                    DrawTextureEx(entityTextures.at(3), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .5, WHITE);
                }
                else if (i + page * 20 == 10) {
                    DrawTextureEx(entityTextures.at(6), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .9, WHITE);
                }
                else if (i + page * 20 == 3) {
                    DrawTextureEx(entityTextures.at(7), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .9, WHITE);
                }
                else if (i + page * 20 == 2) {
                    DrawTextureEx(entityTextures.at(2), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .9, WHITE);
                }
                else if (i + page * 20 == 9) {
                    DrawTextureEx(entityTextures.at(8), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .9, WHITE);
                }
                else if (i + page * 20 == 5) {
                    DrawTextureEx(entityTextures.at(9), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .5, WHITE);
                }
                else if (i + page * 20 == 8) {
                    DrawTextureEx(entityTextures.at(10), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .9, WHITE);
                }
                else if (i + page * 20 == 13) {
                    DrawTextureEx(entityTextures.at(11), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .9, WHITE);
                }
                else if (i + page * 20 == 12) {
                    DrawTextureEx(entityTextures.at(12), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .5, WHITE);
                }
                else if (i + page * 20 == 7) {
                    DrawTextureEx(entityTextures.at(13), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .5, WHITE);
                }
                else if (i + page * 20 == 14) {
                    DrawTextureEx(entityTextures.at(9), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .5, BLUE);
                }
                else if (i + page * 20 == 15) {
                    DrawTextureEx(entityTextures.at(9), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .5, RED);
                }
                else if (i + page * 20 == 4) {
                    DrawTextureEx(entityTextures.at(14), { pos.x + 3 * scale, pos.y + 3 * scale }, 0, scale * .5, WHITE);
                }
            }

        }
        for (int i = 0; i < specialSel.size(); i++) {

            specialSel.at(i).w = 16 * scale;
            specialSel.at(i).h = 16 * scale;
            Vec2 pos(destRec.x + destRec.width - (80 - UIXpos) * scale, destRec.y + (27 + i * 19) * scale);
            specialSel.at(i).pos = pos;

            specialSel.at(i).update();
            specialSel.at(i).draw();

            if (specialIndex == i) {
                specialSel.at(i).unHigh = GREEN;
            }
            else {
                specialSel.at(i).unHigh = BLUE;
            }

            if (specialSel.at(i).isDown) {
                specialIndex = i;
                curIndex = -1;
            }
        }

        for (int i = 0; i < tileSel.size(); i++) {
            tileSel.at(i).draw();
            tileSel.at(i).update();
            if (tileSel.at(i).isDown) {
                curIndex = i + page * 20;
                specialIndex = -1;
            }
            if (curIndex - page * 20 == i) {
                tileSel.at(i).unHigh = GREEN;
            }
            else {
                tileSel.at(i).unHigh = WHITE;
            }
        }

        save.w = 50 * scale;
        save.h = 40 * scale;
        save.pos = Vec2(destRec.x + destRec.width - (80 - UIXpos) * scale, destRec.y + destRec.height - 50 * scale);
        bool savePres = save.isDown;
        save.update();
        save.draw();
        if (save.isDown && !savePres) {
            saveLevelAs(*currentLevel, "LevelOneBeta");
        }
        bool swapPres = swapMode.isDown;

        swapMode.w = 50 * scale;
        swapMode.h = 40 * scale;
        swapMode.pos = Vec2(destRec.x + destRec.width - (80 - UIXpos) * scale, destRec.y + destRec.height - 95 * scale);
        swapMode.update();
        if (tileMode) {
            swapMode.unHigh = YELLOW;
            swapMode.high = YELLOW;
        }
        else {
            swapMode.unHigh = RED;
            swapMode.high = RED;
        }
        swapMode.draw();
        if (swapMode.isDown && !swapPres) {
            tileMode = !tileMode;
            curIndex = -2;
            specialIndex = -1;
        }

        xUp.w = 16 * scale;
        xUp.h = 16 * scale;
        xUp.pos = Vec2(destRec.x + destRec.width - (125 - UIXpos) * scale, destRec.y + destRec.height - 60 * scale);
        xUp.update();
        xUp.draw();
        if (xUp.pressed) {
            cursorSize.x++;
        }

        xDown.w = 16 * scale;
        xDown.h = 16 * scale;
        xDown.pos = Vec2(destRec.x + destRec.width - (125 - UIXpos) * scale, destRec.y + destRec.height - 35 * scale);

        xDown.update();
        xDown.draw();
        if (xDown.pressed && cursorSize.x > 1) {
            cursorSize.x--;
        }



        DrawTextEx;
        yUp.w = 16 * scale;
        yUp.h = 16 * scale;
        yUp.pos = Vec2(destRec.x + destRec.width - (107 - UIXpos) * scale, destRec.y + destRec.height - 60 * scale);
        yUp.update();
        yUp.draw();
        if (yUp.pressed) {
            cursorSize.y++;
        }

        yDown.w = 16 * scale;
        yDown.h = 16 * scale;
        yDown.pos = Vec2(destRec.x + destRec.width - (107 - UIXpos) * scale, destRec.y + destRec.height - 35 * scale);

        yDown.update();
        yDown.draw();
        if (yDown.pressed && cursorSize.y > 1) {
            cursorSize.y--;
        }

        DrawText(TextFormat("[X %i] [Y %i]", (int)cursorSize.x, (int)cursorSize.y), destRec.x + destRec.width - (124 - UIXpos) * scale, destRec.y + destRec.height - 43 * scale, 8 * scale, WHITE);

    }
};



//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------



    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    for (int i = 0; i < tileTexturePath.size(); i++) {
        tileTextures.at(i) = LoadTexture(tileTexturePath.at(i).c_str());
    }

    for (int i = 0; i < entityTexturePath.size(); i++) {
        entityTextures.push_back(LoadTexture(entityTexturePath.at(i).c_str()));
    }
    for (int i = 0; i < allTiles.size(); i++) {
        allTiles[i]->load();
    }
    worldSpaceCamera.zoom = 1.0f;
    worldSpaceCamera.offset = { virtualScreenWidth / 2,virtualScreenHeight / 2 };
    //screenSpaceCamera.zoom = 1.0f;

    RenderTexture2D target = LoadRenderTexture(virtualScreenWidth, virtualScreenHeight); // This is where we'll draw all our objects.

    sourceRec = { 0.0f, 0.0f, (float)target.texture.width, -(float)target.texture.height };
    destRec = { 0, 0, screenWidth , screenHeight };

    Vector2 origin = { 0.0f, 0.0f };




    Room* myLevel = new Room("L");
    Level trueLevel("copeMax");
    

    playerPos = { 0,0 };
    playerVel = { 0,0 };
    
    //myLevel.roomName
    //{"#####","#####","#####"}




    LevelEditor editor(&trueLevel,myLevel);







    bool editMode = false;
    int menu = 0;
   
    loadRoom(*myLevel, "Editor");
    trueLevel.addRoom(myLevel);
    
    loadLevel(trueLevel,trueLevel.levelName);
    float x = 0;
    float y = 0;
    float speed = 50;


    vector<Vec2> lineTemp;
    vector<Color> lineColor;
    myLevel->startLevel();

    vector<Vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(Vec2(rand() % virtualScreenWidth, rand() % virtualScreenHeight));
    }
    float t = 0;
    SetTargetFPS(120);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    button playButton({ virtualScreenWidth/2-50,virtualScreenHeight/2-50 }, 100,100,WHITE,GREEN);
    button controlButton({ virtualScreenWidth / 2 - 50,virtualScreenHeight / 2 + 80 }, 100, 20, WHITE, GREEN);
    Vec2 buttonPos = { virtualScreenWidth / 2 - 60 , virtualScreenHeight / 2 +10 };
    vector<button> saveFileButtons;
    saveFileButtons.push_back(button({ buttonPos.x,buttonPos.y }, 100, 20, WHITE, GREEN));
    saveFileButtons.push_back(button({ buttonPos.x,buttonPos.y+30 }, 100, 20, WHITE, GREEN));
    saveFileButtons.push_back(button({ buttonPos.x,buttonPos.y+60 }, 100, 20, WHITE, GREEN));
    vector<button> saveFileResetButtons;
    saveFileResetButtons.push_back(button({ buttonPos.x + 100,buttonPos.y }, 20, 20, RED, GREEN));
    saveFileResetButtons.push_back(button({ buttonPos.x + 100,buttonPos.y + 30 }, 20, 20, RED, GREEN));
    saveFileResetButtons.push_back(button({ buttonPos.x + 100,buttonPos.y + 60 }, 20, 20, RED, GREEN));

    button localSaveButton(button({ buttonPos.x,buttonPos.y- 30 }, 120, 20, RED, GREEN));
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {



        fElapsedTime = GetFrameTime();
        if (freezeTime) {
            fElapsedTime = 0;
        }
        worldTimer += fElapsedTime;
        if (fElapsedTime > .05) {
            fElapsedTime = .05;
        }
        scale = MIN((float)GetScreenWidth() / virtualScreenWidth, (float)GetScreenHeight() / virtualScreenHeight);
        mouse.x = GetMousePosition().x;
        mouse.y = GetMousePosition().y;
        virtualMouse.x = (mouse.x - (GetScreenWidth() - (virtualScreenWidth * scale)) * 0.5f) / scale;
        virtualMouse.y = (mouse.y - (GetScreenHeight() - (virtualScreenHeight * scale)) * 0.5f) / scale;


        destRec = { (GetScreenWidth() - ((float)virtualScreenWidth * scale)) * 0.5f, (GetScreenHeight() - ((float)virtualScreenHeight * scale)) * 0.5f,
                           (float)virtualScreenWidth * scale, (float)virtualScreenHeight * scale };
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        if (editMode) {

            Vector2 tempCamPos = editor.cameraPosition.rayVec2();
            worldSpaceCamera.target = { floor(tempCamPos.x),floor(tempCamPos.y) };

        }
        

        // Draw
        //----------------------------------------------------------------------------------
        BeginTextureMode(target);
        ClearBackground(BLACK);
        if (menu == 0) {
            DrawText("MY GAME 2", 10, 10, 70, WHITE);
            DrawText("Arrow Keys to move. Z to jump. X to fire.", 10, 70, 10, WHITE);
            DrawText("Start", 210, 130, 20, WHITE);
            playButton.update(virtualMouse);
            playButton.draw();
            if (!playButton.isDown&&playButton.wasDown) {
                
                menu = 1;
            }
            controlButton.update(virtualMouse);
            controlButton.draw();
            
        }
        else if (menu == 1) {
            localSaveButton.draw();
            localSaveButton.update(virtualMouse);
            
            if (localSaveButton.pressed) {
                loadLevel(trueLevel, "LevelOneBeta");
                saveLevelAs(trueLevel, "NOSAVE");
                currentSaveFile = "NOSAVE";
                menu = 2;

            }
            for (int i = 0; i < saveFileButtons.size(); i++) {
                saveFileButtons.at(i).update(virtualMouse);
                saveFileButtons.at(i).draw();
                
            }
            
            for (int i = 0; i < saveFileResetButtons.size(); i++) {
                saveFileResetButtons.at(i).update(virtualMouse);
                saveFileResetButtons.at(i).draw();
            }
            
            DrawText("NoSave", 190, 120, 10, RED);
            DrawText("if in shared files", 310, 120, 10, RED);

            DrawText("Save 1", 190, 150, 10, WHITE);
            DrawText("Save 2", 190, 180, 10, WHITE);
            DrawText("Save 3", 190, 210, 10, WHITE);
            if (saveFileButtons.at(0).isDown) {
                
                loadLevel(trueLevel, "SaveFile1");
                saveLevelAs(trueLevel, "SaveFile1");
                currentSaveFile = "SaveFile1";
                menu = 2;
            }
            else if (saveFileButtons.at(1).isDown) {
                loadLevel(trueLevel, "SaveFile2");
                saveLevelAs(trueLevel, "SaveFile2");
                currentSaveFile = "SaveFile2";
                menu = 2;
            }
            else if (saveFileButtons.at(2).isDown) {
                loadLevel(trueLevel, "SaveFile3");
                saveLevelAs(trueLevel, "SaveFile3");
                currentSaveFile = "SaveFile3";
                menu = 2;
            }
            if (saveFileResetButtons.at(0).isDown) {
                loadLevel(trueLevel, "LevelOneBeta");
                saveLevelAs(trueLevel, "SaveFile1");
            }
            else if (saveFileResetButtons.at(1).isDown) {
                loadLevel(trueLevel, "LevelOneBeta");
                saveLevelAs(trueLevel, "SaveFile2");
            }
            else if (saveFileResetButtons.at(2).isDown) {
                loadLevel(trueLevel, "LevelOneBeta");
                saveLevelAs(trueLevel, "SaveFile3");
            }
            
        }
        else if (menu == 2) {

            
            ClearBackground({ 0,34,86,255 });
            for (int i = 0; i < stars.size(); i++) {
                if (i < 50) {
                    DrawPixel(virtualScreenWidth - abs(((int)(worldSpaceCamera.target.x / 2 + stars.at(i).x)) % virtualScreenWidth), virtualScreenHeight - abs(((int)(worldSpaceCamera.target.y / 3 + stars.at(i).y)+1000) % virtualScreenHeight), { 200,200,200,255 });

                }
                else {
                    DrawPixel(virtualScreenWidth - abs(((int)(worldSpaceCamera.target.x / 4 + stars.at(i).x)) % virtualScreenWidth), virtualScreenHeight - abs(((int)(worldSpaceCamera.target.y / 4 + stars.at(i).y)+1000) % virtualScreenHeight), { 100,100,100,255 });

                }
            }
            
            BeginMode2D(worldSpaceCamera);

            if (IsKeyPressed(KEY_G) && !editMode) {
                editor.drawDebug = !editor.drawDebug;
                std::cout << "djsaklf;jdsa";
            }

            if (editMode) {
                editor.update(fElapsedTime);
                editor.draw();


            }
            else {
                
  
                trueLevel.runningLevel(worldSpaceCamera, virtualScreenWidth, virtualScreenHeight, fElapsedTime);
                
                trueLevel.drawLevel(worldSpaceCamera, virtualScreenWidth, virtualScreenHeight);
                //myLevel.drawLevel(editor.drawDebug);
                //myLevel.updateLevel();

            }


            EndMode2D();
            
            
            //DrawRectangle(0, 0, 50, 1000, GREEN);
            trueLevel.drawUI(worldSpaceCamera, virtualScreenWidth, virtualScreenHeight);
        }
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);
            

        DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
        if (editMode) {
            //cout << editor.currentRoom->roomName;
            freezeTime = false;
            editor.drawUI();
        }


        if (IsKeyPressed(KEY_RIGHT_SHIFT)) {
            currentSaveFile = "Editor";
            if (editMode) {

                
                saveLevelAs(trueLevel, trueLevel.levelName);
                saveLevelAs(trueLevel, "SaveFileE");
                loadLevel(trueLevel, trueLevel.levelName);
            }
            else {
                editor.cameraPosition = playerPos;
                //loadRoom(myLevel, "Editor");
                loadLevel(trueLevel, trueLevel.levelName);
                cout << trueLevel.levelName << endl;
                editor.currentRoom = editor.currentLevel->currentRoom;

            }
            editMode = !editMode;
        }
        /*for (int i = 0; i < trueLevel.rooms.size(); i++) {
            cout << trueLevel.rooms.at(i)->roomName << endl << endl;
            for (int j = 0; j < trueLevel.rooms.at(i)->eList.size(); j++) {
                cout << trueLevel.rooms.at(i)->eList.at(j)->type << endl;
            }
            cout << endl << endl << endl << endl;
        }*/
        DrawFPS(GetScreenWidth() - 80, 10);
        DrawFPS(GetScreenWidth() - 95, 10);
        /*DrawText(TextFormat("Screen resolution: %ix%i", screenWidth, screenHeight), 10, 10, 20, DARKBLUE);
        DrawText(TextFormat("World resolution: %ix%i", virtualScreenWidth, virtualScreenHeight), 10, 40, 20, DARKGREEN);
        DrawText(TextFormat("Pos: %ix%i", (int)x, (int)y), 10, 70, 20, DARKGREEN);
        DrawFPS(GetScreenWidth() - 95, 10);



        DrawText(TextFormat("Default Mouse: [%i , %i]", (int)mouse.x, (int)mouse.y), 350, 25, 20, GREEN);

        */
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

