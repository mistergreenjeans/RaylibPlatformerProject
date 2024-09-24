#include "Component.h"

Component::Component() {
	parent = nullptr;
	compoName = "basic";
}


void Component::start() {

}

void Component::update(float fElapsedTime) {

}

void Component::onRemove() {

}
void Component::draw() {

}

void Component::drawDebugging() {

}

void Component::drawUI() {

}

CompCamera::CompCamera(int virtualScreenWidth, int virtualScreenHeight, int natrualZoom, bool& freezeTime, Camera2D& worldSpaceCamera) : freezeTime(freezeTime), worldSpaceCamera(worldSpaceCamera) {
    compoName = "CompCamera";
    camHeight = virtualScreenHeight / natrualZoom + TILESIZE / 2;
    camWidth = virtualScreenWidth / natrualZoom + TILESIZE / 2;

    this->virtualScreenWidth = virtualScreenWidth;
    this->worldSpaceCamera = worldSpaceCamera;
    this->natrualZoom = natrualZoom;
}

void CompCamera::start() {
    for (int i = 0; i < parent->scene->eList.size(); i++) {
        if (parent->scene->eList.at(i)->myLayer == PLAYER) {
            player = parent->scene->eList.at(i);
        }
    }
    levelHeight = (parent->scene->tileSet.size() * TILESIZE);
    levelWidth = (parent->scene->tileSet.at(0).size() * TILESIZE);
    parent->pos = player->pos;
}

void CompCamera::update(float fElapsedTime) {

    if ((player->pos - parent->pos).getMagnitude() > virtualScreenWidth) {
        parent->pos = player->pos;
    }

    parent->pos += ((player->pos - parent->pos) * .6) * fElapsedTime;
    xt = player->vel.x / 120;
    //if (player->vel.x<0) {
    //    xt = -1;
    //}
    //if (player->vel.x > 0) {
    //    xt = 1;
    //}
    Vec2 distTemp = player->pos + (Vec2(xt * 40, 0)) - parent->pos;

    //DrawCircle(playerPos.x + xt * 30, playerPos.y, 2, GREEN);

    parent->pos.x += (distTemp.x * abs(distTemp.x)) * fElapsedTime / 15;
    parent->pos.y += (distTemp.y * abs(distTemp.y)) * fElapsedTime / 9;

    Rectangle lW = { parent->pos.x - camWidth / 2 - parent->scene->pos.x * TILESIZE, parent->pos.y - camHeight / 2 - parent->scene->pos.y * TILESIZE, camWidth , camHeight };



    if (lW.y + lW.height > levelHeight) {
        parent->pos.y = levelHeight - lW.height / 2 + parent->scene->pos.y * TILESIZE;
    }
    if (lW.y < 0) {
        parent->pos.y = lW.height / 2 + parent->scene->pos.y * TILESIZE;
    }
    if (lW.x + lW.width > levelWidth) {
        parent->pos.x = levelWidth - lW.width / 2 + parent->scene->pos.x * TILESIZE;
    }
    if (lW.x < 0) {
        parent->pos.x = lW.width / 2 + parent->scene->pos.x * TILESIZE;
    }

    if (camHeight > levelHeight) {
        parent->pos.y = levelHeight / 2 + parent->scene->pos.y * TILESIZE;

    }
    if (camWidth > levelWidth) {
        parent->pos.x = levelWidth / 2 + parent->scene->pos.x * TILESIZE;
    }



    DesiredLocation = Vec2((int)parent->pos.x, (int)parent->pos.y);




    if (changingScreens) {

        freezeTime = true;
        followPlayer = false;

        if (t == 0) {
            tranStart = worldSpaceCamera.target;

            tranEnd = DesiredLocation;

        }
        t += GetFrameTime();
        if (t > 1) {
            changingScreens = false;
            t = 0;
            followPlayer = true;
            freezeTime = false;
        }


        Vec2 tempPos = (tranEnd - tranStart) * (t * t * (3 - 2 * t)) + tranStart;
        tempPos.x = (int)tempPos.x;
        tempPos.y = (int)tempPos.y;
        worldSpaceCamera.target = tempPos.rayVec2();
        worldSpaceCamera.zoom = natrualZoom;
    }
    if (followPlayer) {
        worldSpaceCamera.target = DesiredLocation.rayVec2();
        worldSpaceCamera.zoom = natrualZoom;
    }
    //Vec2 left  = player->pos - Vec2(40, 0);
    //Vec2 right = player->pos + Vec2(40, 0);

    //DrawLine(left.x, left.y, right.x, right.y, ORANGE);







}