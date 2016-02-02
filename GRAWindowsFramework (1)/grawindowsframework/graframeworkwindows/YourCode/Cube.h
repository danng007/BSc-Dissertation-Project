#include "Object.h"
#include "BaseColor.h"

class Cube : public Object, public BaseColor
{
public:
	Cube();
	~Cube(void);
	// Called when a mouse button is pressed, or released - x and y are the mouse position.
	void HandleMouseClick(int button, int state, int x, int y);
	
	// Called every time the mouse moves - x and y are the mouse position.
//	void HandlePassiveMouseMotion(int x, int y);

	void Render();
	void Picking();
	void Draw();
	void initFBO();
private:
	GLuint g_framebuffer;
	GLuint g_texture;
	GLuint g_depthbuffer;
	float m_position[3];
	int texId;
	bool drag = true;
	double height = 0.0f, width = 0.0f;
	double mouseX = 0.0f, mouseY = 0.0f, diffx = 0.0f, diffy = 0.0f;

};
