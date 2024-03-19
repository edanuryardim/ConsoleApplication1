#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <windows.h>
#include <iostream>

class Bullet {
public:
    int x, y;

    Bullet(int _x, int _y);

    void draw(HANDLE hConsole) const;
    void clear(HANDLE hConsole) const;
    bool move();
};

#endif // BULLET_H
