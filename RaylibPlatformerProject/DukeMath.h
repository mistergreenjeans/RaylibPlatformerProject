#pragma once

#include "Vec2.h"

static bool RectRectCollision(Rectangle r1, Rectangle r2) {
    if (r1.x < r2.x + r2.width && r2.x < r1.x + r1.width && r1.y < r2.y + r2.height && r2.y < r1.y + r1.height) {
        return true;
    }
    return false;
}
static bool PointCircleCollision(float px, float py, float cx, float cy, float r) {
    if ((px - cx) * (px - cx) + (py - cy) * (py - cy) <= r * r) {
        return true;
    }
    else {
        return false;
    }
}
static bool RectCircleCollision(Rectangle r1, Vec2 circPos, float circRadi) {
    if (r1.x < circPos.x + circRadi && r1.x + r1.width > circPos.x - circRadi && r1.y<circPos.y && r1.y + r1.height>circPos.y) {
        return true;
    }
    else if (r1.y < circPos.y + circRadi && r1.y + r1.height > circPos.y - circRadi && r1.x<circPos.x && r1.x + r1.width>circPos.x) {
        return true;
    }
    else if (PointCircleCollision(r1.x, r1.y, circPos.x, circPos.y, circRadi)) {
        return true;
    }
    else if (PointCircleCollision(r1.x + r1.width, r1.y, circPos.x, circPos.y, circRadi)) {
        return true;
    }
    else if (PointCircleCollision(r1.x + r1.width, r1.y + r1.height, circPos.x, circPos.y, circRadi)) {
        return true;
    }
    else if (PointCircleCollision(r1.x, r1.y + r1.height, circPos.x, circPos.y, circRadi)) {
        return true;
    }
    else {
        return false;
    }
}

