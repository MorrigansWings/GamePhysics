//=============================================================================
// CylinderObject3D
// Jak Tiano, 2014
//
// Builds vertex/index buf for a cylinder based on height/radius/facets input
//=============================================================================
#ifndef _CYLINDER_OBJECT_3D_H
#define _CYLINDER_OBJECT_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "BaseObject3D.h"
//=============================================================================
class CylinderObject3D : public BaseObject3D
{
public:
	CylinderObject3D( float height, float radius, int sideFacetsNum, int heightFacetsNum );
	~CylinderObject3D(void);

	virtual void Create( IDirect3DDevice9* gd3dDevice );

protected:
	float m_height;
	float m_radius;
	int   m_sideFacetsNum;
	int   m_heightFacetsNum;

	void generateTextureCoordinates();
	void Render( IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection );
};
//=============================================================================
#endif //_CYLINDER_OBJECT_3D_H