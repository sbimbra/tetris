#include "TBlock.h"

TBlock::TBlock()
{
	blockColour = Colours::yellow;
	init();
}

void TBlock::createBlocks()
{
	if(shapes.size() == 0)
	{

		/*
			"    "
			"aaa "
			" a  "
			"    "
		*/

		StringArray* shape1 = new StringArray();
		shape1->addLines(T("    \naaa \n a  \n    "));

		/*
			" a  "
			"aa  "
			" a  "
			"    "
		*/
		StringArray* shape2 = new StringArray();
		shape2->addLines(T(" a  \naa  \n a  \n    "));

	
		/*	
			" a  "
			"aaa "
			"    "
			"    "
		*/
		StringArray* shape3 = new StringArray();
		shape3->addLines(T(" a  \naaa \n    \n    "));

		
		/*
			" a  "
			" aa "
			" a  "
			"    "
		*/

		StringArray* shape4 = new StringArray();
		shape4->addLines(T(" a  \n aa \n a  \n    "));

		shapes.add(shape1);
		shapes.add(shape2);
		shapes.add(shape3);
		shapes.add(shape4);
	}
}

