#pragma once

#include "BaseObject3D.h"

class ConeObject3D : public BaseObject3D
{
public:
	ConeObject3D( float height, float radius, int sideFacetsNum, int heightFacetsNum );
	~ConeObject3D(void);

	virtual void Create( IDirect3DDevice9* gd3dDevice );

protected:
	float m_height;
	float m_radius;
	int   m_sideFacetsNum;
	int   m_heightFacetsNum;

	void generateTextureCoordinates();
	void Render( IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection );
};
