#include "MapGenerator.h"
#include "Scene.h"

//#include "MyScene.h"
#define SIZE 50.0f
/*
Room size:
1 block as 2.5m2
file: 9*8 -> 180m2
file2: 6*5 -> 75m2
file3: 12*8 -> 240m2
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
			k = 0;
			j++;
			cout << endl;
		}
	}
	cout << "mapGenerator read finish\n";
	myfile.close();
}

void MapGenerator::HandleMouseClick(int button, int state, int x, int y)
{
	if (Scene::GetGameStart() && x <= 100 && y <= 100 && state == 1 && currentFile != 2)
	{
		fileString = "./file2.txt";
		currentFile = 2;
		ReadFile();
	}

}

char MapGenerator::getBufferChar(int x, int y)
{
	return buffer[x][y];
}

void MapGenerator::setBufferChar(int x, int y, char c)
{
	buffer[x][y] = c;
}