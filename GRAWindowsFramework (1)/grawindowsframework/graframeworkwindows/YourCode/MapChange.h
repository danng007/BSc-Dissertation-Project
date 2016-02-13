#pragma once

#include "Object.h"
#include <iostream>
#include <fstream>
#include "KeyControl.h"
using namespace std;
class MapChange : public Object
{
public:
	MapChange(KeyControl* keyControl);
	~MapChange(void);
	void Draw();
	void Update(const double& deltatime);
	void ReadFile();
	void HandleMouseClick(int button, int state, int x, int y);
private:
	static const int widthUnit = 10, heightUnit = 12; //widthUnit is height -.-
	char buffer[widthUnit][heightUnit];
	ifstream myfile;
	KeyControl* controlKey;



};

