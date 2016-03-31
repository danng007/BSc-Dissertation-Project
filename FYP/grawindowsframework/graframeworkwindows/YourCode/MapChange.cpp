#include "MapChange.h"
#include "Scene.h"

//#include "MyScene.h"
#define SIZE 50.0f
MapChange::MapChange(KeyControl* keyControl, int mapWidth, int mapHeight, char buffer[][100], MapGenerator* mapGenerator)
{
	//bufferp = buffer;
	newX = 100, newY = 100;
	blockX = 100, blockY = 100;
	optionBlockX = 100, optionBlockY = 100;
	
	controlKey = keyControl;
	generatorMap = mapGenerator;
	widthUnit = generatorMap->GetMapWidth();
	heightUnit = generatorMap->GetMapHeight();
	//ReadFile();
	xPos = 0;
	zPos = 0;
	width = Scene::GetWindowWidth();
	height = Scene::GetWindowHeight();
	printf("colsize = %f,  rowSize = %f \n", colSize, rowSize);
	glEnable(GL_TEXTURE_2D);
	wallTexId = Scene::GetTexture("./Resources/textures/wallPaper.bmp");
	windowTexId = Scene::GetTexture("./Resources/textures/window.bmp");
	floorTexId = Scene::GetTexture("./Resources/textures/floor.bmp");
	ceilingTexId = Scene::GetTexture("./Resources/textures/ceiling.bmp");
	doorTexId = Scene::GetTexture("./Resources/textures/door.bmp");
	coffeeTableId = Scene::GetTexture("./Resources/textures/Table.bmp");
	chairId = Scene::GetTexture("./Resources/textures/Chair.bmp");
	bedId = Scene::GetTexture("./Resources/textures/Bed.bmp");
	sofaId = Scene::GetTexture("./Resources/textures/Sofa.bmp");
	toiletId = Scene::GetTexture("./Resources/textures/Toilet.bmp");
	refrigeratorId = Scene::GetTexture("./Resources/textures/Refrigerator.bmp");
	televisionId = Scene::GetTexture("./Resources/textures/TV.bmp");
	bookCaseId = Scene::GetTexture("./Resources/textures/BookCase.bmp");
	wardrobeId = Scene::GetTexture("./Resources/textures/Wardrobe.bmp");
	kitchenTableId = Scene::GetTexture("./Resources/textures/KitchenTablee.bmp");
	

	textures[0] = floorTexId;
	textures[1] = wallTexId;
	textures[2] = windowTexId;
	textures[3] = doorTexId;
	textures[4] = sofaId;
	textures[5] = bedId;
	textures[6] = chairId;
	textures[7] = coffeeTableId;
	textures[8] = toiletId;
	textures[9] = refrigeratorId;
	textures[10] = televisionId;
	textures[11] = wardrobeId;
	textures[12] = bookCaseId;
	textures[13] = kitchenTableId;
	printf("text 13: %d\n",textures[13]);
}

MapChange::~MapChange(void)
{
	glDisable(GL_TEXTURE_2D);
}


void MapChange::Draw()
{
	if (Scene::GetGameStart())
	{
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		
		glOrtho(-width / 2, width / 2, -height / 2, height / 2, 1.0, 1000.0); //change to image view position
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		currentFile = generatorMap->GetCurrentFileNumber();
		widthUnit = generatorMap->GetMapWidth();
		heightUnit = generatorMap->GetMapHeight();

		switch (currentFile)
		{
		case 1:
			
			DrawForSizeOne();
			break;
		case 2:
		
			DrawForSizeTwo();
			break;
		case 3:
			DrawForSizeThree();
			break;
		default:
			break;
		}
		
		
		/*
		Draw the size change function button,
		First quads is file1, second is file2, third is file3
		*/
		
		glPopMatrix();
		glPushMatrix();
		if (optionOpen)
		{
			glTranslatef(-480.0f, -420.0f, 0.0f);	
		}
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glEnable(GL_LIGHTING);
		glMatrixMode(GL_MODELVIEW);

	}
	
}
void MapChange::Update(const double& deltatime)
{
	
	
}
void MapChange::HandleMouseClick(int button, int state, int x, int y)
{
	if (Scene::GetGameStart())
	{

		if (state == 1 ) // state == 1 means only reaction when mouse up fileNum == 1 means the size is9 * 8
		{
			
				blockX = x / (int)colSize + 1;
				if (generatorMap->GetCurrentFileNumber() == 1 || generatorMap->GetCurrentFileNumber() == 3)
				{
					blockY = heightUnit - (y - 10) / (int)rowSize; //the file 1 and file 3 have 10 pixels' calculation problem. here is dirty solution.
				}
				else
				{
					blockY = heightUnit - y / (int)rowSize; // the whole file matrix rotate 90 degree in order to fits the screen more suitable, so the coordinate should be modified
				}
				
				printf(" rowsize = %d, blockY = %d, bufferp[%d][%d] is %c \n", (int)rowSize,blockY,x, y, generatorMap->GetBufferChar(blockX, blockY));
				if (optionOpen && x >= 80 && x <= 725 && y >= 360  && y <= 635)
				{
				
					int optionNum = 0;
					if (y <= 490)
					{
						optionNum = (x - 70) / 93; // choosing level one
					}
					else
					{
						optionNum = (x - 70) / 93 + 7;
					}
					
					printf("test = %d\n", optionNum);
					generatorMap->SetBufferChar(newX, newY, optionNum + 97);
					optionOpen = false;
				}
				else
				{
					if (!optionOpen && blockX >= 1 && blockX <= widthUnit - 2 && blockY >= 1 && blockY <= heightUnit - 2)
					{
						printf("Outside option choose\n");
						newX = blockX;
						newY = blockY;
						optionOpen = true;
					}
				}
		}
		
	}
}

