#pragma warning(disable:4996)
#pragma once

#include "Object.h"
#include "Scene.h"
#include <sstream>
using namespace std;
class LoadModel : public Object
{
public:
	LoadModel(void);
	~LoadModel(void);
	void LoadOBJ(const char * path);
	void RenderModel();
	struct POINT3{
		double X;
		double Y;
		double Z;
	};
	struct Texture{
		double TU;
		double TV;
	};
	struct Normals{
		double NX;
		double NY;
		double NZ;
	};
	struct Face{
		int V[3];
		int T[3];
		int N[3];
	};
	struct Material{
		string filePath;
	};
	class PIC
	{
	public:
		vector<POINT3> V;//V：代表顶点。格式为V X Y Z，V后面的X Y Z表示三个顶点坐标。浮点型
		vector<Texture>  VT;//表示纹理坐标。格式为VT TU TV。浮点型
		vector<Normals> VN;//VN：法向量。每个三角形的三个顶点都要指定一个法向量。格式为VN NX NY NZ。浮点型
		vector<Face> F;//F：面。面后面跟着的整型值分别是属于这个面的顶点、纹理坐标、法向量的索引。
		vector<Material> M;
		//面的格式为：f Vertex1/Texture1/Normal1 Vertex2/Texture2/Normal2 Vertex3/Texture3/Normal3
	} m_pic;
	int faceCounter[1000], counter = -1, outCounter = 0;
	int textID;
	string filePaths[1000];
	string filePath;
	int textIDs[1000];
};