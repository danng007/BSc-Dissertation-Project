#include "BaseColor.h"
BaseColor::BaseColor()
{
	m_colorID[0] = gColorID[0];
	m_colorID[1] = gColorID[1];
	m_colorID[2] = gColorID[2];

	gColorID[0]++;
	if (gColorID[0] > 255)
	{
		gColorID[0] = 0;
		gColorID[1]++;
		if (gColorID[1] > 255)
		{
			gColorID[1] = 0;
			gColorID[2]++;
		}
	}
}

BaseColor::~BaseColor()
{
}

unsigned char BaseColor::gColorID[3] = { 1, 1, 1 };