#include "LongBlock.h"

LongBlock::LongBlock()
{
	blockColour = Colours::red;
	init();
}

void LongBlock::createBlocks()
{
	if(shapes.size() == 0)
	{

		
		/*
			"    "
			"aaaa"
			"    "
			"    "
		*/

		StringArray* shape1 = new StringArray();
		shape1->addLines(T("    \naaaa\n    \n    "));
	
		/*	
			"  a "
			"  a "
			"  a "
			"  a "
		*/
		StringArray* shape2 = new StringArray();
		shape2->addLines(T("  a \n  a \n  a \n  a "));


		shapes.add(shape1);
		shapes.add(shape2);
	}
}

