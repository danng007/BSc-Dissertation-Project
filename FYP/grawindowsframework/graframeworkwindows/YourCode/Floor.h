#pragma once

#include "Object.h"
#include <iostream>
#include <fstream>
#include "KeyControl.h"
#include "MapGenerator.h"
using namespace std;
class Floor : public Object
{
public:
	Floor(KeyControl* keyControl, int mapWidth, int mapHeight, char buffer[][100]);
	~Floor(void);
	void Update(const double& deltatime);
	void ReadFile();
	void Draw();
	void DrawMap();
	void DrawSingleWall(int x, int y, float wallHeight, float z);
	void DrawSingleFloor(int x, int y);
	void DrawRoof(int x, int y);
	void DrawSingleWindow(int x, int y, float wallHeight, bool rowDirection);
	void DrawWall(float posX, float posY, float posZ, float poiX, float poiY, float poiZ);
	void DrawUnitWall(int x, int z, float wallHeight, float y, int xSize, int ySize);
private:
	char(*bufferp)[100];
	bool lightChange = true;
	KeyControl* controlKey;
	float lightColour;
	int floorTexId, windowTexId, wallTexId, ceilingTexId, doorTexId;
	
	int widthUnit, heightUnit; //widthUnit is height -.-
	char buffer[100][100];
	ifstream myfile;
	float wallHeight;
	int scale;
	

	
};

