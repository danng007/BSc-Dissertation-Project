#include "MapChange.h"
#include "Scene.h"

//#include "MyScene.h"
#define SIZE 50.0f
MapChange::MapChange(KeyControl* keyControl)
{
	controlKey = keyControl;
}

MapChange::~MapChange(void)
{
	glDisable(GL_TEXTURE_2D);
}

void MapChange::ReadFile()
{
	int j = 0, k = 0;
	int length;
	myfile.open("./file.txt");      // open input file  
	string s;
	if (myfile.good()) {
		while (getline(myfile, s)) { // getline reads one line into a string  
			// To prove that we have read in this line, print it backwards
			// one character at a time
			for (int i = 0; i < s.size(); i++) {
				buffer[j][k] = s[i];
				cout << buffer[j][k];
				k++;
			}
			k = 0;
			j++;
			cout << endl;
		}
	}
	cout << "Finish";
	myfile.close();
}
void MapChange::Draw()
{


}
void MapChange::Update(const double& deltatime)
{

	
}