#pragma once

#include "Scene.h"

class Controller 
{
public:
	Controller(void);
	~Controller(void);
	void HandleKey(int key, int state, int x, int y);
	bool GetGameStart();

private:
	bool gameStart = false;
};