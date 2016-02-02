#include "Object.h"

class Cube : public Object
{
public:
	Cube();
	~Cube(void);
	// Called when a mouse button is pressed, or released - x and y are the mouse position.
	void HandleMouseClick(int button, int state, int x, int y);
	void gl_select(int x, int y);
	// Called every time the mouse moves - x and y are the mouse position.
	void HandlePassiveMouseMotion(int x, int y);

	void Draw();
private:
	GLuint *pbuff;
	bool drag = false;
	double height = 0.0f;
	double mouseX = 0.0f, mouseY = 0.0f, diffx = 0.0f, diffy = 0.0f;

};
