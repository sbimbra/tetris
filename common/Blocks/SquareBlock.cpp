#include "SquareBlock.h"

SquareBlock::SquareBlock()
{
	blockColour = Colours::grey;
	init();
}

void SquareBlock::createBlocks()
{
	if(shapes.size() == 0)
	{
	
		/*	
			"aa  "
			"aa  "
			"    "
			"    "
		*/
		StringArray* shape = new StringArray();
		shape->addLines(T("aa  \naa  \n    \n    ")); 
		shapes.add(shape);
	}
}

