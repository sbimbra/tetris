#include "GameObject.h"

#ifndef BALL__H
#define BALL__H

class Ball : public GameObject
{
	int x;
	int y;
	int dx;
	int dy;
	int size;
	Random rng;
	int width;
	int height;
	bool redrawMe;
public:
	Ball(int width, int height);
	~Ball();
	int getX();
	int getY();
	int getSize();
	bool redrawNeeded();
	void update();
	Image* getImage();
};

#endif