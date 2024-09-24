#include "Tile.h"

Tile::Tile() {
    tileType = '?';
    hitBox = { 0,0,1,1 };
    myProperties = { 1,1,1,1,1,1,1,1 };
}

Tile::Tile(char type, TileProperties myProp, Rectangle hitBoxSub) {
    tileType = type;
    hitBox = hitBoxSub;
    hitBox.x *= TILESIZE;
    hitBox.y *= TILESIZE;
    hitBox.width *= TILESIZE;
    hitBox.height *= TILESIZE;
    myProperties = myProp;
}

void Tile::draw(int x, int y) {
    Rectangle temp = hitBox;
    temp.x += x * TILESIZE;
    temp.y += y * TILESIZE;
    if (tileType == '#') {
        DrawRectangleLines(temp.x, temp.y, temp.width, temp.height, RED);
    }
    if (tileType == '-') {
        DrawRectangleLines(temp.x, temp.y, temp.width, temp.height, GRAY);
    }
    else if (tileType == '?') {
        DrawRectangleLines(temp.x, temp.y, temp.width, temp.height, PINK);
    }
    else {
        //DrawRectangleLinesEx(temp, 1, { 30,30,30,30 });
    }

}

void Tile::draw(float x, float y, float s) {
    Rectangle temp = hitBox;
    temp.x += x;
    temp.y += y;
    if (tileType == '#') {
        DrawRectangle(temp.x, temp.y, temp.width * s, temp.height * s, RED);
    }
    if (tileType == '-') {
        DrawRectangle(temp.x, temp.y, temp.width * s, temp.height * s, GRAY);
    }
    else if (tileType == '?') {
        DrawRectangle(temp.x, temp.y, temp.width * s, temp.height * s, PINK);
    }
    else {
        //DrawRectangleLinesEx(temp, 1, { 30,30,30,30 });
    }

}

void Tile::load() {

}

void Tile::drawHitbox(int x, int y) {
    Rectangle temp = hitBox;
    temp.x += x * TILESIZE;
    temp.y += y * TILESIZE;
    DrawRectangleLinesEx(temp, 1, GRAY);
}

SimpleTile::SimpleTile(char type, Color mColor, TileProperties myProp, Rectangle hitBoxSub) :Tile(type, myProp, hitBoxSub) {
    myColor = mColor;
}

void SimpleTile::draw(int x, int y) {
    Rectangle temp = hitBox;


    temp.x += x * TILESIZE;
    temp.y += y * TILESIZE;


    DrawRectangle(temp.x, temp.y, temp.width, temp.height, myColor);
}

void SimpleTile::draw(float x, float y, float s) {
    Rectangle temp = hitBox;
    temp.x *= s;
    temp.y *= s;


    temp.x += x;
    temp.y += y;

    temp.width *= s;
    temp.height *= s;

    DrawRectangle(temp.x, temp.y, temp.width, temp.height, myColor);

}

SpriteTile::SpriteTile(char type, std::string texturePath, Color tint, TileProperties myProp, Rectangle hitBoxSub) :Tile(type, myProp, hitBoxSub) {
    texPath = texturePath;


    myTint = tint;
}

void SpriteTile::load() {
    myTex = LoadTexture(texPath.c_str());
}

void SpriteTile::draw(int x, int y) {
    Rectangle temp = hitBox;


    temp.x += x * TILESIZE;
    temp.y += y * TILESIZE;


    DrawTexture(myTex, x * TILESIZE, y * TILESIZE, myTint);
}

void SpriteTile::draw(float x, float y, float s) {
    if (!imSad) {
        Rectangle temp = hitBox;
        temp.x *= s;
        temp.y *= s;


        temp.x += x;
        temp.y += y;

        temp.width *= s;
        temp.height *= s;

        DrawTextureEx(myTex, { x, y }, 0, s, myTint);
    }




}