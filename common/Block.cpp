#include "Block.h"

void Block::init()
{
	myImage = 0;
	redrawMe = true;
	rotationIndex = 0;
	gridX = 4;
	gridY = 0;
	worldX = 5 + gridX*30;
	worldY = 0;
	createBlocks();
	drawBlock();
}

Block::~Block()
{
	if(myImage)
	{
		delete myImage;
	}
}
Image* Block::getImage()
{
	return myImage;
}

void Block::drawBlock()
{
	lockImage();
	if(myImage)
	{
		delete myImage;
	}
	myImage = new Image(Image::ARGB,120,120,true); // cells are 30 wide by 30 high, so always 80x80
	int drawn = 0; 
	Graphics g(*myImage);

	StringArray shape = *(getBlockShape());
	int x = 0;
	int y = 0;
	int width = 30;
	int height = 30;
	g.setColour(blockColour);
	for(int i = 0; i < 4; i++)
	{
		x = 0;
		for(int j = 0; j < 4 && drawn < 4; j++)
		{
			if(shape[i][j] == 'a')
			{
				drawn++;
				g.fillRect(x,y,width,height);
				g.drawBevel(x,y,width,height,width,blockColour.brighter(.75f),blockColour.darker(.75f),true);
			}
			x += width;
		}
		y += height;
	}
	unlockImage();
}

StringArray* Block::getBlockShape()
{
	return shapes[rotationIndex];
}

void Block::update()
{

}

int Block::getX()
{
	return worldX;
}

int Block::getY()
{
	return worldY;
}

int Block::getGridX()
{
	return gridX;
}

int Block::getGridY()
{
	return gridY;
}

bool Block::redrawNeeded()
{
	return redrawMe;
}

bool Block::moveDown()
{
	gridY++;
	worldY += 30;
	return true;
}

bool Block::moveRight()
{
	// check collision first
	gridX++;
	worldX += 30;
	return true;
}

bool Block::moveLeft()
{
	// check collision
	gridX--;
	worldX -= 30;
	return true;
}

bool Block::rotateLeft()
{
	rotationIndex--;
	if(rotationIndex < 0)
	{
		rotationIndex = shapes.size() - 1;
	}
	drawBlock();
	return true;
}

bool Block::rotateRight()
{
	rotationIndex++;
	rotationIndex = rotationIndex % shapes.size();
	drawBlock();
	return true;
}

StringArray* Block::getRotatedLeftBlockShape()
{
	int i = rotationIndex-1;
	if(i<0)
	{
		i = shapes.size() - 1;
	}
	return shapes[i];
}

StringArray* Block::getRotatedRightBlockShape()
{
	int i = (rotationIndex+1) % shapes.size();
	return shapes[i];
}