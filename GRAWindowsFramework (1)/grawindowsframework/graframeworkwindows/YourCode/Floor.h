#pragma once

#include "Object.h"
#include <iostream>
#include <fstream>
#include "KeyControl.h"
using namespace std;
class Floor : public Object
{
public:
	Floor(KeyControl* keyControl);
	~Floor(void);
	void Update(const double& deltatime);
	void ReadFile();
	void Draw();
	void DrawMap();
	void DrawSingleWall(int x, int y, float wallHeight, float z);
	void DrawSingleFloor(int x, int y);
	void DrawRoof(int x, int y);
	void DrawSingleWindow(int x, int y, float wallHeight);
	void DrawWall(float posX, float posY, float posZ, float poiX, float poiY, float poiZ);
private:
	bool lightChange = true;
	KeyControl* controlKey;
	float lightColour;
	int floorTexId, windowTexId, wallTexId, ceilingTexId, doorTexId;
	static const int widthUnit = 8, heightUnit = 10; //widthUnit is height -.-
	char buffer[widthUnit][heightUnit];
	ifstream myfile;
	float wallHeight;
	int scale;

	
};

