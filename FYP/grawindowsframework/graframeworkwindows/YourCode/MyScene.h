/*
The starting point for your scene. It overides the Scene class. */

#pragma once

#include "Scene.h"
#include <iostream>


class MyScene : public Scene
{

public:

	// Constructor is called when the program starts
	void HandleMouseClick(int button, int state, int x, int y);
    MyScene( int argc, char **argv, const char *title, const int windowWidth, const int windowHeight );
	// Destructor is called when the program ends
	char buffer[100][100];
	~MyScene(){};
	int mapWidth, mapHeight;


private:

	// Initialise function is called just before the window opens
    // Use it to add all the objects to the scene that you would like to draw
	void Init();

};
