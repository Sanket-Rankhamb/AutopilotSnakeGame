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

bool GameBoard::isFreePosition(int x, int y){
	if( x < minX || x > maxX) return 0;
	else if( y < minY || y > maxY) return 0;
	else return !snake->isPositionOccupied(x, y);
}

int GameBoard::getFreeDirectionForSnake(){
	int hx = snake->getHeadX();
	int hy = snake->getHeadY();
	if( isFreePosition(hx + 1, hy) ) return RIGHT;
	else if( isFreePosition(hx - 1, hy) ) return LEFT;
	else if( isFreePosition(hx, hy - 1) ) return UP;
	else if( isFreePosition(hx, hy + 1) ) return RIGHT;
	else return snake->getDirection();
}

int GameBoard::getAutoDirection(){
	
	int d = snake->getDirection(), dir; // new direciton
	int hx = snake->getHeadX();
	int hy = snake->getHeadY();
	int fx = food.x;
	int fy = food.y;

	if( d == RIGHT ){
		
		if(hy == fy){ // s and f at same line
			if(hx < fx) dir = RIGHT; // f is infront of s
			else dir = ( (hy == minY || hy != maxY) ? DOWN : UP ); //f is backword of s
		} 
		
		else if(hx == fx) dir = ( (hy < fy ) ? DOWN : UP );// s and f are in same column
		
		else if(hx < fx) dir = RIGHT;
		
		else if( hy < fy) dir = DOWN; // s is upside of f
		else dir = UP; // s is downside of f
		
	}
	else if( d == LEFT ){
		
		if(hy == fy ){
			if(hx > fx) dir = LEFT;
			else dir = ( (hy == minY || hy != maxY) ? DOWN : UP );
		} 
		
		else if(hx == fx) dir = ( (hy < fy ) ? DOWN : UP );
		
		else if(hx > fx) dir = LEFT;
		
		else if( hy < fy) dir = DOWN;
		else dir = UP;	
			
	}
	else if( d == UP ){
		
		if(hx == fx){ // s and f are in same column
			if(hy > fy) dir = UP;  // f is infront of s
			else dir = ( (hx == minX || hx != maxX) ? RIGHT : LEFT ); // f is backword of s
		} 
		
		else if(hy == fy) dir = ( (hx < fx ) ? RIGHT : LEFT ); // s and f are in same line
		
		else if(hy > fy) dir = UP;
		
		else if( hx < fx ) dir = RIGHT;
		else dir = LEFT;
		
	}
	else if( d == DOWN ){
		
		if(hx == fx){ // s and f are in same column
			if(hy < fy) dir = DOWN;  // f is infront of s
			else dir = ( (hx == minX || hx != maxX) ? RIGHT : LEFT ); // f is backword of s
		} 
		
		else if(hy == fy) dir = ( (hx < fx ) ? RIGHT : LEFT ); // s and f are in same line
		
		else if(hy < fy) dir = DOWN;
		
		else if( hx < fx ) dir = RIGHT;
		else dir = LEFT;
		
	}
	
	// check for desided direction doesn't cause self colision
	
	int x, y;
	if(dir == RIGHT){
		x = hx + 1;
		y = hy;
	}
	else if(dir == LEFT){
		x = hx - 1;
		y = hy;
	}
	else if(dir == UP){
		x = hx;
		y = hy - 1;
	}
	else if(dir == DOWN){
		x = hx;
		y = hy + 1;
	}
	
	if( !isFreePosition(x, y) ) dir = getFreeDirectionForSnake();
	
	return dir;
}



