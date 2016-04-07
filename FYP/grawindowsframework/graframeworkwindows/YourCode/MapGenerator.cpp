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

MapGenerator::MapGenerator(KeyControl* keyControl, int mapWidth, int mapHeight, Camera* camera)
{
	currentCamera = camera;
	fileString = "./file.txt";
	ReadFile(buffer1, &mapWidth1, &mapHeight1);
	fileString = "./file2.txt";
	ReadFile(buffer2, &mapWidth2, &mapHeight2);
	fileString = "./file3.txt";
	ReadFile(buffer3, &mapWidth3, &mapHeight3);
	currentCamera->GetBuffer(buffer1);
}
MapGenerator::~MapGenerator(void)
{
	glDisable(GL_TEXTURE_2D);
}

void MapGenerator::ReadFile(char buffer[][100], int* mapWidth, int* mapHeight)
{
	for (int i = 0; i < lastj; i++)
	{
		for (int m = 0; m < lastk; m++)
		{
			buffer[i][m] = '0';
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
			*mapHeight = k;
			k = 0;
			lastj = j;
			j++;
			cout << endl;
		}
	}
	*mapWidth = j;
	cout << "mapGenerator read finish\n";
	myfile.close();
}

void MapGenerator::HandleMouseClick(int button, int state, int x, int y)
{
	if (Scene::GetGameStart() && x <= 150 && y <= 120 && state == 1 && currentFile != 1)
	{ 
		
		currentFile = 1;
		currentCamera->GetBuffer(buffer1);

	}
	if (Scene::GetGameStart() && x > 150 && x <= 300 && y <= 100 && state == 1 && currentFile != 2)
	{
		
		currentFile = 2;
		currentCamera->GetBuffer(buffer2);
	
	}
	if (Scene::GetGameStart() && x > 300 && x <= 450 && y <= 100 && state == 1 && currentFile != 3)
	{
		
		currentFile = 3;
		currentCamera->GetBuffer(buffer3);
		
	}
}

char MapGenerator::GetBufferChar(int x, int y)
{
	char c;
	switch (currentFile)
	{
	case 1:
		c = buffer1[x][y];
		break;
	case 2:
		c = buffer2[x][y];
		break;
	case 3:
		c = buffer3[x][y];
		break;
	default:
		break;
	}
	return c;
}

void MapGenerator::SetBufferChar(int x, int y, char c)
{
	switch (currentFile)
	{
	case 1:
		 buffer1[x][y] = c;
		break;
	case 2:
		 buffer2[x][y] = c;
		 break;
	case 3:
		 buffer3[x][y] = c;
		break;
	default:
		break;
	}
}

int MapGenerator::GetCurrentFileNumber()
{
	return currentFile;
}
int MapGenerator::GetMapHeight()
{
	switch (currentFile)
	{
	case 1:
		return mapHeight1;
		break;
	case 2:
		return mapHeight2;
		break;
	case 3:
		return mapHeight3;
		break;
	default:
		break;
	}
}
int MapGenerator::GetMapWidth()
{
	switch (currentFile)
	{
	case 1:
		return mapWidth1;
		break;
	case 2:
		return mapWidth2;
		break;
	case 3:
		return mapWidth3;
		break;
	default:
		break;
	}
}
char(*MapGenerator::GetBuffer())[100]
{
	
	switch (currentFile)
	{
	case 1:
		return buffer1;
		break;
	case 2:
		return buffer2;
		break;
	case 3:
		return buffer3;
		break;
	default:
		break;
	}
}