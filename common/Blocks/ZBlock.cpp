#include "ZBlock.h"

ZBlock::ZBlock()
{
	blockColour = Colours::orange;
	init();
}

void ZBlock::createBlocks()
{
	if(shapes.size() == 0)
	{
	
		/*	
			"    "
			"aa  "
			" aa "
			"    "
		*/
		StringArray* shape1 = new StringArray();
		shape1->addLines(T("    \naa  \n aa \n    ")); 

		/*
			" a  "
			"aa  "
			"a   "
			"    "
		*/
		
		StringArray* shape2 = new StringArray();
		shape2->addLines(T(" a  \naa  \na   \n    "));
		
		shapes.add(shape1);
		shapes.add(shape2);
	}
}

