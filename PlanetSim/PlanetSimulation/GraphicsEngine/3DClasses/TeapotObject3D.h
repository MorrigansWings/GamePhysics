#pragma once

#include "BaseObject3D.h"

class TeapotObject3D : public BaseObject3D
{
public:
	TeapotObject3D(void);
	~TeapotObject3D(void);

	virtual void Create( IDirect3DDevice9* gd3dDevice );
};

