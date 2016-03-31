#pragma once

#include "Object.h"
#include <iostream>
#include <fstream>
#include "MapGenerator.h"
#include "KeyControl.h"
using namespace std;
class MapChange : public Object
{
public:
	MapChange(KeyControl* keyControl, int mapWidth, int mapHeight, char buffer[][100], MapGenerator* mapGenerator);
	~MapChange(void);
	void Draw();
	void Update(const double& deltatime);
	
	void HandleMouseClick(int button, int state, int x, int y);
private:
	int width = 0;
	int height = 0;
	void DrawForSizeOne();
	void DrawForSizeTwo();
	void DrawForSizeThree();
	//char (*bufferp)[100];
	int currentFile = 1;
	int widthUnit, heightUnit; //widthUnit is height -.-
	int xPos, zPos;
	int floorTexId, windowTexId, wallTexId, ceilingTexId, doorTexId, coffeeTableId, chairId, bedId, sofaId, toiletId, refrigeratorId, televisionId, bookCaseId, wardrobeId, kitchenTableId;
	float rowSize, colSize;
	void DrawUnitBlock(int x, int z);
	int newX, newY, blockX, blockY, optionBlockX, optionBlockY;
	//char buffer[100][100];
	int caseNumber = 0;
	bool clicked = false, optionOpen = false;
	ifstream myfile;
	KeyControl* controlKey;
	MapGenerator* generatorMap;
	void DrawOptionPage();
	int textures[100];

};

