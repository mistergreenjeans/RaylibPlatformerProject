#include "Entity.h"

Entity::Entity(Vec2 p, Vec2 s, layer mLayer, vector<Component*> mComp, string ty, bool updateOScreen) {
    type = ty;
    pos = p;
    spawnPos = pos;
    size = s;
    myLayer = mLayer;
    updateOffScreen = updateOScreen;
    for (int i = 0; i < mComp.size(); i++) {
        myComponents.push_back(mComp.at(i));
        mComp.at(i)->parent = this;
    }
}

Entity::Entity() {
    type = "basic";
    pos = { 0,0 };
    size = { 0,0 };
    myLayer = BASIC;
}

void Entity::addComponent(Component* myComp) {
    myComponents.push_back(myComp);
    myComp->parent = this;
}

Component* Entity::getComponent(string compName) {
    for (int i = 0; i < myComponents.size(); i++) {
        if (myComponents.at(i)->compoName == compName) {
            return myComponents.at(i);
        }
    }
    return nullptr;
}

void Entity::start() {
    for (int i = 0; i < myComponents.size(); i++) {
        myComponents.at(i)->parent = this;
        myComponents.at(i)->start();
    }
}

void Entity::update(float fElapsedTime) {

    for (int i = 0; i < myComponents.size(); i++) {
        myComponents.at(i)->update(fElapsedTime);
    }
    pos += vel * fElapsedTime;


}

void Entity::onRemove() {
    for (int i = 0; i < myComponents.size(); i++) {
        myComponents.at(i)->onRemove();
    }
}

void Entity::draw() {
    for (int i = 0; i < myComponents.size(); i++) {
        myComponents.at(i)->draw();
    }
}

void Entity::drawUI() {
    for (int i = 0; i < myComponents.size(); i++) {
        myComponents.at(i)->drawUI();
    }
}

void Entity::drawDebugging() {
    if (myLayer == BASIC) {
        DrawRectangleLinesEx({ (pos.x - size.x / 2) ,(pos.y - size.y / 2) ,size.x, size.y }, 2, WHITE);
    }
    else if (myLayer == ENEMY) {
        DrawRectangleLinesEx({ (pos.x - size.x / 2) ,(pos.y - size.y / 2) ,size.x, size.y }, 2, RED);
    }
    else if (myLayer == BULLET) {
        DrawRectangleLinesEx({ (pos.x - size.x / 2) ,(pos.y - size.y / 2) ,size.x, size.y }, 2, ORANGE);
    }
    else if (myLayer == PLAYER) {
        DrawRectangleLinesEx({ (pos.x - size.x / 2) ,(pos.y - size.y / 2) ,size.x, size.y }, 2, BLUE);
    }
    else if (myLayer == GROUND) {
        DrawRectangleLinesEx({ (pos.x - size.x / 2) ,(pos.y - size.y / 2) ,size.x, size.y }, 2, GREEN);
    }
    else if (myLayer == INTERACT) {
        DrawRectangleLinesEx({ (pos.x - size.x / 2) ,(pos.y - size.y / 2) ,size.x, size.y }, 2, PURPLE);
    }
    else if (myLayer == ITEM) {
        DrawRectangleLinesEx({ (pos.x - size.x / 2) ,(pos.y - size.y / 2) ,size.x, size.y }, 2, BLUE);
    }
    else if (myLayer == PBULLET) {
        DrawRectangleLinesEx({ (pos.x - size.x / 2) ,(pos.y - size.y / 2) ,size.x, size.y }, 2, MAGENTA);
    }
    else if (myLayer == DECOR) {
        DrawRectangleLinesEx({ (pos.x - size.x / 2) ,(pos.y - size.y / 2) ,size.x, size.y }, 2, { 102,195,255,10 });
    }
    if (updateOffScreen) {
        DrawRectangle((pos.x - size.x / 2), (pos.y - size.y / 2), 2, 2, WHITE);
    }
    for (int i = 0; i < myComponents.size(); i++) {
        myComponents.at(i)->drawDebugging();
    }


}

Vec2 Entity::getPos() {
    return pos;
}

void Entity::saveToTXT(ofstream& outStream) {

    outStream << type << endl;
    //outStream << myLayer << endl;
    outStream << (int)spawnPos.x << endl;
    outStream << (int)spawnPos.y << endl;
    //outStream << (int)size.x << endl;
    //outStream << (int)size.y << endl;
    outStream << updateOffScreen << endl;

    //outStream << "COMPONENTS:" << endl;
    //for (int i = 0; i < myComponents.size(); i++) {
    //    myComponents.at(i)->saveToTXT(outStream);


    //    outStream << "---END OF COMPONENT---" << endl;
    //}
    outStream << "###END OF ENTITY###" << endl;
}