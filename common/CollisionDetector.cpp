#include "CollisionDetector.h"

bool CollisionDetector::checkMoveLeft()
{
	int offsetX = currentBlock->getGridX() - 1; // -1 because we're seeing if there's a collision there
	int offsetY = currentBlock->getGridY();
	StringArray* blockShape = currentBlock->getBlockShape();
	OwnedArray<String,CriticalSection>* gameGrid = grid->getGrid();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if((*blockShape)[i][j] == 'a')
			{
				if((j + offsetX) < 0 || (*(*gameGrid)[i+offsetY])[j+offsetX] == 'a')
				{
					// collision, can't do the move
					return false;
				}
				else
				{
					// break because we don't need to check the ones farther to the right.
					// those ones can't collide, because if they did, then the pre-move state
					// was invalid, which is impossible
					break;
				}
			}
		}
	}
	return true;
}

bool CollisionDetector::checkMoveRight()
{
	int offsetX = currentBlock->getGridX() + 1; // -1 because we're seeing if there's a collision there
	int offsetY = currentBlock->getGridY();
	StringArray* blockShape = currentBlock->getBlockShape();
	OwnedArray<String,CriticalSection>* gameGrid = grid->getGrid();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 3; j >= 0; j--) // we need to start from the right or else the early break isn't valid
		{
			if((*blockShape)[i][j] == 'a')
			{
				if((j + offsetX) > 9 || (*(*gameGrid)[i+offsetY])[j+offsetX] == 'a')
				{
					// collision, can't do the move
					return false;
				}
				else
				{
					// break because we don't need to check the ones farther to the right.
					// those ones can't collide, because if they did, then the pre-move state
					// was invalid, which is impossible
					break;
				}
			}
		}
	}
	return true;
}

bool CollisionDetector::checkMoveDown()
{
	int offsetX = currentBlock->getGridX();
	int offsetY = currentBlock->getGridY() + 1; // +1 means down in our coordinate system
	StringArray* blockShape = currentBlock->getBlockShape();
	OwnedArray<String,CriticalSection>* gameGrid = grid->getGrid();
	for(int i = 3; i >= 0; i--) // start from the bottom
	{
		for(int j = 3; j >= 0; j--)
		{
			if((*blockShape)[i][j] == 'a')
			{
				if((i+offsetY) > 19 || (*(*gameGrid)[i+offsetY])[j+offsetX] == 'a')
				{
					// collision, can't do the move
					return false;
				}
			}
		}
	}
	return true;
}

bool CollisionDetector::checkRotateLeft()
{
	int offsetX = currentBlock->getGridX();
	int offsetY = currentBlock->getGridY();
	StringArray* blockShape = currentBlock->getRotatedLeftBlockShape();
	OwnedArray<String,CriticalSection>* gameGrid = grid->getGrid();
	for(int i = 0; i < 4; i++) // start from the bottom
	{
		for(int j = 0; j < 4; j++)
		{
			if((*blockShape)[i][j] == 'a')
			{
				if((i+offsetY) > 19 || (j+offsetX < 0) || (j+offsetX > 9) || (*(*gameGrid)[i+offsetY])[j+offsetX] == 'a')
				{
					// collision, can't do the move
					return false;
				}
			}
		}
	}
	return true;
}

bool CollisionDetector::checkRotateRight()
{
	int offsetX = currentBlock->getGridX();
	int offsetY = currentBlock->getGridY();
	StringArray* blockShape = currentBlock->getRotatedRightBlockShape();
	OwnedArray<String,CriticalSection>* gameGrid = grid->getGrid();
	for(int i = 0; i < 4; i++) // start from the bottom
	{
		for(int j = 0; j < 4; j++)
		{
			if((*blockShape)[i][j] == 'a')
			{
				if((i+offsetY) > 19 || (j+offsetX < 0) || (j+offsetX > 9) || (*(*gameGrid)[i+offsetY])[j+offsetX] == 'a')
				{
					// collision, can't do the move
					return false;
				}
			}
		}
	}
	return true;
}

bool CollisionDetector::checkInPlace()
{
	int offsetX = currentBlock->getGridX();
	int offsetY = currentBlock->getGridY();
	StringArray* blockShape = currentBlock->getBlockShape();
	OwnedArray<String,CriticalSection>* gameGrid = grid->getGrid();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if((*blockShape)[i][j] == 'a')
			{
				if((i+offsetY) > 19 || (j+offsetX < 0) || (j+offsetX > 9) || (*(*gameGrid)[i+offsetY])[j+offsetX] == 'a')
				{
					// collision, can't do the move
					return false;
				}
			}
		}
	}
	return true;

}