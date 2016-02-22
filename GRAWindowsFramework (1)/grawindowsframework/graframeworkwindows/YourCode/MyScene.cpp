
/*
Use this as the starting point to your work. Include the header file for each object in your scene, then add it to the scene using AddObjectToScene().
*/

#include "MyScene.h"
#include "Triangle.h"
#include "Floor.h"
#include "KeyControl.h"
#include "MapChange.h"

// Constructor creates your CourseworkScene and initialises the base class Scene
MyScene::MyScene( int argc, char **argv, const char *title, const int windowWidth, const int windowHeight ) : Scene(argc, argv, title, windowWidth, windowHeight)
{
}

// Initialise your scene by adding all the objects you want to be in the scene here
void MyScene::Init()
{

	glewInit();
    // set background colour
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	ReadFile();
	//c = new Cube();
//	AddObjectToScene(c);


	KeyControl *keyControl = new KeyControl();
	AddObjectToScene(keyControl);

	Floor *f = new Floor(keyControl, mapWidth, mapHeight);
	AddObjectToScene(f);

	MapChange *mapChange = new MapChange(keyControl, mapWidth, mapHeight);
	AddObjectToScene(mapChange);


	
	// for example: create and add a new triangle to the scene
 /*   Triangle *t = new Triangle();
    AddObjectToScene(t);*/
}

void MyScene::ReadFile()
{
	int j = 0, k = 0;
	int length;
	myfile.open("./file.txt");      // open input file  
	string s;
	if (myfile.good()) {
		while (getline(myfile, s)) {
			for (int i = 0; i < s.size(); i++) {

				k++;
			}
			mapHeight = k;
			k = 0;
			j++;
		}
	}
	mapWidth = j;
	printf( "MyScene Read Finish, mapWidth = %d, mapHeight = %d\n", mapWidth, mapHeight);
	myfile.close();
}