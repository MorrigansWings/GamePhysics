#pragma once

#include "BaseObject3D.h"

class TorusObject3D : public BaseObject3D
{
public:
	TorusObject3D( float _innerRadius, float _outerRadius, int _sides, int _rings);
	~TorusObject3D(void);
	
	virtual void Create( IDirect3DDevice9* gd3dDevice );

private:
	float innerRadius;
	float outerRadius;
	int sides;
	int rings;
};

