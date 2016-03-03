
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
Scene object handles drawing, updating and sending key events to all the objects in the scene.
Do not change this file. You may only add objects to the Scene using AddObjectsToScene in the Init function of MyScene.
*/

#include "Scene.h"
#include "Object.h"

Texture Scene::texture = Texture();
Camera Scene::camera = Camera();
bool Scene::gameStart = false;
Scene::Scene( int argc, char **argv, const char *title, const int windowWidth, const int windowHeight ) : StaticEngine(argc, argv, title, windowWidth, windowHeight)
{
}

Scene::~Scene()
{
	for(Object* obj : sceneObjs)
	{
	    if(obj != NULL)
	       delete obj;
	    obj = NULL;
	}
}

int Scene::GetWindowWidth()
{
    return StaticEngine::windowWidth;
}

int Scene::GetWindowHeight()
{
    return StaticEngine::windowHeight;
}

int Scene::GetTexture(std::string fileName)
{
    return texture.GetTexture(fileName);
}

void Scene::Init()
{
}

void Scene::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    	camera.SetUpCamera();
		for( Object *obj : sceneObjs )
		obj->Draw();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	CheckGLError();
}

void Scene::HandleResize(int w, int h)
{
	camera.SetViewport(w, h);
}

void Scene::HandleKey( int key, int state, int x, int y )
{
	if (state == 0 && (key == 'o' || key == 'O'))
	{
		gameStart = !gameStart;
		printf("o\n");
	}
    camera.HandleKey(key, state, x, y);
	for( Object *obj : sceneObjs )
         obj->HandleKey(key, state, x, y );
}

void Scene::Mouse(int button, int state, int x, int y)
{
    camera.HandleMouseClick( button, state, x, y );
	for( Object *obj : sceneObjs )
         obj->HandleMouseClick( button, state, x, y );
}

void Scene::MouseMotion(int x, int y)
{
    camera.HandleMouseMotion( x, y );
    for( Object *obj : sceneObjs )
         obj->HandleMouseMotion( x, y );
}

void Scene::PassiveMouseMotion( int x, int y)
{
    camera.HandlePassiveMouseMotion( x, y );
    for( Object *obj : sceneObjs )
         obj->HandlePassiveMouseMotion( x, y );
}

void Scene::Update( const double& deltatime )
{
    camera.Update(deltatime);
    for( Object *obj : sceneObjs )
         obj->Update(deltatime);
}

void Scene::AddObjectToScene( Object *object )
{
    sceneObjs.push_back(object);
}

bool Scene::GetGameStart()
{
	return gameStart;
}