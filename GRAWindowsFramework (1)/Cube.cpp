#include "Cube.h"
#include "Scene.h"

int selected = 0;



Cube::Cube()
{
	height = Scene::GetWindowHeight();

}

Cube::~Cube(void)
{

}

void Cube::Draw()
{
	
	glPushMatrix();

	glTranslatef(0.0, 0.0, 0.0);
	glLoadName(1);
	glBegin(GL_QUADS);
		glColor3f( 1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f + diffx,0.0f + diffy,-20.0f);
		glVertex3f(0.0f + diffx, 100.0f + diffy, -20.0f);
		glVertex3f(100.0f + diffx, 100.0f + diffy, -20.0f);
		glVertex3f(100.0f + diffx, 0.0f + diffy, -20.0f);
	glEnd();

	glutSwapBuffers();
}

void Cube::HandleMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		mouseX = x;
		mouseX = y;
		gl_select(x, height - y);
		drag = -drag;
	}
	
}

// Called every time the mouse moves - x and y are the mouse position.
void Cube::HandlePassiveMouseMotion(int x, int y)
{
	if (drag && (GLbyte)pbuff[3] == 1)
	{
		diffx = x - mouseX;
		diffy = y - mouseY;
		printf("Cube %d  %d/n", diffx, diffy);
	}
}


void Cube::gl_select(int x, int y)
{
	GLuint buff[64] = { 0 };
	GLint hits, view[4];

	/*
	This choose the buffer where store the values for the selection data
	*/
	glSelectBuffer(64, buff);

	/*
	This retrieve info about the viewport
	*/
	glGetIntegerv(GL_VIEWPORT, view);

	/*
	Switching in selecton mode
	*/
	glRenderMode(GL_SELECT);

	/*
	Clearing the name's stack
	This stack contains all the info about the objects
	*/
	glInitNames();

	/*
	Now fill the stack with one element (or glLoadName will generate an error)
	*/
	glPushName(0);

	/*
	Now modify the vieving volume, restricting selection area around the cursor
	*/
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	/*
	restrict the draw to an area around the cursor
	*/
	gluPickMatrix(x, y, 1.0, 1.0, view);
	gluPerspective(60, 1.0, 0.0001, 1000.0);

	/*
	Draw the objects onto the screen
	*/
	glMatrixMode(GL_MODELVIEW);

	/*
	draw only the names in the stack, and fill the array
	*/
	glutSwapBuffers();

	/*
	Do you remeber? We do pushMatrix in PROJECTION mode
	*/
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	/*
	get number of objects drawed in that area
	and return to render mode
	*/
	hits = glRenderMode(GL_RENDER);

	pbuff = buff;

	/*
	uncomment this to show the whole buffer
	* /
	gl_selall(hits, buff);
	*/

	glMatrixMode(GL_MODELVIEW);
}



