
/*
Use this as the starting point to your work. Include the header file for each object in your scene, then add it to the scene using AddObjectToScene().
*/

#include "MyScene.h"
#include "Floor.h"
#include "MapChange.h"
#include "MapGenerator.h"
#include "Sky.h"
// Constructor creates your CourseworkScene and initialises the base class Scene
MyScene::MyScene( int argc, char **argv, const char *title, const int windowWidth, const int windowHeight ) : Scene(argc, argv, title, windowWidth, windowHeight)
{
}

// Initialise your scene by adding all the objects you want to be in the scene here
void MyScene::Init()
{

	glewInit();
   
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Camera * currentCamera = GetCamera();

	MapGenerator *mapGenerator = new MapGenerator( mapWidth, mapHeight, currentCamera);
	AddObjectToScene(mapGenerator);

	Floor *f = new Floor( mapWidth, mapHeight, buffer, mapGenerator);
	AddObjectToScene(f);

	MapChange *mapChange = new MapChange( mapWidth, mapHeight, buffer, mapGenerator);
	AddObjectToScene(mapChange);

	Sky *sky = new Sky();
	AddObjectToScene(sky);

  
}

