#pragma once
#ifndef FALLINGOBJECT_H
#define FALLINGOBJECT_H

#include <windows.h>
#include <iostream>

class FallingObject {
public:
    int x, y;
    bool isDouble;

    FallingObject(int _x, int _y, bool _isDouble);

    void draw(HANDLE hConsole) const;
    void clear(HANDLE hConsole) const;
    bool move();
};

#endif // FALLINGOBJECT_H
