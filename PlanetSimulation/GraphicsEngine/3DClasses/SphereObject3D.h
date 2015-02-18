//=============================================================================
// SphereObject3D
// Jak Tiano, 2014
//
// Builds vertex/index buffer for a sphere based on radius/facets input
//=============================================================================
#ifndef _SPHERE_OBJECT_3D_H
#define _SPHERE_OBJECT_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "BaseObject3D.h"
//=============================================================================
class SphereObject3D : public BaseObject3D
{	
public:
	SphereObject3D( float radius, int sideFacetsNum, int heightFacetsNum );
	~SphereObject3D(void);

	virtual void Create( IDirect3DDevice9* gd3dDevice );
	void Render( IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection );

protected:
	float m_radius;
	int   m_sideFacetsNum;
	int   m_heightFacetsNum;

	void generateTextureCoordinates();
};
//=============================================================================
#endif // _SPHERE_OBJECT_3D_H