void MapChange::DrawUnitBlock(int x, int z)
{
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(x * colSize, z *rowSize, -10.0f);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f((x + 1) * colSize, z * rowSize, -10.0f);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f((x + 1) * colSize, (z + 1) *rowSize, -10.0f);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x* colSize, (z + 1)* rowSize, -10.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}
void MapChange::DrawForSizeOne()
{
	

	colSize = Scene::GetWindowWidth() / 10; // heng Full
	rowSize = Scene::GetWindowHeight() / 13; // shu  Give s size blank blocks at top
	glTranslatef(-480, -403, 0);
	
	for (int z = zPos; z < heightUnit + zPos; z++) // add modify value to X and Y, move 2D image to the middle of window
	{
		for (int x = xPos; x < widthUnit + xPos; x++)
		{
			caseNumber = (int)(generatorMap->GetBufferChar(x - xPos, z - zPos)) - 97;
			if (caseNumber >= 0 && caseNumber <= 13)
			{
				//printf("caseNumber = %d \n",caseNumber);
				glBindTexture(GL_TEXTURE_2D, textures[caseNumber]);
				DrawUnitBlock(x, z);
			}
	
		}
	}
	if (optionOpen)
	{
		glBindTexture(GL_TEXTURE_2D, ceilingTexId);
		DrawUnitBlock(newX, newY);
		glPushMatrix();
		glTranslatef(0.0f, 3.0f, 0.0f);
		DrawOptionPage();
		glPopMatrix();
	}

	glTranslatef(80.0f, 635.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS); // Full horizontal Quads
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(800.0f, 0.0f, -10.0f);
	glVertex3f(800.0f, 20.0f, -10.0f);
	glVertex3f(0.0f, 20.0f, -10.0f);
	glEnd();
	glTranslatef(0.0f, 20.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS); // first file
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(150.0f, 0.0f, -10.0f);
	glVertex3f(150.0f, 100.0f, -10.0f);
	glVertex3f(0.0f, 100.0f, -10.0f);
	glEnd();
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS); //second file
	glVertex3f(150.0f, 0.0f, -10.0f);
	glVertex3f(300.0f, 0.0f, -10.0f);
	glVertex3f(300.0f, 100.0f, -10.0f);
	glVertex3f(150.0f, 100.0f, -10.0f);
	glEnd();
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS); //third file
	glVertex3f(300.0f, 0.0f, -10.0f);
	glVertex3f(450.0f, 0.0f, -10.0f);
	glVertex3f(450.0f, 100.0f, -10.0f);
	glVertex3f(300.0f, 100.0f, -10.0f);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
}

