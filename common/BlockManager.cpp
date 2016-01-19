#include "BlockManager.h"

BlockManager::BlockManager(int seed, int numBlocksToPreview) : rand(0), queueLength(numBlocksToPreview)
{
	blockPreviewImage = new Image(Image::ARGB, 50, 300, true);
	setSeed(seed);
}

BlockManager::~BlockManager()
{
	delete blockPreviewImage;
	for(int i = 0; i < queueLength; i++)
	{
		delete blockQueue[i];
	}
}

void BlockManager::setSeed(int seed)
{
	for(int i = 0; i < blockQueue.size(); i++)
	{
		delete blockQueue[i];
	}
	blockQueue.clear();
	rand.setSeed(seed);
	for(int i = 0; i < queueLength; i++)
	{
		blockQueue.insert(0,getRandomBlock());
	}
	updateImage();
}

Block* BlockManager::getNextBlock()
{
	Block* returnBlock = blockQueue.getLast();
	blockQueue.removeLast();
	blockQueue.insert(0, getRandomBlock());
	updateImage();
	return returnBlock;
}


Block* BlockManager::getRandomBlock()
{
	int id = rand.nextInt(7);
	Block* newBlock = 0;
	switch(id)
	{
	case 0:
		newBlock = new SquareBlock();
		break;
	case 1:
		newBlock = new ZBlock();
		break;
	case 2:
		newBlock = new SBlock();
		break;
	case 3:
		newBlock = new TBlock();
		break;
	case 4:
		newBlock = new LBlock();
		break;
	case 5:
		newBlock = new InvLBlock();
		break;
	case 6:
		newBlock = new LongBlock();
		break;
	}
	return newBlock;
}

void BlockManager::updateImage()
{
	int width = 50;
	int height = 300;
	int numBlocks = queueLength;
	double aspect = 6;
	if(numBlocks <= 4)
	{
		// no aspect ratio correction needed
		Graphics g(*blockPreviewImage);
		g.fillAll(Colours::white);
		for(int i = 0; i < numBlocks; i++)
		{
			g.drawImageWithin(blockQueue[i]->getImage(), 0, (numBlocks-i)*60,50,50,RectanglePlacement::xLeft,false);
		}
		sendChangeMessage(this);
	}
	
}

Image* BlockManager::getBlockPreviewImage()
{
	return blockPreviewImage;
}