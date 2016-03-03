#pragma once

#include "Object.h"
#include "Scene.h"

class KeyControl : public Object
{
public:
	KeyControl(void);
	~KeyControl(void);
	void HandleKey(int key, int state, int x, int y);
	bool GetGameStart();

private:
	bool gameStart = false;
};