#include "Sky.h"
Sky::Sky()
{
	glEnable(GL_TEXTURE_2D);
	textures[0] = Scene::GetTexture("./Resources/textures/skybox_right.bmp");
	textures[1] = Scene::GetTexture("./Resources/textures/skybox_up.bmp");
	textures[2] = Scene::GetTexture("./Resources/textures/skybox_bottom.bmp");
}

Sky::~Sky()
{

}

void Sky::Draw()
{
	if (!Scene::GetGameStart())
	{
		
		glPushMatrix();
		glTranslatef(0.0f, 9909.0f, 0.0f);
		glScalef(10000.0f, 10000.0f, 10000.0f);
		//NEAR
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		DrawSurface();

		//RIGHT
		glRotatef(90, 0, 1, 0);
		DrawSurface();

		//BACK
		glRotatef(90, 0, 1, 0);
		DrawSurface();

		//LEFT
		glRotatef(90, 0, 1, 0);
		DrawSurface();
		glBindTexture(GL_TEXTURE_2D, 0);
		//UP
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glRotatef(90, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		DrawSurface();
		glBindTexture(GL_TEXTURE_2D, 0);
		
		//DOWN
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glRotatef(180, 1, 0, 0);
		DrawSurface();
		glBindTexture(GL_TEXTURE_2D, 0);
		
		glPopMatrix();
	}
}

void Sky::DrawSurface()
{
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(1, -1, 1);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-1, -1, 1);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-1, 1, 1);
	glTexCoord2d(0.0f, 1.0);
	glVertex3f(1, 1, 1);
	glEnd();
}

