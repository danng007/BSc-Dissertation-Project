
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
The basic class that contains a list of objects to draw each frame,
and deals with all the input callbacks and windowing. 
You must not modify this.
*/

#pragma once

#include "StaticEngine.h"
#include "Texture.h"
#include "Camera.h"
#include <vector>

class Object;

class Scene : public StaticEngine
{
public:
	Scene( int argc, char **argv, const char *title, const int windowWidth, const int windowHeight );
	virtual ~Scene();

    // This function returns the current width of the window
    static int GetWindowWidth();
    
    // This function return the current height of the window
    static int GetWindowHeight();
    
    // This function will load a texture at filename and upload it to a texture buffer
    // it returns the number / texture buffer reference it was uploaded to
	static int GetTexture(std::string fileName);
    
    // This function will return a pointer to the Camera class
    static Camera* GetCamera() { return &camera; }
	static bool GetGameStart();

protected:

	// This function will be called before the window is opened
	virtual void Init() = 0;

	// This function will be called when the screen needs to be redraw
	void DrawScene();
	// This function will be called when the window is resized
	void HandleResize( int w, int h );
	// This function will be called when a keyboard key is pressed
	void HandleKey( int key, int state, int x, int y );
	// This function will be called when a mouse button is pressed down/up
	void Mouse( int button, int state, int x, int y );
	// This function will be called when a mouse button is pressed then dragged
	void MouseMotion( int x, int y );
	// This is called whenever the mouse moves
	void PassiveMouseMotion( int x, int y);
	// This function will be called when the screen isn't redrawing, resizing or doing any processinf
	void Update( const double& deltatime );

    // This function will push a displayable object into the scene list so Draw and Update will be called on it
	void AddObjectToScene( Object *object );
 
private:

	static bool gameStart;
	static Texture texture;
    static Camera camera;
	std::vector<Object*> sceneObjs;
};
