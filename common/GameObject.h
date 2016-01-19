#include "../../../juce.h"

#ifndef GAME_OBJECT__H
#define GAME_OBJECT__H

class GameObject
{
protected:
	Image* myImage;
	Rectangle bounds;
	CriticalSection imageCriticalSection;
public:
	virtual ~GameObject()
	{
	}
	virtual void update()=0;
	virtual int getX()=0;
	virtual int getY()=0;
	virtual bool redrawNeeded()=0;
	virtual void resized(int width, int height);
	virtual Image* getImage();
	void lockImage();
	void unlockImage();
	Rectangle& getBounds();
};

#endif