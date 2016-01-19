#include "InvLBlock.h"

InvLBlock::InvLBlock()
{
	blockColour = Colours::green;
	init();
}

void InvLBlock::createBlocks()
{
	if(shapes.size() == 0)
	{

		/*
			"    "
			"aaa "
			"  a "
			"    "
		*/

		StringArray* shape1 = new StringArray();
		shape1->addLines(T("    \naaa \n  a \n    "));

	
		/*	
			" a  "
			" a  "
			"aa  "
			"    "
		*/
		StringArray* shape2 = new StringArray();
		shape2->addLines(T(" a  \n a  \naa  \n    ")); 

		/*
			"    "
			"a   "
			"aaa "
			"    "
		*/

		StringArray* shape3 = new StringArray();
		shape3->addLines(T("    \na   \naaa \n    "));

		/*
			"aa  "
			"a   "
			"a   "
			"    "
		*/

		StringArray* shape4 = new StringArray();
		shape4->addLines(T("aa  \na   \na   \n    "));

		
		
		shapes.add(shape1);
		shapes.add(shape2);
		shapes.add(shape3);
		shapes.add(shape4);
	}
}

