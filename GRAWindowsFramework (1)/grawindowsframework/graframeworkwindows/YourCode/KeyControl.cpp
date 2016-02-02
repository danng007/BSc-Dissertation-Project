#include "KeyControl.h"
KeyControl::KeyControl()
{

}

KeyControl::~KeyControl()
{

}

void KeyControl::HandleKey(int key, int state, int x, int y)
{
	// toggle booleans to remember which key was pressed/released ready for the update function
	/*switch (key) {
	case 'A':
	case 'a':
		aKey = state;
		break;
	case 'D':
	case 'd':
		dKey = state;
		break;
	case 'W':
	case 'w':
		wKey = state;
		break;
	case 'S':
	case 's':
		sKey = state;
		break;
	default:
		break;
	}*/
	if (state == 0 && key == 'q')
	{
		gameStart = !gameStart;
		printf("Q\n");
	}
}

bool KeyControl::GetGameStart()
{
	return gameStart;
}