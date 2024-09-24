#pragma once
#include <corecrt_math.h>
#include "raylib.h"

class Vec2 {
public:
    float x;
    float y;
    float m;
    Vec2(float x1, float y1) {
        x = x1;
        y = y1;
        m = getMagnitude();
    }
    Vec2() {
        x = 0;
        y = 0;
        m = 0;
    }
    Vec2(Vector2 temp) {
        x = temp.x;
        y = temp.y;
        m = getMagnitude();
    }
    Vec2 getLeft() {
        return Vec2(-y, x);
    }
    Vector2 rayVec2() {
        return { x,y };
    }
    Vec2 rotate(double a, double cx = 0, double cy = 0) {
        if (a != 0) {
            Vec2 re(cx + (x - cx) * cos(a) - (y - cy) * sin(a), cy + (x - cx) * sin(a) + (y - cy) * (cos(a)));
            return re;
        }
        else {
            return Vec2(x, y);
        }

    }
    float dot(Vec2 v) {
        return x * v.x + y * v.y;
    }

    Vec2 project(Vec2 v) {
        float vMag = v.getMagnitude();
        return v * (dot(v) / (vMag * vMag));
    }
    float getDistance(Vec2 temp) {
        return sqrt((x - temp.x) * (x - temp.x) + (y - temp.y) * (y - temp.y));
    }
    float getMagnitude() {
        m = sqrt(x * x + y * y);
        return m;
    }
    float getAngle() {
        return atan2(y, x);
    }
    Vec2 normalize() {
        getMagnitude();
        if (m == 0) {
            return Vec2(0, 0);
        }
        return Vec2(x / m, y / m);
    }
    bool operator==(Vec2 temp) {
        return x == temp.x && y == temp.y;
    }
    Vec2 operator+(Vec2 temp) {
        return Vec2(x + temp.x, y + temp.y);
    }
    Vec2 operator-(Vec2 temp) {
        return Vec2(x - temp.x, y - temp.y);
    }
    void operator+=(Vec2 temp) {
        x += temp.x;
        y += temp.y;
    }
    void operator-=(Vec2 temp) {
        x -= temp.x;
        y -= temp.y;
    }
    Vec2 operator*(double temp) {
        return Vec2(x * temp, y * temp);
    }
    Vec2 operator/(double temp) {
        return Vec2(x / temp, y / temp);
    }
    void operator*=(double temp) {
        x *= temp;
        y *= temp;
    }
    void operator/=(double temp) {
        x /= temp;
        y /= temp;
    }
};