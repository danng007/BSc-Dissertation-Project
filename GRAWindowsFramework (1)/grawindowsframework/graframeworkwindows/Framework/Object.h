
/*
	This is the class you will use to add objects to your scene.
	First create a new class for the object that you want to draw.
	Then make your new class inherit the 'Object' class.
	This way your new class will be able to override all the functions that an object may want to do.
	If you want to draw the new object you have created then you will need to override the Draw() function.
	If you want to update the object every frame you need to override the Update( const double& deltaTime ) function.
	If you want your object to recieve keyboard or mouse commands then override the Handle...() functions.
	Once you have done this you can add your new object to the scene with AddObjectToScene() in the Init function of MyScene.
*/

#pragma once

#include "Scene.h"

class Object
{
public:
    Object(void) {}
    virtual ~Object(void) {}
    
    // Called each frame after updates are done to draw it to the screen
    virtual void Draw(){};
    
    // Called each frame to update.
    virtual void Update( const double& deltaTime ){};
    
    // Called when keyboard input is received - x and y are the mouse coordinates at the time when the key was pressed
    virtual void HandleKey(int key, int state, int x, int y ){}
    // Called when a mouse button is pressed, or released.  x and y are the mouse position
    virtual void HandleMouseClick( int button, int state, int x, int y ){}
    // Called when the mouse moves if a button is pressed, x and y are the mouse position
    virtual void HandleMouseMotion( int x, int y ){}
    // Called every time the mouse moves, x and y are the mouse position.
    virtual void HandlePassiveMouseMotion( int x, int y ){}
};
