#include "../../../juce.h"
#include "GameObject.h"
#include "TetrisGrid.h"
#include "Block.h"
#include "BlockManager.h"
#include "Blocks/SquareBlock.h"
#include "CollisionDetector.h"

#ifndef GAME_THREAD__H
#define GAME_THREAD__H

class GameThread : public Thread, public ChangeBroadcaster
{
	Component* drawingComp;
	int levelTimeSteps[20];
	int level;
	int width;
	int height;
	int seed;
	int linesRemoved;
	TetrisGrid* gameGrid;
	Block* currentBlock;
	Time nextUpdate;
	RelativeTime timeStep;
	Image* canvas;
	BlockManager* blockManager;
	Array<GameObject*> gameObjects;
	CollisionDetector* collision;
	CriticalSection canvasCriticalSection;
public:
	GameThread(int gameWidth, int gameHeight, Component* drawingComp);
	~GameThread();
	void update();
	void draw();
	void run();
	void setBounds(int width, int height);
	Image* getCanvas();
	void lockCanvas();
	void unlockCanvas();
	void newCanvas();
	BlockManager* getBlockManager();
	void setSeed(int seed);
	void moveBlockDown();
	void moveBlockLeft();
	void moveBlockRight();
	void rotateBlockRight();
	void rotateBlockLeft();
};

#endif