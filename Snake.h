#ifndef snake_H
#define snake_H

#include "BodySegment.h"

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

class Snake{
	
	protected:
		BodySegment *body, oldTail;
		int capacity, length;
		short int direction;
		
	public:
		
		Snake();
		Snake(int hx, int hy, int direction);
		~Snake();
		int getLength();
		int getDirection();
		int getHeadX();
		int getHeadY();
		BodySegment& getBodySegment(int index);
		int getOldTailX();
		int getOldTailY();
		bool isHeadAt( int x, int y);
		void grow();
		void followHead();
		void moveRight();
		void moveLeft();
		void moveUp();
		void moveDown();
    	bool isSelfCollision();
    	bool isPositionOccupied(int x, int y);
		
};

#endif
