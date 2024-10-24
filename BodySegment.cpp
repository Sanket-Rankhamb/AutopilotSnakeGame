#include "BodySegment.h"

BodySegment::BodySegment(){
	x = 10; 
	y = 10;
}

void BodySegment::setPosition(int x, int y){
	this->x = x;
	this->y = y;
}

int BodySegment::getX(){
	return x;
}

int BodySegment::getY(){
	return y;
}
