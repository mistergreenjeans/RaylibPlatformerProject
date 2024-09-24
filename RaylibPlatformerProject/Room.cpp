#include "Room.h"

Room::Room() {
    roomName = "NewLevel";
    tileSet.push_back({ {new Tile(' ',TILE_RULE_background)}});
    background.push_back({ new Tile(' ',TILE_RULE_background) });
}
Room::Room(std::string name) {
    roomName = name;
    tileSet.push_back({ { new Tile(' ',TILE_RULE_background)} });
    background.push_back({ new Tile(' ',TILE_RULE_background) });
}

void Room::addEntity(Entity* add) {

    add->scene = this;
    add->start();
    eList.push_back(add);
}

void Room::drawLevel(Camera2D& worldSpaceCamera, int virtualScreenWidth, int virtualScreenHeight, bool debugMode) {


    int tempLeft = (worldSpaceCamera.target.x - virtualScreenWidth / 2 / worldSpaceCamera.zoom) / TILESIZE - pos.x;
    int tempRight = ((worldSpaceCamera.target.x + virtualScreenWidth / 2 / worldSpaceCamera.zoom) / TILESIZE + 1 - pos.x);
    int tempTop = (worldSpaceCamera.target.y - virtualScreenHeight / 2 / worldSpaceCamera.zoom) / TILESIZE - pos.y;
    int tempBottom = ((worldSpaceCamera.target.y + virtualScreenHeight / 2 / worldSpaceCamera.zoom) / TILESIZE + 1 - pos.y);

    if (tempLeft < pos.x) {
        tempLeft = 0;
    }
    if (tempTop < pos.y) {
        tempTop = 0;
    }
    if (tempRight > pos.x + width) {
        tempRight = width;
    }
    if (tempBottom > pos.y + height) {
        tempBottom = height;
    }
    for (int i = tempTop; i < tempBottom; i++) {
        for (int j = tempLeft; j < tempRight; j++) {
            if (i < background.size() && j < background.at(i).size())
                background.at(i).at(j)->draw((int)(j + pos.x), (int)(i + pos.y));
        }

    }
    for (int i = tempTop; i < tempBottom; i++) {
        for (int j = tempLeft; j < tempRight; j++) {
            if (i < tileSet.size() && j < tileSet.at(i).size())
                tileSet.at(i).at(j)->draw((int)(j + pos.x), (int)(i + pos.y));
        }

    }
    for (int i = 0; i < eList.size(); i++) {
        eList.at(i)->draw();
        if (debugMode) {
            eList.at(i)->drawDebugging();
        }
    }
}

void Room::drawUI() {
    for (int i = 0; i < eList.size(); i++) {
        eList.at(i)->drawUI();

    }
}

void Room::startLevel() {
    for (int i = 0; i < eList.size(); i++) {
        eList.at(i)->start();
        eList.at(i)->scene = this;
    }
}

void Room::updateLevel(Camera2D& worldSpaceCamera, int virtualScreenWidth, int virtualScreenHeight, float fElapsedTime) {
    width = tileSet.at(0).size();
    height = tileSet.size();
    int w = virtualScreenWidth + 120;
    int h = virtualScreenHeight + 120;
    int x = worldSpaceCamera.target.x - w / 2;
    int y = worldSpaceCamera.target.y - h / 2;
    //update offScreen
    //DrawRectangleLines(x, y, w, h, PURPLE);

    for (int i = 0; i < eList.size(); i++) {
        if (eList.at(i)->removeMe) {
            eList.at(i)->onRemove();
            eList.erase(eList.begin() + i);
            i--;
            continue;
        }
        if (eList.at(i)->updateOffScreen || (eList.at(i)->pos.x > x && eList.at(i)->pos.y > y && eList.at(i)->pos.x < x + w && eList.at(i)->pos.y < y + h)) {
            eList.at(i)->isOnScreen = true;
            eList.at(i)->update(fElapsedTime);
        }
        else {
            eList.at(i)->isOnScreen = false;
        }


    }
}

void Room::drawLevel2(float ratioL, Camera2D& worldSpaceCamera, int virtualScreenWidth, int virtualScreenHeight) {

    int tempLeft = (worldSpaceCamera.target.x - virtualScreenWidth / ratioL / 2) / TILESIZE;
    int tempRight = (worldSpaceCamera.target.x + virtualScreenWidth / ratioL / 2) / TILESIZE + 1;
    int tempTop = (worldSpaceCamera.target.y - virtualScreenHeight / ratioL / 2) / TILESIZE;
    int tempBottom = (worldSpaceCamera.target.y + virtualScreenHeight / ratioL / 2) / TILESIZE + 1;


    if (tempLeft < 0) {
        tempLeft = 0;
    }
    if (tempTop < 0) {
        tempTop = 0;
    }
    if (tempRight > tileSet.at(0).size()) {
        tempRight = tileSet.at(0).size();
    }
    if (tempBottom > tileSet.size()) {
        tempBottom = tileSet.size();
    }

    for (int i = tempTop; i < tempBottom; i++) {
        for (int j = tempLeft; j < tempRight; j++) {

            background.at(i).at(j)->draw(j, i);
        }

    }
    for (int i = tempTop; i < tempBottom; i++) {
        for (int j = tempLeft; j < tempRight; j++) {

            tileSet.at(i).at(j)->draw(j, i);
        }

    }

}