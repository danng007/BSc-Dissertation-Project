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
	char GetBufferChar(int x, int y);
	void SetBufferChar(int x, int y, char c);
	int GetCurrentFileNumber();
	int GetMapWidth();
	int GetMapHeight();
private:
	ifstream myfile;
	int lastj = 0, lastk = 0, mapWidth = 0, mapHeight = 0;
	string fileString = "./file.txt";
	int currentFile = 1;
};