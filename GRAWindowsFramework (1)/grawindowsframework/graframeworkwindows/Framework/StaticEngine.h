
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
This class is in charge of dealing with cross platform issues in setting up and opening a window
Do not change this code you, do not need to understand or look at this code
*/

#pragma once

#ifdef _WIN32
#include <Windows.h>
#include <GL\glew.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <GL\glut.h>

#else
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#endif


class StaticEngine
{
public:
    StaticEngine(int argc, char **argv, const char *title, const int& windowWidth, const int& windowHeight);
    virtual ~StaticEngine();
    
    virtual void Run();                                             //maps to init()
    
    static StaticEngine* GetCurrentInstance();
    static const char* GetWindowTitle();
    static int GetWindowID();
    static int GetWindowWidth();
    static int GetWindowHeight();
    
protected:
    /* Pointer to current application context */
    static StaticEngine *current;
    
    /* Window information */
    static const char* windowTitle;
    static int windowID;
    static int windowWidth;
    static int windowHeight;
    static int time;
    
    /* Callbacks */
    static void InitFunc();                                         //maps to init();
    static void DrawFunc();                                         //maps to drawScene()
    static void ResizeFunc(int w, int h);                           //maps to handleResize(int w, int h)
    static void KeyDownFunc(unsigned char key, int x, int y);       //maps to keyboardDown(unsigned char key, int x, int y)
    static void KeyUpFunc(unsigned char key, int x, int y);         //maps to keyboardUp(unsigned char key, int x, int y)
    static void SpecialKeyDownFunc(int key, int x, int y);          //maps to specialKeyDown(int key, int x, int y)
    static void SpecialKeyUpFunc(int key, int x, int y);            //maps to specialKeyUp(int key, int x, int y)
    static void MouseFunc(int button, int state, int x, int y);     //maps to mouse(int button, int state, int x, int y)
    static void MouseMotionFunc(int x, int y);                      //maps to mouseMotion(int x, int y)
    static void PassiveMouseMotionFunc(int x, int y);               //maps to passiveMouseMotion(int x, int y)
    static void IdleFunc();                                         //maps to idle()
    
    /* Virtual callback overrides */
    virtual void Init() = 0;
    virtual void DrawScene() = 0;
    virtual void HandleResize( int w, int h ) = 0;
    virtual void HandleKey( int key, int state, int x, int y ) = 0;
    virtual void Mouse( int button, int state, int x, int y ) = 0;
    virtual void MouseMotion( int x, int y ) = 0;
    virtual void PassiveMouseMotion( int x, int y ) = 0;
    virtual void Update( const double& ) = 0;
    
    /* GLError checking */
    static int CheckGLError();                                         //returns the number of openGL related errors
    
};


