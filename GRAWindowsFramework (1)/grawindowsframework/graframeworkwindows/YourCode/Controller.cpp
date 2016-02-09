#include "Controller.h"
Controller::Controller()
{

}

Controller::~Controller()
{

}

void Controller::HandleKey(int key, int state, int x, int y)
{
	if (state == 0 && key == 'q')
	{
		gameStart = !gameStart;
		printf("q\n");
	}
}

bool Controller::GetGameStart()
{
	return gameStart;
}