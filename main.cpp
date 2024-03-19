#include <iostream>
#include <vector>
#include <conio.h>
#include <cstdlib> // For random number generation
#include <ctime>   // For seeding random number generator
#include "Bullet.h"
#include "FallingObject.h"
#include "MovingObject.h"

using namespace std;

const int width = 70;
const int height = 25;

enum GameStatus {
    PLAYING,
    PAUSED,
    EXIT
};

GameStatus gameStatus = PLAYING;

void drawPlayingArea() {
    system("cls");
    for (int i = 0; i < width; ++i) cout << "-";
    cout << endl;
    for (int i = 1; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if ((j == 0 || j == width - 1) && i != height - 1) cout << "|"; // Skip drawing '|' in the last row
            else cout << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < width; ++i) cout << "-";

    // Print additional text on the right side
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<SHORT>(width + 5), 0 });
    cout << "Press p to pause" << endl;
    cout << "                                                                           Press x to exit" << endl;
    cout << "                                                                           Press right and left to play" << endl;
    cout << "                                                                           Status:";
    switch (gameStatus) {
    case PLAYING:
        cout << "Playing";
        break;
    case PAUSED:
        cout << "Paused";
        break;
    case EXIT:
        cout << "Exiting";
        break;
    }
}

int score = 0;

void drawScore() {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { static_cast<SHORT>(width - 15), 0 });
    cout << "Score: " << score;
}

void checkCollision(MovingObject& obj, vector<FallingObject>& asteroids) {
    auto bullet = obj.bullets.begin();
    while (bullet != obj.bullets.end()) {
        auto asteroid = asteroids.begin();
        while (asteroid != asteroids.end()) {
            if (bullet->x == asteroid->x && bullet->y == asteroid->y) {
                bullet = obj.bullets.erase(bullet); // Remove bullet
                asteroid->clear(GetStdHandle(STD_OUTPUT_HANDLE)); // Clear asteroid from display
                if (asteroid->isDouble)
                    score += 20; // Increase score by 2 for double stars
                else
                    score += 40; // Increase score by 1 for single stars
                asteroid = asteroids.erase(asteroid); // Remove asteroid
                break; // Exit asteroid loop
            }
            else {
                ++asteroid;
            }
        }
        if (bullet != obj.bullets.end()) {
            ++bullet;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    MovingObject obj(width / 2, height - 2);
    vector<FallingObject> asteroids;

    drawPlayingArea();

    while (gameStatus != EXIT) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 'p' || key == 'P') {
                gameStatus = (gameStatus == PAUSED) ? PLAYING : PAUSED;
                drawPlayingArea();
            }
            else if (key == 'x' || key == 'X') {
                gameStatus = EXIT;
                drawPlayingArea();
                break;
            }
            else if (key == 77) { // Sağ ok tuşu
                if (gameStatus == PLAYING) {
                    obj.clear(hConsole); // Önceki konumu temizle
                    obj.moveRight();
                }
            }
            else if (key == 75) { // Sol ok tuşu
                if (gameStatus == PLAYING) {
                    obj.clear(hConsole); // Önceki konumu temizle
                    obj.moveLeft();
                }
            }
            else if (key == 32) { // Space bar
                if (gameStatus == PLAYING) {
                    obj.shoot();
                }
            }
        }

        if (gameStatus == PLAYING) {
            obj.draw(hConsole);
            obj.updateBullets();
            for (const auto& bullet : obj.bullets) {
                bullet.draw(hConsole);
            }

            drawScore();

            checkCollision(obj, asteroids);

            if (rand() % 20 == 0) {
                if (rand() % 2 == 0)
                    asteroids.push_back(FallingObject(rand() % (width - 2) + 1, 1, true)); // Double star
                else
                    asteroids.push_back(FallingObject(rand() % (width - 2) + 1, 1, false)); // Single star
            }

            for (auto& asteroid : asteroids) {
                asteroid.draw(hConsole);
                if (!asteroid.move()) {
                    continue;
                }
            }
        }

        Sleep(100);
    }

    return 0;
}
