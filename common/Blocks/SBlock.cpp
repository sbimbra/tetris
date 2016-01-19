#include "SBlock.h"

SBlock::SBlock()
{
	blockColour = Colours::purple;
	init();
}

void SBlock::createBlocks()
{
	if(shapes.size() == 0)
	{
	
		/*	
			"    "
			" aa "
			"aa  "
			"    "
		*/
		StringArray* shape1 = new StringArray();
		shape1->addLines(T("    \n aa \naa \n    ")); 

		/*
			"a   "
			"aa  "
			" a  "
			"    "
		*/

		StringArray* shape2 = new StringArray();
		shape2->addLines(T("a   \naa  \n a  \n    "));
		
		shapes.add(shape1);
		shapes.add(shape2);
	}
}

