#include "Level.h"

Level::Level(string name) {
    levelName = name;

}

void Level::goToLastSave() {

}

void Level::onScreenTransition() {

    CompCamera* camTemp = dynamic_cast<CompCamera*>(camera->getComponent("CompCamera"));
    camTemp->changingScreens = true;
}

void Level::runningLevel(Camera2D& worldSpaceCamera, int virtualScreenWidth, int virtualScreenHeight, float fElapsedTime) {

    camera->scene = player->scene;

    for (int i = 0; i < rooms.size(); i++) {
        if (RectRectCollision({ player->pos.x / TILESIZE,player->pos.y / TILESIZE,0,0 }, { rooms.at(i)->pos.x, rooms.at(i)->pos.y,  (float)rooms.at(i)->width, (float)rooms.at(i)->height })) {

            if (currentRoom != rooms.at(i)) {
                if (player->pos.y / TILESIZE < currentRoom->pos.y) {
                    player->vel.y = -1000;
                }
                currentRoom = rooms.at(i);

                for (int j = 0; j < currentRoom->eList.size(); j++) {
                    if (currentRoom->eList.at(j)->type == "Player" || currentRoom->eList.at(j)->type == "Camera") {


                        currentRoom->eList.erase(currentRoom->eList.begin() + j);
                        j--;

                    }
                }

                player->scene = currentRoom;
                camera->scene = currentRoom;

                currentRoom->addEntity(player);
                currentRoom->addEntity(camera);
                onScreenTransition();
            }

        }

    }

    if (currentRoom) {


        //currentRoom->drawLevel();
        currentRoom->updateLevel(worldSpaceCamera, virtualScreenWidth, virtualScreenHeight, fElapsedTime);
    }
}

void Level::drawLevel(Camera2D& worldSpaceCamera, int virtualScreenWidth, int virtualScreenHeight) {

    for (int i = 0; i < rooms.size(); i++) {

        if (RectRectCollision({ worldSpaceCamera.target.x - virtualScreenWidth / worldSpaceCamera.zoom / 2, worldSpaceCamera.target.y - virtualScreenHeight / worldSpaceCamera.zoom / 2 ,virtualScreenWidth / worldSpaceCamera.zoom,virtualScreenHeight / worldSpaceCamera.zoom },
            { rooms.at(i)->pos.x * TILESIZE, rooms.at(i)->pos.y * TILESIZE, (float)rooms.at(i)->width * TILESIZE, (float)rooms.at(i)->height * TILESIZE })) {

            rooms.at(i)->drawLevel(worldSpaceCamera, virtualScreenWidth, virtualScreenHeight);

        }

    }

}
void Level::drawUI(Camera2D& worldSpaceCamera, int virtualScreenWidth, int virtualScreenHeight) {
    for (int i = 0; i < rooms.size(); i++) {

        if (RectRectCollision({ worldSpaceCamera.target.x - virtualScreenWidth / worldSpaceCamera.zoom / 2, worldSpaceCamera.target.y - virtualScreenHeight / worldSpaceCamera.zoom / 2 ,virtualScreenWidth / worldSpaceCamera.zoom,virtualScreenHeight / worldSpaceCamera.zoom },
            { rooms.at(i)->pos.x * TILESIZE, rooms.at(i)->pos.y * TILESIZE, (float)rooms.at(i)->width * TILESIZE, (float)rooms.at(i)->height * TILESIZE })) {

            rooms.at(i)->drawUI();

        }

    }

}

void Level::addRoom(Room* r) {
    rooms.push_back(r);

}
