
/*******************************************************************
********************************************************************
********************************************************************
********************************************************************
******************* DO NOT CHANGE THIS FILE  ***********************
********************************************************************
********************************************************************
********************************************************************
*******************************************************************/

/*
This is the entry point to the program. It creates a MyScene object and uses it to draw the window.
Do not change this code.
*/

#include "MyScene.h"

int main(int argc, char * argv[])
{
	MyScene *scene = NULL;

	// Create an instance of the castle engine
	scene = new MyScene(argc, argv, "G53GRA", (const int)800, (const int)700);
    
	// Start the engine running
	scene->Run();

	// clean up
	delete scene;
	return 0;
}