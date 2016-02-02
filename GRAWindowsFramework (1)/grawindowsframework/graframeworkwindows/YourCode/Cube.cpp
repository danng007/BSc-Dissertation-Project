#include "Cube.h"
#include "Scene.h"
#define SIZE 512

Cube::Cube()
{
	height = Scene::GetWindowHeight();
	width = Scene::GetWindowWidth();
	m_position[0] = 0;
	m_position[1] = 0;
	m_position[2] = 0;
	initFBO();
	g_texture = Scene::GetTexture("./face.bmp");
	
}

Cube::~Cube(void)
{
	
}


void Cube::initFBO()
{
	
  	glGenFramebuffersEXT(1, &g_framebuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_framebuffer);
	glGenTextures(1, &g_texture);
	glBindTexture(GL_TEXTURE_2D, g_texture);
	//设置filter
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	 //声明贴图大小及格式分配空间
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	//framebuffer的RGBA贴图-绑定纹理与FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, g_texture, 0);

	//分配zbuffer给FBO 使用 
	glGenRenderbuffersEXT(1, &g_depthbuffer);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, g_depthbuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, 256, 256);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, g_depthbuffer);
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	
		switch (status){
		case GL_FRAMEBUFFER_COMPLETE_EXT:
			 //    MessageBox(NULL,"GL_FRAMEBUFFER_COMPLETE_EXT!","SUCCESS",MB_OK|MB_ICONEXCLAMATION);
				break;
			
				 case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
					printf("Error!\n");
					 exit(0);
					 break;
	}

}
void Cube::Picking()
{
	// set mesh position
	glPushMatrix();
	glTranslatef(m_position[0], m_position[1], m_position[2]);

	glColor3f(m_colorID[0] / 255.0f, m_colorID[1] / 255.0f, m_colorID[2] / 255.0f);

	glBegin(GL_QUADS);
	glVertex3f(0.0f + diffx, 0.0f + diffy, -20.0f);
	glVertex3f(0.0f + diffx, 100.0f + diffy, -20.0f);
	glVertex3f(100.0f + diffx, 100.0f + diffy, -20.0f);
	glVertex3f(100.0f + diffx, 0.0f + diffy, -20.0f);
	glEnd();
	printf("picking: %f  %f  %f \n", m_colorID[0] / 255.0f, m_colorID[1] / 255.0f, m_colorID[2] / 255.0f);
	glPopMatrix();


}
void Cube::Draw()
{
	
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, g_framebuffer);
		glPushAttrib(GL_VIEWPORT_BIT);
		glViewport(0, 0, width, height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glTranslatef(m_position[0], m_position[1], m_position[2]);
		glColor3f(1.0f, 1.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, g_texture);
		glBegin(GL_QUADS);
		glTexCoord2d(0.0f, 0.0f);
		glVertex3f(0.0f + diffx, 0.0f + diffy, -20.0f);
		glTexCoord2d(1.0f, 0.0f);
		glVertex3f(0.0f + diffx, 100.0f + diffy, -20.0f);
		glTexCoord2d(1.0f, 1.0f);
		glVertex3f(100.0f + diffx, 100.0f + diffy, -20.0f);
		glTexCoord2d(0.0f, 1.0f);
		glVertex3f(100.0f + diffx, 0.0f + diffy, -20.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

}


void Cube::HandleMouseClick(int button, int state, int x, int y)
{
	printf("!!!!!!!!!H\n");
	// turn off texturing, lighting and fog
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_FOG);
	glDisable(GL_LIGHTING);

	// render every object in our scene
	// suppose every object is stored in a list container called SceneObjects
	/* list<SceneObject *>::iterator itr = SceneObjects.begin();
	while(itr != SceneObjects.end())
	{
	(*itr)->Picking();
	itr++;
	}*/
	Picking();
	// get color information from frame buffer
	unsigned char pixel[3];

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

	// now our picked screen pixel color is stored in pixel[3]
	// so we search through our object list looking for the object that was selected
	//itr = SceneObjects.begin();
	//while(itr != SceneObjects.end())
	//{
	//     if((*itr)->m_colorID[0] == pixel[0] && (*itr)->m_colorID[1] == pixel[1] && (*itr)->m_colorID[2] == pixel[2])
	//     {
	//          // flag object as selected
	//          SetSelected((*itr);
	//          break;
	//     }
	//     itr++;
	//}
	printf("m_color: %d  %d  %d    pixel: %d  %d  %d\n", m_colorID[0], m_colorID[1], m_colorID[2], pixel[0], pixel[1], pixel[2]);
	if (m_colorID[0] == pixel[0] && m_colorID[1] == pixel[1] && m_colorID[2] == pixel[2])
	{
		// flag object as selected
		printf("HHHHHHHHHH\n");
	}
	drag = true;

}