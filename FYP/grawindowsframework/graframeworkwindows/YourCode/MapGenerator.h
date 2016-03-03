#pragma once

#include "Object.h"
#include <iostream>
#include <fstream>
#include "KeyControl.h"
using namespace std;
class MapGenerator : public Object
{
public:
	MapGenerator(KeyControl* keyControl, int mapWidth, int mapHeight);
	~MapGenerator(void);
	void ReadFile();
	void HandleMouseClick(int button, int state, int x, int y);
	char buffer[100][100];
	char getBufferChar(int x, int y);
	void setBufferChar(int x, int y, char c);

private:
	ifstream myfile;
	
	string fileString = "./file.txt";
	int currentFile = 1;
};