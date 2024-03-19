#pragma once
#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include <windows.h>
#include <iostream>
#include <vector>
#include "Bullet.h"

class MovingObject {
public:
    int x, y;
    std::vector<Bullet> bullets;

    MovingObject(int _x, int _y);

    void draw(HANDLE hConsole) const;
    void clear(HANDLE hConsole) const;
    void moveLeft();
    void moveRight();
    void shoot();
    void updateBullets();
};

#endif // MOVINGOBJECT_H
