#pragma once
#include <string>
#include "Vec2.h"
const int TILESIZE = 8;

struct TileProperties {
    //true = will stop player
    //false = player passes through

    bool solidLeft;
    bool solidRight;
    bool solidTop;
    bool solidBottom;

    //0 - no interaction
    //1 - stops hook but cannot hold on
    //2 - canHook

    bool stopBulletLeft;
    bool stopBulletRight;
    bool stopBulletTop;
    bool stopBulletBottom;

    //

    bool isSpike;
    bool platPassThru;

    bool operator==(TileProperties temp) {
        return solidLeft == temp.solidLeft &&
            solidRight == temp.solidRight &&
            solidTop == temp.solidTop &&
            solidBottom == temp.solidBottom;
        isSpike == temp.isSpike;
    }
};

enum TileRules
{

};
const TileProperties TILE_RULE_solid = { 1,1,1,1,1,1,1,1 };
const TileProperties TILE_RULE_solidBulPass = { 1,1,1,1,0,0,0,0 };
const TileProperties TILE_RULE_platformBulPass = { 0,0,1,0,0,0,0,0,0,1 };
const TileProperties TILE_RULE_background = { 0,0,0,0,0,0,0,0 };
const TileProperties TILE_RULE_backgroundBulStop = { 0,0,0,0,1,1,1,1 };
const TileProperties TILE_RULE_leftSpike = { 1,0,0,0,0,0,0,0,1 };
const TileProperties TILE_RULE_rightSpike = { 0,1,0,0,0,0,0,0,1 };
const TileProperties TILE_RULE_upSpike = { 0,0,1,0,0,0,0,0,1 };
const TileProperties TILE_RULE_downSpike = { 0,0,0,1,0,0,0,0,1 };
class Tile {
public:

    char tileType;
    Rectangle hitBox;
    TileProperties myProperties;



    Tile();
    Tile(char type, TileProperties myProp = { 1,1,1,1,1,1,1,1 }, Rectangle hitBoxSub = { 0,0,1,1 });
    virtual void draw(int x, int y);
    virtual void draw(float x, float y, float s = 1);
    virtual void load();
    void drawHitbox(int x, int y);
};

class SimpleTile : public Tile {
public:
    Color myColor;
    SimpleTile(char type, Color mColor, TileProperties myProp = { 1,1,1,1,1,1,1,1 },
        Rectangle hitBoxSub = { 0,0,1,1 });
    void draw(int x, int y);
    virtual void draw(float x, float y, float s = 1);
};
class SpriteTile : public Tile {
public:
    Texture2D myTex;
    std::string texPath;
    Color myTint;
    bool imSad = true;
    SpriteTile(char type, std::string texturePath, Color tint,
        TileProperties myProp = { 1,1,1,1,1,1,1,1 }, Rectangle hitBoxSub = { 0,0,1,1 });
    void load();
    void draw(int x, int y);
    virtual void draw(float x, float y, float s = 1);
};