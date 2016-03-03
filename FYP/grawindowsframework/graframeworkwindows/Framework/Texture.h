
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
Texture is a class owned by Scene for handling the loading of bitmap (.bmp) textures from file into memory and passing them on to the GPU.
Call the GetTexture function with a file name and it will load it into memory (if it hasn't been loaded already), and return an integer identifier for the associated texture object in graphics memory.
Do not change this file, you do not need to understand this file as it is beyond the scope of this module. However just know that from inside a Object you can call Scene::GetTexture("myfilename.bmp") to load a texture.
*/

#pragma once

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <map>
#include <string>

class Texture
{
public:
	Texture(void);
	~Texture(void);

	// Loads a texture into memory and returns the id of the texture object created.
	int GetTexture(std::string fileName);

private:
	std::map<int, std::string> textures;
};

