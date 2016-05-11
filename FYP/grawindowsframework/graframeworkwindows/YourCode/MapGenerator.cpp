#include "MapGenerator.h"
#include "Scene.h"


#define SIZE 50.0f
/*
Room size:
file: 9*8 (11*10 with walls)
file2: 6*5 (8 * 7 with walls)
file3: 12*8 (14 * 10 with walls)
*/

MapGenerator::MapGenerator( int mapWidth, int mapHeight, Camera* camera)
{
	currentCamera = camera;
	fileString = "./mapFiles/file.txt";
	ReadFile(buffer1, &mapWidth1, &mapHeight1);
	fileString = "./mapFiles/file2.txt";
	ReadFile(buffer2, &mapWidth2, &mapHeight2);
	fileString = "./mapFiles/file3.txt";
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
				k++;
			}
			lastk = k;
			*mapHeight = k;
			k = 0;
			lastj = j;
			j++;
		}
	}
	*mapWidth = j;
	myfile.close();
}

void MapGenerator::HandleMouseClick(int button, int state, int x, int y) //Detect based on mouse coordinate
{
	if (Scene::GetGameStart() && x <= 150 && y <= 120 && state == 1 && currentFile != 1)
	{ 
		currentFile = 1;
		currentCamera->GetBuffer(buffer1); //Each time file changed, pass the different pointer to camera. Update the collision detection envirionment.
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
	if (Scene::GetGameStart() && x > 450 && x < 800 && y <= 100 && state == 1)
	{
		FileOutPut();
	}
}

void MapGenerator::FileOutPut()
{
	switch (currentFile)
	{
	case 1:
		ofile.open("./mapFiles/outFile1.txt");
		FileOut(1, mapWidth1, mapHeight1);
		ofile.close();
		break;
	case 2:
		ofile.open("./mapFiles/outFile2.txt");
		FileOut(2, mapWidth2, mapHeight2);
		ofile.close();
		break;
	case 3:
		ofile.open("./mapFiles/outFile3.txt");
		FileOut(3, mapWidth3, mapHeight3);
		ofile.close();
		break;
	default:
		break;
	}
}

void MapGenerator::FileOut(int file, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			switch (file)
			{

			case 1:
				ofile << buffer1[i][j];
				break;
			case 2:
				ofile << buffer2[i][j];
				break;
			case 3:
				ofile << buffer3[i][j];
				break;
				default:
				break;
			}
		}
		ofile << "\n";
	}
}

char MapGenerator::GetBufferChar(int x, int y) //map string get function
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

void MapGenerator::SetBufferChar(int x, int y, char c) //map string set function
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

int MapGenerator::GetCurrentFileNumber() //Return the reference number of current map
{
	return currentFile;
}

int MapGenerator::GetMapHeight() //Return the height of current map
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
int MapGenerator::GetMapWidth() //Return the width of current map
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
char(*MapGenerator::GetBuffer())[100] // Get the whole map string
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