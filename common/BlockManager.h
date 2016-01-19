#ifndef BLOCK_MANAGER__H
#define BLOCK_MANAGER__H

#include "../../../juce.h"
#include "Block.h"
#include "Blocks/SquareBlock.h"
#include "Blocks/ZBlock.h"
#include "Blocks/SBlock.h"
#include "Blocks/TBlock.h"
#include "Blocks/LBlock.h"
#include "Blocks/InvLBlock.h"
#include "Blocks/LongBlock.h"

class BlockManager : public ChangeBroadcaster
{
	Image* blockPreviewImage;
	Random rand;
	Array<Block*> blockQueue;
	int queueLength;
	Block* getRandomBlock();
	void updateImage();
public:
	BlockManager(int seed, int numBlocksToPreview);
	~BlockManager();
	void setSeed(int seed);
	Block* getNextBlock();
	Image* getBlockPreviewImage();	
};

#endif