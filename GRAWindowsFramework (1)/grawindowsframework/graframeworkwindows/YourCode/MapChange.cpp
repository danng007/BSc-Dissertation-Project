#include "MapChange.h"
#include "Scene.h"

//#include "MyScene.h"
#define SIZE 50.0f
MapChange::MapChange(KeyControl* keyControl)
{
	controlKey = keyControl;
	ReadFile();
	xPos = -5;
	zPos = -7;
	colSize = Scene::GetWindowWidth() / (widthUnit - 2); // heng Full
	rowSize = Scene::GetWindowHeight() / (heightUnit ); // shu  Give s size blank blocks at top
	printf("colsize = %f,  rowSize = %f \n", colSize, rowSize);
	glEnable(GL_TEXTURE_2D);
	wallTexId = Scene::GetTexture("./wallPaper.bmp");
	windowTexId = Scene::GetTexture("./window.bmp");
	floorTexId = Scene::GetTexture("./floor.bmp");
	ceilingTexId = Scene::GetTexture("./ceiling.bmp");
	doorTexId = Scene::GetTexture("./door.bmp");
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
				buffer[j][k] = s[i];
				cout << buffer[j][k];
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
		glOrtho(-width / 2, width / 2, -height / 2, height / 2, 1.0, 1000.0); //change to image view positino
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();


		
		for (int z = zPos ; z < heightUnit + zPos; z++) // add -3 to X and Y move 2D image to the middle of window
		{
			for (int x = xPos; x < widthUnit + xPos; x++)
			{

				switch (buffer[x - xPos][z - zPos])
				{
				case '0':
				{
					glBindTexture(GL_TEXTURE_2D, floorTexId);
					glBegin(GL_QUADS);
					glNormal3f(0.0f, 1.0f, 0.0f);
					glTexCoord2d(0.0f, 0.0f);
					glVertex3f(x * colSize, z *rowSize,-10.0f);
					glTexCoord2d(1.0f, 0.0f);
					glVertex3f((x + 1) * colSize, z * rowSize, -10.0f);
					glTexCoord2d(1.0f, 1.0f);
					glVertex3f((x + 1) * colSize, (z + 1) *rowSize, -10.0f);
					glTexCoord2d(0.0f, 1.0f);
					glVertex3f(x* colSize, (z + 1)* rowSize, -10.0f);
					glEnd();
					glBindTexture(GL_TEXTURE_2D, 0);
					break;
				}
				case '1':
				{
					glBindTexture(GL_TEXTURE_2D, wallTexId);
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
					break;
				}
				case '2':
				{
					glBindTexture(GL_TEXTURE_2D, windowTexId);
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
					break;
				}
				case '3':
				{
					glBindTexture(GL_TEXTURE_2D, doorTexId);
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
					break;
				}
				default:
					break;
				}
			}
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
	if ( state == 1) // state == 1 means only reaction when mouse up
	{
		printf("X is %d, Y is %d \n", x, y);
	}
}