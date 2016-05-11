#pragma once

#include "Object.h"
#include <iostream>
#include <fstream>

using namespace std;
class MapGenerator : public Object
{
public:
	MapGenerator( int mapWidth, int mapHeight, Camera* camera);
	~MapGenerator(void);
	void ReadFile(char buffer[][100], int* mapWidth, int* mapHeight);
	void HandleMouseClick(int button, int state, int x, int y);
	char buffer1[100][100], buffer2[100][100], buffer3[100][100];
	Camera* currentCamera;
	char GetBufferChar(int x, int y);
	void SetBufferChar(int x, int y, char c);
	int GetCurrentFileNumber();
	int GetMapWidth();
	int GetMapHeight();
	char (*GetBuffer())[100];
	int currentFile = 1;
private:
	void FileOut(int file, int width, int height);
	void FileOutPut();
	ofstream ofile;
	ifstream myfile;
	int lastj = 0, lastk = 0, mapWidth1, mapWidth2, mapWidth3, mapHeight1, mapHeight2, mapHeight3;
	string fileString = "./file.txt";

};