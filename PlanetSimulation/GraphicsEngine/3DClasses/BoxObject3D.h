#pragma once

#include "BaseObject3D.h"

class BoxObject3D : public BaseObject3D
{
public:
	BoxObject3D(float _width, float _height, float _depth);
	~BoxObject3D(void);

	virtual void Create( IDirect3DDevice9* gd3dDevice );

private:
	float width, height, depth;

	void generateTextureCoordinates();
};
