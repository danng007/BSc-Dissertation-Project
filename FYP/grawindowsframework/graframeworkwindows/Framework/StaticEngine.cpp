
/*******************************************************************
********************************************************************
********************************************************************
********************************************************************
******************* DO NOT CHANGE THIS FILE  ***********************
********************************************************************
********************************************************************
********************************************************************
*******************************************************************/

/*
Implementation of platform specific window handling operations.
Do not change this file, you do not need to understand this either.
*/

#include "StaticEngine.h"
#include <string>

StaticEngine *StaticEngine::current = 0;
const char* StaticEngine::windowTitle = "";
int StaticEngine::windowID = 0;
int StaticEngine::windowWidth = 1;
int StaticEngine::windowHeight = 1;
int StaticEngine::time = 0;

StaticEngine::StaticEngine(int argc, char **argv, const char *title, const int& windowWidth, const int& windowHeight)
{
    StaticEngine::windowTitle = title;
    StaticEngine::windowWidth = windowWidth;
    StaticEngine::windowHeight = windowHeight;
    
    glutInit(&argc, argv);
}

StaticEngine::~StaticEngine()
{
}

void StaticEngine::Run()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100,100);
    windowID = glutCreateWindow(windowTitle);
    current = this;
    
    glutDisplayFunc(DrawFunc);
    glutReshapeFunc(ResizeFunc);
    glutKeyboardFunc(KeyDownFunc);
    glutKeyboardUpFunc(KeyUpFunc);
    glutSpecialFunc(SpecialKeyDownFunc);
    glutSpecialUpFunc(SpecialKeyUpFunc);
    glutMouseFunc(MouseFunc);
    glutMotionFunc(MouseMotionFunc);
    glutPassiveMotionFunc(PassiveMouseMotionFunc);
    glutIdleFunc(IdleFunc);
    
    printf("Running OpenGL Version: %s\n", glGetString(GL_VERSION));
    
    InitFunc();
    
    glutMainLoop();
}

StaticEngine* StaticEngine::GetCurrentInstance()
{
    return StaticEngine::current;
}

const char* StaticEngine::GetWindowTitle()
{
    return StaticEngine::windowTitle;
}

int StaticEngine::GetWindowID()
{
    return StaticEngine::windowID;
}

int StaticEngine::GetWindowWidth()
{
    return StaticEngine::windowWidth;
}

int StaticEngine::GetWindowHeight()
{
    return StaticEngine::windowHeight;
}

void StaticEngine::InitFunc()
{
    // set background colour
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    
    // enable depth tests less than or equal
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    // enable culling of backface polygons
    glEnable(GL_CULL_FACE);
    
    // enable transparancy blending
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // enable 2D texturing
    glEnable(GL_TEXTURE_2D);
    
    // enable blending colour information with texture information
    glEnable(GL_COLOR_MATERIAL);
    
    // turn off 2 sided lighting
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    
    // set the ambient light model
    GLfloat global_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
    // enable directional light lighting
    // (x, y, z, 0.0) -> directional lighting
    // (x, y, z, 1.0) -> positional lighting
    glEnable(GL_LIGHTING);
    GLfloat ambience[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambience);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHT0);
    
    // enable smooth shading from lighting
    glShadeModel(GL_SMOOTH);
    
    // enable automatic normalisation of normal vectors
    glEnable(GL_NORMALIZE);
    
    current->Init();
    time = 0;
}

void StaticEngine::DrawFunc()
{
    current->DrawScene();
    glutSwapBuffers();
}

void StaticEngine::ResizeFunc(int w, int h)
{
	glutReshapeWindow(800, 700); //fixed the windows size;
   /* StaticEngine::windowWidth = w;
    StaticEngine::windowHeight = h;
    current->HandleResize(w,h);*/
}

void StaticEngine::KeyDownFunc(unsigned char key, int x, int y)
{
    current->HandleKey(key, 1, x, y);
}

void StaticEngine::KeyUpFunc(unsigned char key, int x, int y)
{
    current->HandleKey(key, 0, x, y);
}

void StaticEngine::SpecialKeyDownFunc(int key, int x, int y)
{
    if( key>=1 && key<=12){
        current->HandleKey(key + 255, 1, x, y);
    } else {
        current->HandleKey(key+ 168, 1, x, y);
    }
}

void StaticEngine::SpecialKeyUpFunc(int key, int x, int y)
{
    if( key>=1 && key<=12){
        current->HandleKey(key + 255, 0, x, y);
    } else {
        current->HandleKey(key+ 168, 0, x, y);
    }
}

void StaticEngine::MouseFunc(int button, int state, int x, int y)
{
    current->Mouse(button, state, x, y);
}

void StaticEngine::MouseMotionFunc(int x, int y)
{
    current->MouseMotion(x, y);
}

void StaticEngine::PassiveMouseMotionFunc(int x, int y)
{
    current->PassiveMouseMotion(x, y);
}

void StaticEngine::IdleFunc()
{
    int t = glutGet(GLUT_ELAPSED_TIME);
    double diff = (double)(t - time) / 1000.0;
    time = t;
    
    current->Update(diff);
    
    glutPostRedisplay();
}

int StaticEngine::CheckGLError()
{
    int e=0;
    GLenum error = glGetError();
    while ( GL_NO_ERROR != error )
    {
        e++;
        printf("StaticEngine:GL Error %i: %s\n", e, gluErrorString(error));
        error = glGetError();
    }
    
    return e;
}

