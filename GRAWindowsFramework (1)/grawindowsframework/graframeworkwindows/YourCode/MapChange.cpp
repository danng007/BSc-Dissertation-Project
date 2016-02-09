#include "MapChange.h"
#include "Scene.h"

//#include "MyScene.h"
#define SIZE 40.0f
MapChange::MapChange(KeyControl* keyControl)
{
	controlKey = keyControl;
	ReadFile();
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


		glBegin(GL_QUADS);
		for (int z = -3 ; z < heightUnit -3; z++) // add -3 to X and Y move 2D image to the middle of window
		{
			for (int x = -3; x < widthUnit-3; x++)
			{

				switch (buffer[x + 3][z + 3])
				{
				case '0':
				{
					glColor3f(1.0f,0.0f,0.0f);
					glNormal3f(0.0f, 1.0f, 0.0f);
					glVertex3f(x * SIZE, z *SIZE,-10.0f);
					glVertex3f((x + 1) * SIZE, z * SIZE, -10.0f);
					glVertex3f((x + 1) * SIZE, (z + 1) *SIZE,-10.0f);
					glVertex3f(x* SIZE, (z + 1)* SIZE, -10.0f);
					break;
				}
				case '1':
				{
					glColor3f(0.0f, 1.0f, 0.0f);
					glNormal3f(0.0f, 1.0f, 0.0f);
					glVertex3f(x * SIZE, z *SIZE, -10.0f);
					glVertex3f((x + 1) * SIZE, z * SIZE, -10.0f);
					glVertex3f((x + 1) * SIZE, (z + 1) *SIZE, -10.0f);
					glVertex3f(x* SIZE, (z + 1)* SIZE, -10.0f);
					break;
				}
				case '2':
				{
					glColor3f(0.0f, 0.0f, 1.0f);
					glNormal3f(0.0f, 1.0f, 0.0f);
					glVertex3f(x * SIZE, z *SIZE, -10.0f);
					glVertex3f((x + 1) * SIZE, z * SIZE, -10.0f);
					glVertex3f((x + 1) * SIZE, (z + 1) *SIZE, -10.0f);
					glVertex3f(x* SIZE, (z + 1)* SIZE, -10.0f);
					break;
				}
				case '3':
				{
					glColor3f(1.0f, 0.0f, 1.0f);
					glNormal3f(0.0f, 1.0f, 0.0f);
					glVertex3f(x * SIZE, z *SIZE, -10.0f);
					glVertex3f((x + 1) * SIZE, z * SIZE, -10.0f);
					glVertex3f((x + 1) * SIZE, (z + 1) *SIZE, -10.0f);
					glVertex3f(x* SIZE, (z + 1)* SIZE, -10.0f);
					break;
				}
				default:
					break;
				}
			}
		}


		glEnd();


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