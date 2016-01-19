#include "GameThread.h"

GameThread::GameThread(int gameWidth, int gameHeight, Component* drawingComp) : Thread(T("Main game"))
{
	levelTimeSteps[0] = 1100;
	levelTimeSteps[1] = 1000;
	levelTimeSteps[2] = 900;
	levelTimeSteps[3] = 800;
	levelTimeSteps[4] = 690;
	levelTimeSteps[5] = 610;
	levelTimeSteps[6] = 535;
	levelTimeSteps[7] = 465;
	levelTimeSteps[8] = 400;
	levelTimeSteps[9] = 340;
	levelTimeSteps[10] = 290;
	levelTimeSteps[11] = 250;
	levelTimeSteps[12] = 215;
	levelTimeSteps[13] = 180;
	levelTimeSteps[14] = 150;
	levelTimeSteps[15] = 120;
	levelTimeSteps[16] = 95;
	levelTimeSteps[17] = 75;
	levelTimeSteps[18] = 60;
	levelTimeSteps[19] = 50;

	linesRemoved = 0;
	timeStep = timeStep.milliseconds(levelTimeSteps[0]);
	width = gameWidth;
	height = gameHeight;
	canvas = 0;
	this->drawingComp = drawingComp;	
	newCanvas();
	gameGrid = new TetrisGrid(gameWidth, gameHeight);
	collision = new CollisionDetector(gameGrid);
	gameObjects.add(gameGrid);
	blockManager = new BlockManager(seed,4);
}

GameThread::~GameThread()
{
	stopThread(1000);
	canvasCriticalSection.enter();
	if(canvas)
	{
		deleteAndZero(canvas);
	}
	canvasCriticalSection.exit();

	for(int i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}

	delete blockManager;

	delete collision;
}

void GameThread::update()
{
	Time current = Time::getCurrentTime();
	if(current < nextUpdate)
	{
		return;
	}
	
	newCanvas();
	
	nextUpdate = nextUpdate + timeStep;

	for(int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}

	moveBlockDown();
}

void GameThread::draw()
{
	canvasCriticalSection.enter();
	Graphics g(*canvas);
	for(int i = 0; i < gameObjects.size(); i++)
	{
		if(gameObjects[i]->redrawNeeded())
		{
			gameObjects[i]->lockImage();
			g.drawImageAt(gameObjects[i]->getImage(), gameObjects[i]->getX(), gameObjects[i]->getY());
			gameObjects[i]->unlockImage();
		}
	}
	canvasCriticalSection.exit();
	MessageManagerLock* lock = new MessageManagerLock();
	drawingComp->repaint();
	delete lock;
}

void GameThread::run()
{
	currentBlock = blockManager->getNextBlock();
	collision->setBlock(currentBlock);
	gameObjects.add(currentBlock);
	nextUpdate = Time::getCurrentTime() + RelativeTime(1);
	while(!threadShouldExit())
	{
		update();
		draw();
		wait(20); // just so we don't run at 100% cpu
	}
}

void GameThread::setBounds(int width, int height)
{
	this->width = width;
	this->height = height;
	newCanvas();

	for(int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->resized(width,height);
	}
}

Image* GameThread::getCanvas()
{
	return canvas;
}

void GameThread::lockCanvas()
{
	canvasCriticalSection.enter();
}

void GameThread::unlockCanvas()
{
	canvasCriticalSection.exit();
}

void GameThread::newCanvas()
{
	canvasCriticalSection.enter();
	if(canvas != 0)
	{
		delete canvas;
	}
	canvas = new Image(Image::ARGB, width, height, true);
	canvasCriticalSection.exit();
}

void GameThread::moveBlockDown()
{
	nextUpdate = Time::getCurrentTime() + timeStep;
	if(collision->checkMoveDown())
	{
		currentBlock->moveDown();
	}
	else
	{
		gameGrid->addBlockToStack(currentBlock);
		linesRemoved += gameGrid->removeLines();
		gameObjects.removeValue(currentBlock);
		delete currentBlock;
		currentBlock = blockManager->getNextBlock();
		gameObjects.add(currentBlock);
		collision->setBlock(currentBlock);
		timeStep = timeStep.milliseconds(levelTimeSteps[jmin(linesRemoved/5,19)]);
		if(!collision->checkInPlace())
		{
			signalThreadShouldExit();
		}

		sendChangeMessage((void*)linesRemoved);
	}
}

void GameThread::moveBlockLeft()
{
	if(collision->checkMoveLeft())
	{
		currentBlock->moveLeft();
	}
}
void GameThread::moveBlockRight()
{
	if(collision->checkMoveRight())
	{
		currentBlock->moveRight();
	}
}
void GameThread::rotateBlockRight()
{
	if(collision->checkRotateRight())
	{
		currentBlock->rotateRight();
	}
}
void GameThread::rotateBlockLeft()
{
	if(collision->checkRotateLeft())
	{
		currentBlock->rotateLeft();
	}
}

void GameThread::setSeed(int seed)
{
	blockManager->setSeed(seed);
}

BlockManager* GameThread::getBlockManager()
{
	return blockManager;
}