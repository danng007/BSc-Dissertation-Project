#include "KeyControl.h"
KeyControl::KeyControl()
{

}

KeyControl::~KeyControl()
{

}

void KeyControl::HandleKey(int key, int state, int x, int y)
{
	if (state == 0 && key == 'q')
	{
		gameStart = !gameStart;
		printf("KeyControlQ\n");
	}
}

bool KeyControl::GetGameStart()
{
	return gameStart;
}