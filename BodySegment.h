#ifndef BODYSEGMENT_H
#define BODYSEGMENT_H

class BodySegment{
	int x, y;
	public:
		BodySegment();
		void setPosition( int x, int y);
		int getX();
		int getY();
};

#endif
