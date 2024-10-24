#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "snake.h"

struct Food {
	int x, y;
};

class GameBoard{
    int minX, minY, maxX, maxY;
    Snake *snake;
    Food food;
	public:
    GameBoard(int minX, int minY, int maxX, int maxY);
    ~GameBoard();
    void drawBorder();
    void drawSnake();
    Snake& getSnake();
    bool isBorderCollision();
    int generateFood();
    void drawFood();
	bool isSnakeEatingFood();
	bool isFreePosition(int x, int y);
	int getFreeDirectionForSnake(); 
	int getAutoDirection();  
};

#endif