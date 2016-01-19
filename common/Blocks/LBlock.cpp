#include "LBlock.h"

LBlock::LBlock()
{
	blockColour = Colours::blue;
	init();
}

void LBlock::createBlocks()
{
	if(shapes.size() == 0)
	{
	
		
		/*
			"aaa "
			"a   "
			"    "
			"    "
		*/

		StringArray* shape1 = new StringArray();
		shape1->addLines(T("aaa \na   \n    \n    "));


		/*
			"aa  "
			" a  "
			" a  "
			"    "
		*/
		StringArray* shape2 = new StringArray();
		shape2->addLines(T("aa  \n a  \n a  \n    "));
	
		
		/*
			"    "
			"  a "
			"aaa "
			"    "
		*/
		StringArray* shape3 = new StringArray();
		shape3->addLines(T("    \n  a \naaa \n    "));



		/*	
			"a   "
			"a   "
			"aa  "
			"    "
		*/
		StringArray* shape4 = new StringArray();
		shape4->addLines(T("a   \na   \naa  \n    ")); 


		
		shapes.add(shape1);
		shapes.add(shape2);
		shapes.add(shape3);
		shapes.add(shape4);
	}
}

