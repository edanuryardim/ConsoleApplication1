#include "MovingObject.h"
#include "Bullet.h"

const int width = 70;
const int height = 25;

MovingObject::MovingObject(int _x, int _y) : x(_x), y(_y), bullets() {}

void MovingObject::draw(HANDLE hConsole) const {
    SetConsoleCursorPosition(hConsole, { static_cast<SHORT>(x), static_cast<SHORT>(y) });
    std::cout << "^";
}

void MovingObject::clear(HANDLE hConsole) const {
    SetConsoleCursorPosition(hConsole, { static_cast<SHORT>(x), static_cast<SHORT>(y) });
    std::cout << " ";
}

void MovingObject::moveLeft() {
    if (x > 1) x--;
}

void MovingObject::moveRight() {
    if (x < width - 2) x++;
}

void MovingObject::shoot() {
    bullets.push_back(Bullet(x, y - 1));
}

void MovingObject::updateBullets() {
    auto bullet = bullets.begin();
    while (bullet != bullets.end()) {
        if (!bullet->move()) {
            bullet = bullets.erase(bullet);
        }
        else {
            ++bullet;
        }
    }
}
