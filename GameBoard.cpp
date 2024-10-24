#include "GameBoard.h"
#include <iostream>
#include <windows.h>
#include "Macros.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

GameBoard::GameBoard(int minX, int minY, int maxX, int maxY ){	
	snake = new Snake(minX+1, minY+1, RIGHT);
	this->minX = minX;
	this->minY = minY;
	this->maxX = maxX;
	this->maxY = maxY;
}

GameBoard::~GameBoard(){
	delete snake;
}

void GameBoard::drawBorder() {
	
    // Get the console handle
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // All 4 corners
    
    COORD pos = { minX - 1, minY - 1};
    SetConsoleCursorPosition(console, pos);
    cout << (char) TOP_LEFT_CORNER;
    
    pos = { maxX + 1, minY - 1};
    SetConsoleCursorPosition(console, pos);
    cout << (char) TOP_RIGHT_CORNER;
    
    pos = { minX - 1, maxY + 1};
    SetConsoleCursorPosition(console, pos);
    cout << (char) BOTTOM_LEFT_CORNER;
    
    pos = { maxX + 1, maxY + 1 };
    SetConsoleCursorPosition(console, pos);
    cout << (char) BOTTOM_RIGHT_CORNER;
    
    // Top border (start from minX)
    for (int x = minX; x <= maxX; ++x) {
        pos = {x, minY - 1};  // Coordinates for top border
        SetConsoleCursorPosition(console, pos);
        cout << (char) HORIZONTAL;
    }
    
    // Bottom border (start from minX)
    for (int x = minX; x <= maxX; ++x) {
        COORD pos = {x, maxY + 1};  // Coordinates for bottom border
        SetConsoleCursorPosition(console, pos);
        cout << (char) HORIZONTAL;
    }
    
    // Left and right borders
    for (int y = minY; y <= maxY; ++y) {
    	
        // Left border 
        COORD posLeft = {minX - 1, y};
        SetConsoleCursorPosition(console, posLeft);
        cout << (char) VERTICLE;
        
        // Right border
        COORD posRight = {maxX + 1, y};
        SetConsoleCursorPosition(console, posRight);
        cout << (char) VERTICLE;
    }
    
    // Reset cursor to the bottom right corner or an empty area
    COORD resetPos = {minX, maxY+1};
    SetConsoleCursorPosition(console, resetPos);
}

void GameBoard::drawSnake(){
	
	// Get the console handle
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Erase the tail position of snake
    int x = snake->getOldTailX();
    int y = snake->getOldTailY();
    COORD pos = { x, y };
    SetConsoleCursorPosition(console, pos);
    cout << " ";
    
    // draw the snake body ( Except Head )
    int length = snake->getLength();
	for(int i=1; i<length; i++ ){
		int x = snake->getBodySegment(i).getX();
		int y = snake->getBodySegment(i).getY();
		COORD pos = {x, y};
		SetConsoleCursorPosition(console, pos);
        cout << (char) BODY_SEGMENT;
	}
	
    // draw the head
    x = snake->getHeadX();
	y = snake->getHeadY();
	pos = {x, y};
	SetConsoleCursorPosition(console, pos);
    cout << (char) HEAD;
    
}

Snake& GameBoard::getSnake(){
	return *snake;
}

bool GameBoard::isBorderCollision(){
	int x = snake->getHeadX();
	int y = snake->getHeadY();
	if(x > maxX || y > maxY) return 1;
	else if( x < minX || y < minY ) return 1;
	return 0;
}

int GameBoard::generateFood(){
	
    // Seed the random number generator with the current time
    srand(time(0));

    // Generate two random number
    int x = rand() % (maxX - minX) + minX; // x position
	int y = rand() % (maxY - minY) + minY; // y position
	
	// food should not be generated at the area occupied by snake
	if( snake->isPositionOccupied( x, y ) ) return generateFood();
	
	food.x = x;
	food.y = y;
	
	return 0;
}

void GameBoard::drawFood(){
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {food.x, food.y};
	SetConsoleCursorPosition(console, pos);
    cout << (char) FOOD;
}

bool GameBoard::isSnakeEatingFood(){
	if( snake->getHeadX() == food.x && snake->getHeadY() == food.y ) return 1;
	else return 0;
}

