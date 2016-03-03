#include "MapChange.h"
#include "Scene.h"

//#include "MyScene.h"
#define SIZE 50.0f
MapChange::MapChange(KeyControl* keyControl, int mapWidth, int mapHeight, char buffer[][100])
{
	bufferp = buffer;
	newX = 100, newY = 100;
	blockX = 100, blockY = 100;
	optionBlockX = 100, optionBlockY = 100;
	widthUnit = mapWidth;
	heightUnit = mapHeight;
	controlKey = keyControl;
	ReadFile();
	xPos = 0;
	zPos = 0;
	colSize = Scene::GetWindowWidth() / (widthUnit - 2); // heng Full
	rowSize = Scene::GetWindowHeight() / (heightUnit ); // shu  Give s size blank blocks at top
	printf("colsize = %f,  rowSize = %f \n", colSize, rowSize);
	glEnable(GL_TEXTURE_2D);
	wallTexId = Scene::GetTexture("./wallPaper.bmp");
	windowTexId = Scene::GetTexture("./window.bmp");
	floorTexId = Scene::GetTexture("./floor.bmp");
	ceilingTexId = Scene::GetTexture("./ceiling.bmp");
	doorTexId = Scene::GetTexture("./door.bmp");
	textures[0] = floorTexId;
	textures[1] = wallTexId;
	textures[2] = windowTexId;
	textures[3] = doorTexId;

}

MapChange::~MapChange(void)
{
	glDisable(GL_TEXTURE_2D);
}

void MapChange::ReadFile()
{
	int j = 0, k = 0;
	int length;
	myfile.open("./file.txt");      // open input file  
	string s;
	if (myfile.good()) {
		while (getline(myfile, s)) { 
			for (int i = 0; i < s.size(); i++) {
				bufferp[j][k] = s[i];
				cout << bufferp[j][k];
				k++;
			}
			k = 0; 
			j++;
			cout << endl;
		}
	}
	cout << "MapChange Read Finish\n";
	myfile.close();
}
void MapChange::Draw()
{
	if (Scene::GetGameStart())
	{
		glDisable(GL_LIGHTING);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		int width = Scene::GetWindowWidth();
		int height = Scene::GetWindowHeight();
		glOrtho(-width / 2, width / 2, -height / 2, height / 2, 1.0, 1000.0); //change to image view position
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(-480, -400, 0);

		
		for (int z = zPos ; z < heightUnit + zPos; z++) // add modify value to X and Y, move 2D image to the middle of window
		{
			for (int x = xPos; x < widthUnit + xPos; x++)
			{

				switch (bufferp[x - xPos][z - zPos])
				{
				case '0':
				{
					glBindTexture(GL_TEXTURE_2D, textures[0]);
					DrawUnitBlock(x, z);
					break;
				}
				case '1':
				{
					glBindTexture(GL_TEXTURE_2D, textures[1]);
					DrawUnitBlock(x, z);
					break;
				}
				case '2':
				{
					glBindTexture(GL_TEXTURE_2D, textures[2]);
					DrawUnitBlock(x, z);
					break;
				}
				case '3':
				{
					glBindTexture(GL_TEXTURE_2D, textures[3]);
					DrawUnitBlock(x, z);
					break;
				}
				default:
					break;
				}
			}
		}
		
			
		if (optionOpen)
		{
			glBindTexture(GL_TEXTURE_2D, ceilingTexId);
			DrawUnitBlock(newX, newY);
			DrawOptionPage();
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


		if (state == 1) // state == 1 means only reaction when mouse up
		{
			blockX = x / (int)colSize + 1;
			blockY = heightUnit - y / (int)rowSize; // the whole file matrix rotate 90 degree in order to fits the screen more suitable, so the coordinate should be modified
			printf("bufferp[%d][%d] is %c \n", x, y, bufferp[blockX][blockY]);
			if (optionOpen && x >= colSize && blockX <= widthUnit - 3 && y >= 7 * rowSize  && y <= 10 * rowSize)
			{
				int optionNum = 0;
				optionNum = (x - colSize) / (8 * colSize / 4);
				printf("option Choose %d\n", optionNum);
				bufferp[newX][newY] = optionNum + 48;
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

void MapChange::DrawOptionPage()
{
	int x = 2, z = 4;
	
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(x * colSize, z *rowSize, -10.0f);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f((x + 8) * colSize, z * rowSize, -10.0f);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f((x + 8) * colSize, (z + 3) *rowSize, -10.0f);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x * colSize, (z + 3)* rowSize, -10.0f);
	glEnd(); //bottom page of option page
	
	for (int i = 0; i < 4; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(x * colSize + 3, z *rowSize + 3, -10.0f);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f((x + 2) * colSize - 3, z * rowSize + 3, -10.0f);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f((x + 2) * colSize - 3, (z + 3) *rowSize - 3, -10.0f);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(x * colSize + 3, (z + 3)* rowSize - 3, -10.0f);
		glEnd();
		x += 2; // draw each option, reduce a little each size to make it look better.
	}
	
	
	
	
}