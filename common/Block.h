#include "../../../juce.h"
#include "GameObject.h"

#ifndef BLOCK__H
#define BLOCK__H

class Block : public GameObject
{
protected:
	bool redrawMe;
	int worldX;
	int worldY;
	int gridX;
	int gridY;
	int rotationIndex;
	OwnedArray<StringArray> shapes;
	Colour blockColour;
public:
	virtual ~Block();
	Image* getImage();
	void init();
	StringArray* getBlockShape();
	void update();
	int getX();
	int getY();
	int getGridX();
	int getGridY();
	void drawBlock();
	bool redrawNeeded();
	bool moveDown();
	bool moveRight();
	bool moveLeft();
	bool rotateLeft();
	bool rotateRight();
	StringArray* getRotatedRightBlockShape();
	StringArray* getRotatedLeftBlockShape();
	virtual void createBlocks()=0;
};

#endif