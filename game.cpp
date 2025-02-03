/************************************
 * Автор: Важенин С.С               *
 * Дата:  17.12.2024                *
 * Название: "Змейка"               *
 ************************************/
#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

void setCursorPosition(short int x, short int y) {
    COORD position = {x, y};
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(outputHandle, position);
}

const int mapWidth = 30;
const int mapHeight = 18;
const int maxSnakeLength = (mapWidth - 3) * (mapHeight - 2);
const int directionUp = 0;
const int directionDown = 1;
const int directionLeft = 2;
const int directionRight = 3;

int currentDirection = directionUp;
bool gameRunning = true;

char gameMap[] =
"#############################\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#                           #\n"
"#############################\n";

char snakeSymbol = '*';
int snakeX[maxSnakeLength] = {0};
int snakeY[maxSnakeLength] = {0};
int snakeLength = 1;
int foodX = 1 + (rand() % (mapWidth - 3));
int foodY = 1 + (rand() % (mapHeight - 2));
char foodSymbol = '@';

int main() {
    snakeX[0] = mapWidth / 2;
    snakeY[0] = mapHeight / 2;
    double startTime = clock();

    while (gameRunning) {
        if (GetKeyState('W') & 0x8000 && currentDirection != directionDown) {
            currentDirection = directionUp;
        }
        if (GetKeyState('A') & 0x8000 && currentDirection != directionRight) {
            currentDirection = directionLeft;
        }
        if (GetKeyState('S') & 0x8000 && currentDirection != directionUp) {
            currentDirection = directionDown;
        }
        if (GetKeyState('D') & 0x8000 && currentDirection != directionLeft) {
            currentDirection = directionRight;
        }

        if ((clock() - startTime) / CLOCKS_PER_SEC >= 0.2) {
            startTime = clock();
            if (snakeX[0] == foodX && snakeY[0] == foodY) {
                ++snakeLength;
                foodX = 1 + (rand() % (mapWidth - 3));
                foodY = 1 + (rand() % (mapHeight - 2));
            }

            for (int i = snakeLength - 1; i > 0; --i) {
                snakeX[i] = snakeX[i - 1];
                snakeY[i] = snakeY[i - 1];
            }

            switch (currentDirection) {
                case directionUp:
                    --snakeY[0];
                    break;
                case directionDown:
                    ++snakeY[0];
                    break;
                case directionLeft:
                    --snakeX[0];
                    break;
                case directionRight:
                    ++snakeX[0];
                    break;
            }

            if (snakeX[0] == 0 || snakeY[0] == 0 || snakeX[0] == mapWidth - 2 || snakeY[0] == mapHeight - 2) {
                gameRunning = false;
            }

            for (int i = 1; i < snakeLength; ++i) {
                if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
                    gameRunning = false;
                }
            }

            setCursorPosition(0, 0);

            cout << "Score: " << snakeLength << endl;
            gameMap[foodY * mapWidth + foodX] = foodSymbol;
            for (int i = 0; i < snakeLength; ++i) {
                gameMap[snakeY[i] * mapWidth + snakeX[i]] = snakeSymbol;
            }
            cout << gameMap;
            for (int i = 0; i < snakeLength; ++i) {
                gameMap[snakeY[i] * mapWidth + snakeX[i]] = ' ';
            }
        }
    }

    cout << endl;
    cout << "Game over :( " << endl;
    cout << "Your score is " << snakeLength << endl;
    system("pause");
}
