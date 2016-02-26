#pragma once

#include "Object.h"
#include <iostream>
#include <fstream>
#include "KeyControl.h"
using namespace std;
class MapChange : public Object
{
public:
	MapChange(KeyControl* keyControl, int mapWidth, int mapHeight);
	~MapChange(void);
	void Draw();
	void Update(const double& deltatime);
	void ReadFile();
	void HandleMouseClick(int button, int state, int x, int y);
private:
	int widthUnit, heightUnit; //widthUnit is height -.-
	int xPos, zPos;
	int floorTexId, windowTexId, wallTexId, ceilingTexId, doorTexId;
	float rowSize, colSize;
	void DrawUnitBlock(int x, int z);
	int newX, newY, blockX, blockY;
	char buffer[100][100];
	bool clicked = false, optionOpen = false;
	ifstream myfile;
	KeyControl* controlKey;
	void DrawOptionPage();
	int textures[100];

};

