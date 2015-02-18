//=============================================================================
//                              BaseObject3D
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendergin via Vertex and Index buffer
//=============================================================================
#ifndef _BASE_OBJECT_3D_H
#define _BASE_OBJECT_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include <d3dx9.h>

#include "../d3dUtil.h"
#include "../Materials/BaseMaterial.h"
//=============================================================================
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
//=============================================================================
class BaseObject3D
{
protected:	
	int							m_numVerticies;
	int							m_numTriangles;

    D3DXMATRIX                  m_World;
	LPD3DXMESH					m_Mesh;
	BaseMaterial*				m_Material;

	IDirect3DVertexBuffer9*     m_VertexBuffer;
	IDirect3DIndexBuffer9*      m_IndexBuffer;

public:
    BaseObject3D(void);
    ~BaseObject3D(void);

	inline BaseMaterial* GetMaterial(void) { return m_Material; };
	inline void SetMaterial( BaseMaterial* material ) { m_Material = material; };

	inline D3DXMATRIX getWorldMatrix(void) { return m_World; };

    // Replace or add to the following code as you progress with the material
    virtual void Create( IDirect3DDevice9* gd3dDevice ) = 0;
	virtual void Update( float dt ) {};
    virtual void Render( IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection );

	void generateTangents(void);

	// Modifying World Matrix
	void Translate( float dx, float dy, float dz );
	void Rotate( D3DXMATRIX rotationMatrix );
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H