void MapChange::DrawForSizeTwo()
{

	colSize = Scene::GetWindowWidth() / 7; // heng Full
	rowSize = Scene::GetWindowHeight() / 10; // shu  Give s size blank blocks at top
	glTranslatef(-513, -420, 0);
	for (int z = zPos; z < heightUnit + zPos; z++) // add modify value to X and Y, move 2D image to the middle of window
	{
		for (int x = xPos; x < widthUnit + xPos; x++)
		{
			caseNumber = (int)(generatorMap->GetBufferChar(x - xPos, z - zPos)) - 97;
			if (caseNumber >= 0 && caseNumber <= 12)
			{
				//printf("caseNumber = %d \n",caseNumber);
				glBindTexture(GL_TEXTURE_2D, textures[caseNumber]);
				DrawUnitBlock(x, z);
			}

		}
	}
	if (optionOpen)
	{
		glBindTexture(GL_TEXTURE_2D, ceilingTexId);
		DrawUnitBlock(newX, newY);
		glTranslatef(33.0f, 20.0f, 0.0f);
		DrawOptionPage();
		glTranslatef(-33.0f, -20.0f, 0.0f);
	}

	glTranslatef(113.0f, 630.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(800.0f, 0.0f, -10.0f);
	glVertex3f(800.0f, 20.0f, -10.0f);
	glVertex3f(0.0f, 20.0f, -10.0f);
	glEnd();
	glTranslatef(0.0f, 20.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(150.0f, 0.0f, -10.0f);
	glVertex3f(150.0f, 150.0f, -10.0f);
	glVertex3f(0.0f, 150.0f, -10.0f);
	glEnd();
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(150.0f, 0.0f, -10.0f);
	glVertex3f(300.0f, 0.0f, -10.0f);
	glVertex3f(300.0f, 150.0f, -10.0f);
	glVertex3f(150.0f, 150.0f, -10.0f);
	glEnd();
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(300.0f, 0.0f, -10.0f);
	glVertex3f(450.0f, 0.0f, -10.0f);
	glVertex3f(450.0f, 150.0f, -10.0f);
	glVertex3f(300.0f, 150.0f, -10.0f);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	
}
void MapChange::DrawForSizeThree()
{

	colSize = Scene::GetWindowWidth() / 10; // heng Full
	rowSize = Scene::GetWindowHeight() / 16; // shu  Give s size blank blocks at top
	glTranslatef(-480, -393, 0);
	for (int z = zPos; z < heightUnit + zPos; z++) // add modify value to X and Y, move 2D image to the middle of window
	{
		for (int x = xPos; x < widthUnit + xPos; x++)
		{
			caseNumber = (int)(generatorMap->GetBufferChar(x - xPos, z - zPos)) - 97;
			if (caseNumber >= 0 && caseNumber <= 12)
			{
				//printf("caseNumber = %d \n",caseNumber);
				glBindTexture(GL_TEXTURE_2D, textures[caseNumber]);
				DrawUnitBlock(x, z);
			}

		}
	}
	if (optionOpen)
	{
		glBindTexture(GL_TEXTURE_2D, ceilingTexId);
		DrawUnitBlock(newX, newY);
		DrawOptionPage();
	}

	glTranslatef(80.0f, 645.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(800.0f, 0.0f, -10.0f);
	glVertex3f(800.0f, 20.0f, -10.0f);
	glVertex3f(0.0f, 20.0f, -10.0f);
	glEnd();
	glTranslatef(0.0f, 20.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glVertex3f(150.0f, 0.0f, -10.0f);
	glVertex3f(150.0f, 90.0f, -10.0f);
	glVertex3f(0.0f, 90.0f, -10.0f);
	glEnd();
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(150.0f, 0.0f, -10.0f);
	glVertex3f(300.0f, 0.0f, -10.0f);
	glVertex3f(300.0f, 90.0f, -10.0f);
	glVertex3f(150.0f, 90.0f, -10.0f);
	glEnd();
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex3f(300.0f, 0.0f, -10.0f);
	glVertex3f(450.0f, 0.0f, -10.0f);
	glVertex3f(450.0f, 90.0f, -10.0f);
	glVertex3f(300.0f, 90.0f, -10.0f);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
}

void MapChange::DrawOptionPage()
{
	int x = 2, z = 4;
	
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(150, 110, -10.0f);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(810, 110, -10.0f);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(810, 400, -10.0f);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(150, 400, -10.0f);
	glEnd(); //bottom page of option page
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(150.0f, 0.0f, 0.0f);
	for (int i = 0; i < 7; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(i * 94 + 3, 260, -10.0f);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f((i + 1) * 94 - 3, 260, -10.0f);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f((i + 1) * 94 - 3, 390, -10.0f);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(i * 94 + 3, 390, -10.0f);
		glEnd();
	}
	glTranslatef(0.0f, -140.0f, 0.0f);
	int j = 0;
	for (int i = 7; i < 14; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(j * 94 + 3, 260, -10.0f);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f((j + 1) * 94 - 3, 260, -10.0f);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f((j + 1) * 94 - 3, 390, -10.0f);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(j * 94 + 3, 390, -10.0f);
		glEnd();
		j++;
	}
	
	
	
	
}