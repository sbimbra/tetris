#ifndef COLLISION_DETECTOR__H
#define COLLISION_DETECTOR__H

#include "../../../juce.h"
#include "Block.h"
#include "TetrisGrid.h"

class CollisionDetector
{
	TetrisGrid* grid;
	Block* currentBlock;
public:
	CollisionDetector(TetrisGrid* theGrid) : grid(theGrid)
	{
	}

	void setBlock(Block* newBlock)
	{
		currentBlock = newBlock;
	}

	bool checkInPlace();
	bool checkMoveLeft();
	bool checkMoveRight();
	bool checkMoveDown();
	bool checkRotateRight();
	bool checkRotateLeft();
};

#endif