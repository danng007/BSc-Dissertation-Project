#pragma once

#include "Object.h"
#include "Scene.h"
#include "MapGenerator.h"
class Sky : public Object
{
public:
	Sky();
	~Sky(void);

	int textures[6];
	void Draw();
private:
	void DrawSurface();
	void DrawDownSurface();
};