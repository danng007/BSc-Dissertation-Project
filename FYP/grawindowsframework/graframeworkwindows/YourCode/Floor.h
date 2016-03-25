#pragma once

#include "Object.h"
#include <iostream>
#include <fstream>
#include "KeyControl.h"
#include "MapGenerator.h"
#include "MapGenerator.h"
#include <glm\glm.hpp>
#include "LoadModel.h"
#include "ModelLoader.h"
using namespace std;
class Floor : public Object
{
public:
	Floor(KeyControl* keyControl, int mapWidth, int mapHeight, char buffer[][100], MapGenerator* mapGenerator);
	~Floor(void);
	void Update(const double& deltatime);

	void Draw();
	void DrawMap();
	void DrawSingleWall(int x, int y, float wallHeight, float z);
	void DrawSingleFloor(int x, int y);
	void DrawRoof(int x, int y);
	void DrawSingleWindow(int x, int y, float wallHeight, bool rowDirection);
	void DrawWall(float posX, float posY, float posZ, float poiX, float poiY, float poiZ);
	void DrawUnitWall(int x, int z, float wallHeight, float y, int xSize, int ySize);
	LoadModel coffeeTable;
	LoadModel sponBob;
	LoadModel chair;
	LoadModel  bed;
	LoadModel sofa;
	LoadModel toilet;
	LoadModel refrigerator;
	LoadModel television;
	LoadModel wardrobe;
	/*std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	*/

private:
	MapGenerator* generatorMap;
	//char(*bufferp)[100];
	bool lightChange = true;
	KeyControl* controlKey;
	float lightColour;
	int floorTexId, windowTexId, wallTexId, ceilingTexId, doorTexId, spongBobTexId, chairTexId, coffeeTableTexId, bedTexId;
	/*GLuint vbo_points, vbo_normals, vbo_uvs;*/
	int widthUnit, heightUnit; //widthUnit is height -.-
	char buffer[100][100];
	ifstream myfile;
	float wallHeight;
	int scale;
	

	
};

