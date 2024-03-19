#include "FallingObject.h"
#include "Bullet.h"

const int width = 70;
const int height = 25;

FallingObject::FallingObject(int _x, int _y, bool _isDouble) : x(_x), y(_y), isDouble(_isDouble) {}

void FallingObject::draw(HANDLE hConsole) const {
    SetConsoleCursorPosition(hConsole, { static_cast<SHORT>(x), static_cast<SHORT>(y) });
    if (isDouble)
        std::cout << "**";
    else
        std::cout << "*";
}

void FallingObject::clear(HANDLE hConsole) const {
    SetConsoleCursorPosition(hConsole, { static_cast<SHORT>(x), static_cast<SHORT>(y) });
    std::cout << "  ";
}

bool FallingObject::move() {
    clear(GetStdHandle(STD_OUTPUT_HANDLE));
    if (y < height - 2) {
        y++;
        draw(GetStdHandle(STD_OUTPUT_HANDLE));
        return true;
    }
    else {
        y = 1;
        x = rand() % (width - 2) + 1;
        draw(GetStdHandle(STD_OUTPUT_HANDLE));
        return true;
    }
}
