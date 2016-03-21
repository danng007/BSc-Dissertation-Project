#include "ModelLoader.h"
ModelLoader::ModelLoader()
{

}

ModelLoader::~ModelLoader()
{

}

void ModelLoader::loadOBJ(const char * path, std::vector < glm::vec3 > &vertices, std::vector < glm::vec2 > &uvs, std::vector < glm::vec3 > &normals)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > modelVertices;
	std::vector< glm::vec2 > modelUvs;
	std::vector< glm::vec3 > modelNormals;
	FILE * file = fopen(path, "rt");
	if (file == NULL){
		printf("Impossible to open the file !\n");
		return;
	}
	while (true)
	{
		char eachFileLine[128];
		int eachLine = fscanf(file, "%s", eachFileLine);
		if (eachLine == EOF)
		{
			break; //if file reading end, break;
		}
		if (strcmp(eachFileLine, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			modelVertices.push_back(vertex);
		}
		else
		{
			if (strcmp(eachFileLine, "vt") == 0){
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				modelUvs.push_back(uv);
			}
			else
			{
				if (strcmp(eachFileLine, "vn") == 0){
					glm::vec3 normal;
					fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
					modelNormals.push_back(normal);
				}

				else
				{
					if (strcmp(eachFileLine, "f") == 0){
						std::string vertex1, vertex2, vertex3;
						unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
						int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
						if (matches != 9){
							printf("File can't be read by our simple parser : ( Try exporting with other options\n");
							return;
						}
						vertexIndices.push_back(vertexIndex[0]);
						vertexIndices.push_back(vertexIndex[1]);
						vertexIndices.push_back(vertexIndex[2]);
						uvIndices.push_back(uvIndex[0]);
						uvIndices.push_back(uvIndex[1]);
						uvIndices.push_back(uvIndex[2]);
						normalIndices.push_back(normalIndex[0]);
						normalIndices.push_back(normalIndex[1]);
						normalIndices.push_back(normalIndex[2]);
					}
				}
			}
		}
	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = modelVertices[vertexIndex - 1];
		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 theUvss = modelUvs[uvIndex - 1];
		uvs.push_back(theUvss);
	}	
	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 theNormals = modelNormals[normalIndex - 1];
		normals.push_back(theNormals);
	}
	
	
}