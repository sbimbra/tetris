#include "GameObject.h"
#include "Block.h"
#ifndef TETRIS_GRID__H
#define TETRIS_GRID__H

class TetrisGrid : public GameObject
{
	bool updatedImage;
	Rectangle outerRect;
	Rectangle innerRect;
	int cellWidth;
	int cellHeight;
	OwnedArray<String,CriticalSection> grid;
public:
	static const int GRID_WIDTH = 10;
	static const int GRID_HEIGHT = 20;
	TetrisGrid(int canvasWidth, int canvasHeight);
	~TetrisGrid();
	void drawGrid();
	void update();
	int getX();
	int getY();
	bool redrawNeeded();
	OwnedArray<String,CriticalSection>* getGrid(); 
	void addBlockToStack(Block* blockToAdd);
	int removeLines();
};

#endif