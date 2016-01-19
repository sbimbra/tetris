#include "TetrisGrid.h"

TetrisGrid::TetrisGrid(int canvasWidth, int canvasHeight)
{
	myImage = 0;
	
	// We need to initialize the game grid with spaces for empty cells
	// and some character for filled cells (maybe different letters are different
	// colors, just for variety
	
	
	for(int i = 0; i < GRID_HEIGHT; i++)
	{
		String* buffer = new String();
		for(int j = 0; j < GRID_WIDTH; j++)
		{
			*buffer += ' ';
		}
		grid.add(buffer);
	}
	
	outerRect = Rectangle(canvasWidth, canvasHeight);
	cellWidth = 30;
	cellHeight = 30;
	drawGrid();
}

TetrisGrid::~TetrisGrid()
{
	if(myImage != 0)
	{
		delete myImage;
	}
}

// drawGrid iterates over all the grid cells, drawing blocks where possible.
void TetrisGrid::drawGrid()
{
	lockImage();
	if(myImage != 0)
	{
		delete myImage;
	}
	myImage = new Image(Image::ARGB,outerRect.getWidth(), outerRect.getHeight(),false);
	Graphics g(*myImage);
	g.fillAll(Colours::darkgrey);

	g.setOrigin(5,0); // move the origin to (5,0), so we have a border on the edges

	int x = 0;
	int y = 0;

	for(int i = 0; i < GRID_HEIGHT; i++)
	{
		x = 0;
		for(int j = 0; j < GRID_WIDTH; j++)
		{
			Colour c(Colours::white);
			jassert(grid[i]->length() == 10);
			if((*(grid[i]))[j] == 'a')
			{
				c = Colours::darkgrey;
			}
			g.setColour(c);
			g.fillRect(x,y,cellWidth,cellHeight);
			x += cellWidth;	
		}
		y += cellHeight;
	}
	unlockImage();
	updatedImage = true;
}

void TetrisGrid::update()
{
}

int TetrisGrid::getX()
{
	return 0;
}
int TetrisGrid::getY()
{
	return 0;
}

bool TetrisGrid::redrawNeeded()
{
	return true;
}

OwnedArray<String,CriticalSection>* TetrisGrid::getGrid()
{
	return &grid;
}

void TetrisGrid::addBlockToStack(Block* blockToAdd)
{
	int offsetX = blockToAdd->getGridX();
	int offsetY = blockToAdd->getGridY();
	StringArray* blockShape = blockToAdd->getBlockShape();
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			tchar cell = (*blockShape)[i][j];
			if(cell == 'a')
			{
				(*(grid[offsetY+i]))[offsetX+j] = cell; 
			}
		}
	}
	drawGrid();
}

int TetrisGrid::removeLines()
{
	int removed = 0;
	for(int i = 0; i < GRID_HEIGHT; i++)
	{
		bool removeThisRow = true;
		for(int j = 0; j < GRID_WIDTH; j++)
		{
			if(((*(grid[i]))[j]) == ' ')
			{
				removeThisRow = false;
				break;
			}
		}
		if(removeThisRow)
		{
			grid.remove(i);
			String* emptyLine = new String(T("          "));
			grid.insert(0, emptyLine);
			removed++;
			if(removed == 4)
			{
				break;
			}
		}
	}
	drawGrid();
	return removed;
}