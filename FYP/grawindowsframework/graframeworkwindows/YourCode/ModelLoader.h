#pragma once

#include "Object.h"
#include "Scene.h"
#include <glm\glm\glm.hpp>
using namespace std;
class ModelLoader : public Object
{
public:
	ModelLoader(void);
	
	bool loadOBJ(const char * path, std::vector < glm::vec3 > & vertices, std::vector < glm::vec2 > & uvs, std::vector < glm::vec3 > & normals);
private:
	~ModelLoader(void);
};