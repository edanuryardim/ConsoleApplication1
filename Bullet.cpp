#include "Bullet.h"


Bullet::Bullet(int _x, int _y) : x(_x), y(_y) {}

void Bullet::draw(HANDLE hConsole) const {
    SetConsoleCursorPosition(hConsole, { static_cast<SHORT>(x), static_cast<SHORT>(y) });
    std::cout << "|";
}

void Bullet::clear(HANDLE hConsole) const {
    SetConsoleCursorPosition(hConsole, { static_cast<SHORT>(x), static_cast<SHORT>(y) });
    std::cout << " ";
}

bool Bullet::move() {
    if (y > 1) {
        clear(GetStdHandle(STD_OUTPUT_HANDLE));
        y--;
        return true;
    }
    return false; // Bullet reached the top
}
