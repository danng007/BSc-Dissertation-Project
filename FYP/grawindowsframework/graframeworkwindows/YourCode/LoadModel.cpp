#include "LoadModel.h"

#define YU 1//800//2
LoadModel::LoadModel()
{
	
}

LoadModel::~LoadModel()
{

}

void LoadModel::LoadOBJ(const char * path)
{

		ifstream ifs(path);//cube bunny Eight
		string s;
		Mian *f;
		POINT3 *v;
		FaXiangLiang *vn;
		WenLi    *vt;
		while (getline(ifs, s))
		{
			if (s.length()<2)continue;
			if (s[0] == 'v'){
				if (s[1] == 't'){//vt 0.581151 0.979929 纹理
					istringstream in(s);
					vt = new WenLi();
					string head;
					in >> head >> vt->TU >> vt->TV;
					m_pic.VT.push_back(*vt);
				}
				else if (s[1] == 'n'){//vn 0.637005 -0.0421857 0.769705 法向量
					istringstream in(s);
					vn = new FaXiangLiang();
					string head;
					in >> head >> vn->NX >> vn->NY >> vn->NZ;
					m_pic.VN.push_back(*vn);
				}
				else{//v -53.0413 158.84 -135.806 点
					istringstream in(s);
					v = new POINT3();
					string head;
					in >> head >> v->X >> v->Y >> v->Z;
					m_pic.V.push_back(*v);
				}
			}
			else if (s[0] == 'f'){//f 2443//2656 2442//2656 2444//2656 面
				for (int k = s.size() - 1; k >= 0; k--){
					if (s[k] == '/')s[k] = ' ';
				}
				istringstream in(s);
				f = new Mian();
				string head;
				in >> head;
				int i = 0;
				while (i<3)
				{
					if (m_pic.V.size() != 0)
					{
						in >> f->V[i];
						f->V[i] -= 1;
					}
					if (m_pic.VT.size() != 0)
					{
						in >> f->T[i];
						f->T[i] -= 1;
					}
					if (m_pic.VN.size() != 0)
					{
						in >> f->N[i];
						f->N[i] -= 1;
					}
					i++;
				}
				m_pic.F.push_back(*f);
			}
		}
	
}
void LoadModel::RenderModel()
{
	
	
		for (int i = 0; i<m_pic.F.size(); i++)
		{
			glBegin(GL_TRIANGLES);                            // 绘制三角形GL_TRIANGLES;GL_LINE_LOOP;GL_LINES;GL_POINTS
			if (m_pic.VT.size() != 0)glTexCoord2f(m_pic.VT[m_pic.F[i].T[0]].TU, m_pic.VT[m_pic.F[i].T[0]].TV);  //纹理    
			if (m_pic.VN.size() != 0)glNormal3f(m_pic.VN[m_pic.F[i].N[0]].NX, m_pic.VN[m_pic.F[i].N[0]].NY, m_pic.VN[m_pic.F[i].N[0]].NZ);//法向量
			glVertex3f(m_pic.V[m_pic.F[i].V[0]].X / YU, m_pic.V[m_pic.F[i].V[0]].Y / YU, m_pic.V[m_pic.F[i].V[0]].Z / YU);        // 上顶点

			if (m_pic.VT.size() != 0)glTexCoord2f(m_pic.VT[m_pic.F[i].T[1]].TU, m_pic.VT[m_pic.F[i].T[1]].TV);  //纹理
			if (m_pic.VN.size() != 0)glNormal3f(m_pic.VN[m_pic.F[i].N[1]].NX, m_pic.VN[m_pic.F[i].N[1]].NY, m_pic.VN[m_pic.F[i].N[1]].NZ);//法向量
			glVertex3f(m_pic.V[m_pic.F[i].V[1]].X / YU, m_pic.V[m_pic.F[i].V[1]].Y / YU, m_pic.V[m_pic.F[i].V[1]].Z / YU);        // 左下

			if (m_pic.VT.size() != 0)glTexCoord2f(m_pic.VT[m_pic.F[i].T[2]].TU, m_pic.VT[m_pic.F[i].T[2]].TV);  //纹理
			if (m_pic.VN.size() != 0)glNormal3f(m_pic.VN[m_pic.F[i].N[2]].NX, m_pic.VN[m_pic.F[i].N[2]].NY, m_pic.VN[m_pic.F[i].N[2]].NZ);//法向量
			glVertex3f(m_pic.V[m_pic.F[i].V[2]].X / YU, m_pic.V[m_pic.F[i].V[2]].Y / YU, m_pic.V[m_pic.F[i].V[2]].Z / YU);        // 右下
			glEnd();// 三角形绘制结束    

		}
	
		
}