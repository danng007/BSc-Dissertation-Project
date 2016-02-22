/*
The starting point for your scene. It overides the Scene class. */

#pragma once

#include "Scene.h"
#include <iostream>
#include <fstream>
//#include "Cube.h"
class MyScene : public Scene
{

public:

	// Constructor is called when the program starts
	void HandleMouseClick(int button, int state, int x, int y);
    MyScene( int argc, char **argv, const char *title, const int windowWidth, const int windowHeight );
	// Destructor is called when the program ends
    
	~MyScene(){};
	int mapWidth, mapHeight;
	//Cube *c;
	//void HandleKey(int key, int state, int x, int y);

private:
	ifstream myfile;
	void ReadFile();
	// Initialise function is called just before the window opens
    // Use it to add all the objects to the scene that you would like to draw
	void Init();

};
