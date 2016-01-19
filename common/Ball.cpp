#include "Ball.h"
Ball::Ball(int width, int height) : rng(Time::getHighResolutionTicks())
{
	redrawMe = true;
	this->width = width;
	this->height = height;
	x = rng.nextInt(width/2);
	y = rng.nextInt(height/2);		
	dx = rng.nextInt(10);
	dy = rng.nextInt(10);
	size = 30;
	myImage = new Image(Image::ARGB,size,size,true);
	Graphics g(*myImage);
	g.setColour(Colours::blue);
	g.fillEllipse(0,0,size-10,size-10);
	DropShadowEffect dropShadow;
	dropShadow.applyEffect(*myImage,g);
	bounds = Rectangle(x,y,size,size);
}

Ball::~Ball()
{
	if(myImage)
	{
		deleteAndZero(myImage);
	}
}

int Ball::getX()
{
	return x;
}

int Ball::getY()
{
	return y;
}

int Ball::getSize()
{
	return size;
}

bool Ball::redrawNeeded()
{
	return redrawMe;
}

void Ball::update()
{
	if(!(x > 0 && x < (width-size)))
	{
		dx = -dx;
	}

	if(!(y > 0 && y < (height-size)))
	{
		dy = -dy;
	}

	x += dx;
	y += dy;
	redrawMe = true;
}

Image* Ball::getImage()
{
	redrawMe = false;
	return myImage;
}