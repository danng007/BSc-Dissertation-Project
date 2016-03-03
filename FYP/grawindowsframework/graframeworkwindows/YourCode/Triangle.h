
#pragma once

#include "Object.h"

class Triangle : public Object
{
public:
    Triangle();
    ~Triangle();
    
    void Draw();
    void Update( const double& deltaTime );
	void HandleKey(int key, int state, int x, int y );

private:
    float xrot, yrot, zrot;
    float scale;
};
