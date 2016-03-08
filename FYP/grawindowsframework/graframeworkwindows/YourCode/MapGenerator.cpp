#include "MapGenerator.h"
#include "Scene.h"

//#include "MyScene.h"
#define SIZE 50.0f
/*
Room size:
1 block as 2.5m2
file: 9*8 (11*10 with walls) -> 180m2
file2: 6*5 (8 * 7 with walls)-> 75m2
file3: 12*8 (14 * 10 with walls)-> 240m2
reference: uk regular house size...
*/

MapGenerator::MapGenerator(KeyControl* keyControl, int mapWidth, int mapHeight)
{
	
	ReadFile();

}
MapGenerator::~MapGenerator(void)
{
	glDisable(GL_TEXTURE_2D);
}

void MapGenerator::ReadFile()
{
	for (int i = 0; i < lastj; i++)
	{
		for (int m = 0; m < lastk; m++)
		{
			buffer[i][m] = 'a';
		}
	}
	int j = 0, k = 0;
	int length;
	myfile.open(fileString);      // open input file  
	string s;
	if (myfile.good()) {
		while (getline(myfile, s)) {
			for (int i = 0; i < s.size(); i++) {
				buffer[j][k] = s[i];
				cout << buffer[j][k];
				k++;
			}
			lastk = k;
			mapHeight = k;
			k = 0;
			lastj = j;
			j++;
			cout << endl;
		}
	}
	mapWidth = j;
	cout << "mapGenerator read finish\n";
	myfile.close();
}

void MapGenerator::HandleMouseClick(int button, int state, int x, int y)
{
	if (Scene::GetGameStart() && x <= 150 && y <= 136 && state == 1 && currentFile != 1)
	{
		fileString = "./file.txt";
		currentFile = 1;
		ReadFile();
	}
	if (Scene::GetGameStart() && x > 150 && x <= 300 && y <= 136 && state == 1 && currentFile != 2)
	{
		fileString = "./file2.txt";
		currentFile = 2;
		ReadFile();
	}

}

char MapGenerator::GetBufferChar(int x, int y)
{
	return buffer[x][y];
}

void MapGenerator::SetBufferChar(int x, int y, char c)
{
	buffer[x][y] = c;
}

int MapGenerator::GetCurrentFileNumber()
{
	return currentFile;
}
int MapGenerator::GetMapHeight()
{
	return mapHeight;
}
int MapGenerator::GetMapWidth()
{
	return mapWidth;
}