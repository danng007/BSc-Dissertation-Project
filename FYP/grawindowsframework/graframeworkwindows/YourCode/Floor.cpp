#include "Floor.h"
#include "Scene.h"

//#include "MyScene.h"
#define SIZE 50.0f
Floor::Floor(KeyControl* keyControl, int mapWidth, int mapHeight, char buffer[][100], MapGenerator* mapGenerator) // past 2D array. need past array points
 
{
	generatorMap = mapGenerator;
	widthUnit = mapWidth;
	heightUnit = mapHeight;
	//bufferp = buffer;
	controlKey = keyControl;
	lightColour = 0.0f;
	scale = 10;
	wallHeight = 100.0f;
	
	glEnable(GL_TEXTURE_2D);
	wallTexId = Scene::GetTexture("./wallPaper.bmp");
	windowTexId = Scene::GetTexture("./window.bmp");
	floorTexId = Scene::GetTexture("./floor.bmp");
	ceilingTexId = Scene::GetTexture("./ceiling.bmp");
	doorTexId = Scene::GetTexture("./door.bmp");
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_NORMALIZE); //Automatically normalize normals
}

Floor::~Floor(void)
{
	glDisable(GL_TEXTURE_2D);
}


void Floor::DrawSingleFloor(int x, int z)
{

	//glColor3f(1.0f, 1.0f, 0.0f);
	glNormal3f(0.0f,1.0f,0.0f);
	glTexCoord2d(0.0f,0.0f);
	glVertex3f(x * SIZE, -9.9f, z *SIZE);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f((x + 1) * SIZE, -9.9f, z * SIZE);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f((x + 1) * SIZE, -9.9f, (z + 1) *SIZE);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x* SIZE, -9.9f, (z+1 )* SIZE);

}
void Floor::DrawSingleWall(int x, int z, float wallHeight, float y) // firstly, drawing normal floor, then drawing unit wall at the center of block, then extend the wall to their neighbours. 
{
	


	//Unite center wall
	glColor3f(1.0f, 1.0f, 1.0f);//white
	DrawUnitWall(x, z, wallHeight, y, 1, 1);
	//bottom : No bottom of wall is needed, as floor cover all bottom of room
	
	//Extend wall:
	if ((x - 1 >= 0 ) && generatorMap->getBufferChar(x - 1, z) != '0')
	{
		DrawUnitWall(x, z, wallHeight, y, 0, 1);
		
	}
	if ((x + 1 < widthUnit) && generatorMap->getBufferChar(x + 1, z) != '0')
	{
		DrawUnitWall(x, z, wallHeight, y, 2, 1);
	}
	if ((z + 1 < heightUnit) && generatorMap->getBufferChar(x, z + 1) != '0')
	{
		DrawUnitWall(x, z, wallHeight, y, 1, 2);
	}
	if ((z - 1 >= 0) && generatorMap->getBufferChar(x, z - 1) != '0')
	{
		DrawUnitWall(x, z, wallHeight, y, 1, 0);
	}
}
void Floor::DrawSingleWindow(int x, int z, float wallHeight, bool rowDirection)
{
	
	if (!rowDirection) //True: it's on the sides row of text file 
	{
		//back
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(x * SIZE, -10.0f, z *SIZE + SIZE / 3);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f((x + 1) * SIZE, -10.0f, z * SIZE + SIZE / 3);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f((x + 1) * SIZE, wallHeight, z *SIZE + SIZE / 3);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(x* SIZE, wallHeight, z * SIZE + SIZE / 3);
		//front
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(x * SIZE, -10.0f, z * SIZE + 2 * SIZE / 3);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f((x + 1) * SIZE, -10.0f, z * SIZE + 2 * SIZE / 3);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f((x + 1) * SIZE, wallHeight, z *SIZE + 2 * SIZE / 3);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(x* SIZE, wallHeight, z * SIZE + 2 * SIZE / 3);
		//left
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(x * SIZE, -10.0f, z * SIZE + SIZE / 3);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(x * SIZE, -10.0f, z * SIZE + 2 * SIZE / 3);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(x * SIZE, wallHeight, z *SIZE + 2 * SIZE / 3);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(x * SIZE, wallHeight, z * SIZE + SIZE / 3);
		//right
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f((x + 1) * SIZE, -10.0f, z * SIZE + SIZE / 3);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f((x + 1) * SIZE, -10.0f, z * SIZE + 2 * SIZE / 3);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f((x + 1) * SIZE, wallHeight, z *SIZE + 2 * SIZE / 3);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f((x + 1)* SIZE, wallHeight, z * SIZE + SIZE / 3);
	
	}
	else //false: its on the bottom and top tow of the txt file
	{
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(x * SIZE + SIZE / 3, -10.0f, z *SIZE );
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(x * SIZE + 2 * SIZE / 3, -10.0f, z * SIZE );
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(x * SIZE + 2 * SIZE / 3, wallHeight, z *SIZE );
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(x* SIZE + SIZE / 3, wallHeight, z * SIZE );
		//front
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(x * SIZE + SIZE / 3, -10.0f, (z + 1)* SIZE);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(x * SIZE + 2 * SIZE / 3, -10.0f, (z + 1) * SIZE);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(x * SIZE + 2 * SIZE / 3, wallHeight, (z + 1)*SIZE );
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(x* SIZE + SIZE / 3, wallHeight, (z + 1)* SIZE );
		//left
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(x * SIZE + SIZE / 3, -10.0f, z * SIZE );
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(x * SIZE + SIZE / 3, -10.0f, (z + 1) * SIZE);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(x * SIZE + SIZE / 3, wallHeight, (z + 1)*SIZE );
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(x * SIZE + SIZE / 3, wallHeight, z * SIZE );
		//right
		glNormal3f(0.0, 1.0, 0.0);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(x * SIZE + 2 * SIZE / 3, -10.0f, z * SIZE);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(x * SIZE + 2 * SIZE / 3, -10.0f, (z + 1)* SIZE );
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(x * SIZE + 2 * SIZE / 3, wallHeight, (z +1 ) *SIZE );
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(x * SIZE + 2 * SIZE / 3, wallHeight, z * SIZE );
	}
	//bottom
	glVertex3f(x * SIZE, -10.0f, z *SIZE);
	glVertex3f((x + 1) * SIZE, -10.0f, z * SIZE);
	glVertex3f((x + 1) * SIZE, -10.0f, (z + 1) *SIZE);
	glVertex3f(x* SIZE, -10.0f, (z + 1)* SIZE);
	
}
void Floor::DrawRoof(int x, int z)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(0, wallHeight, 0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(x * SIZE, wallHeight, 0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(x * SIZE, wallHeight, z *SIZE);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(0, wallHeight, z * SIZE);
}

void Floor::Draw()
{
	//glBindTexture should at the outside of glBegin and glEnd;
	if (!Scene::GetGameStart()) //detect the game state, if game start then begin drawing
	{
		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glDisable(GL_CULL_FACE);
		glTranslatef(-300.0f, 0.0f, -300.0f);

		for (int z = 0; z < heightUnit; z++)
		{
			for (int x = 0; x < widthUnit; x++)
			{
				glBindTexture(GL_TEXTURE_2D, floorTexId);
				glBegin(GL_QUADS);
				DrawSingleFloor(x, z);
				glEnd();
				glBindTexture(GL_TEXTURE_2D, 0);
				switch (generatorMap->getBufferChar(x, z))
				{
				case '0':
				{
					
					break;
				}
				case '1':
				{
					glBindTexture(GL_TEXTURE_2D, wallTexId);
					glBegin(GL_QUADS);
					DrawSingleWall(x, z, wallHeight, -10.0f);
					glEnd();
					glBindTexture(GL_TEXTURE_2D, 0);
					break;
				}
				case '2':
				{
					
					glBindTexture(GL_TEXTURE_2D, wallTexId);
					glBegin(GL_QUADS);
					DrawSingleWall(x, z, wallHeight, wallHeight / 2);
					glEnd();
					glBindTexture(GL_TEXTURE_2D, 0);

					glBindTexture(GL_TEXTURE_2D, windowTexId);
					GLfloat lightColor0[] = { lightColour, lightColour, lightColour, 1.0f }; //Color (0.5, 0.5, 0.5)
					GLfloat lightPos0[] = { x * SIZE + SIZE / 2, wallHeight / 2, z * SIZE + SIZE / 2, 1.0f }; //Position
					glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
					glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
					glBegin(GL_QUADS);
					if (generatorMap->getBufferChar(x, z - 1) != '0' &&generatorMap->getBufferChar(x, z + 1) != '0')
					{
						DrawSingleWindow(x, z, wallHeight / 2, true);
					}
					else
					{
						
						DrawSingleWindow(x, z, wallHeight / 2, false);
					}
					glEnd();
					glBindTexture(GL_TEXTURE_2D, 0);
					break;
				}
				case '3':
				{
					glBindTexture(GL_TEXTURE_2D, wallTexId);
					glBegin(GL_QUADS);
					DrawSingleWall(x, z, wallHeight, wallHeight / 2);
					glEnd();
					glBindTexture(GL_TEXTURE_2D, 0);

					glBindTexture(GL_TEXTURE_2D, doorTexId);
					glBegin(GL_QUADS);
					if (generatorMap->getBufferChar(x, z - 1) != '0' && generatorMap->getBufferChar(x, z + 1) != '0')
					{
						DrawSingleWindow(x, z, wallHeight / 2, true);
					}
					else
					{
						DrawSingleWindow(x, z, wallHeight / 2, false);
					}
					glEnd();
					glBindTexture(GL_TEXTURE_2D, 0);
					break;
					break;
				}
				default:
					break;
				}
			}
		}
		glBindTexture(GL_TEXTURE_2D, ceilingTexId);
		glBegin(GL_QUADS);
		DrawRoof(widthUnit, heightUnit);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();
		glEnable(GL_CULL_FACE);
		glPopAttrib();
	}

}
void Floor::Update(const double& deltatime)
{

	if (lightChange)
	{
		lightColour += 0.005f;
	}
	else
	{
		lightColour -= 0.005f;
	}
	if (lightColour >= 1.0f )
	{
		lightChange = false;
	}
	if (lightColour <= 0.0f)
	{
		lightChange = true;
	}
}
void Floor::DrawUnitWall(int x, int z, float wallHeight, float y, int xSize, int ySize)
{
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(x * SIZE +  xSize * SIZE / 3, y, z *SIZE + ySize * SIZE / 3);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(x * SIZE + xSize * SIZE / 3, y, z *SIZE + (1+ ySize) *  SIZE / 3);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(x * SIZE + xSize * SIZE / 3, wallHeight, z *SIZE + (1 + ySize) *   SIZE / 3);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x * SIZE + xSize * SIZE / 3, wallHeight, z *SIZE + ySize * SIZE / 3);
	//front
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(x * SIZE + xSize * SIZE / 3, y, z *SIZE + ySize * SIZE / 3);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(x * SIZE + (1 + xSize) * SIZE / 3, y, z *SIZE + ySize * SIZE / 3);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(x * SIZE + (1 + xSize) *SIZE / 3, wallHeight, z *SIZE + ySize * SIZE / 3);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x * SIZE + xSize *SIZE / 3, wallHeight, z *SIZE + ySize * SIZE / 3);
	//left
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(x * SIZE + (1 + xSize) *SIZE / 3, y, z *SIZE + ySize * SIZE / 3);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(x * SIZE + (1 + xSize) *SIZE / 3, y, z *SIZE + (1 + ySize) *   SIZE / 3);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(x * SIZE + (1 + xSize) *SIZE / 3, wallHeight, z *SIZE + (1 + ySize) *   SIZE / 3);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x * SIZE + (1 + xSize) * SIZE / 3, wallHeight, z *SIZE + ySize * SIZE / 3);
	//right
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(x * SIZE + xSize * SIZE / 3, y, z *SIZE + (1 + ySize) *   SIZE / 3);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(x * SIZE + (1 + xSize) * SIZE / 3, y, z *SIZE + (1 + ySize) *   SIZE / 3);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(x * SIZE + (1 + xSize) *SIZE / 3, wallHeight, z *SIZE + (1 + ySize) *   SIZE / 3);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(x * SIZE + xSize * SIZE / 3, wallHeight, z *SIZE + (1 + ySize) *   SIZE / 3);
}