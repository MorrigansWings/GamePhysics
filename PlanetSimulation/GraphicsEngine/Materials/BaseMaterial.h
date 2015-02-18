//=============================================================================
//                              BaseMaterial
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that contains the most intrinsic parameters to implement per model
// lighting / shaders effects.
//=============================================================================
#pragma once
#include "../d3dApp.h"
//=============================================================================
class BaseMaterial
{
protected:
	ID3DXEffect* m_Effect; 

	D3DXMATRIX  m_WorldMat;
    D3DXMATRIX  m_ViewProjectionMat;

	bool m_TextureToggle;
	bool m_WireframeToggle;

	D3DXHANDLE m_gWVP;
	D3DXHANDLE m_TextureUseHandle;

private:
	D3DXVECTOR4 m_materialColor;
	LPDIRECT3DTEXTURE9 m_materialTexture;
	
	D3DXHANDLE m_TextureHandle;
	D3DXHANDLE m_MaterialColorHandle;

public:
    BaseMaterial(void);
    virtual ~BaseMaterial(void);

	virtual void InitEffect ( IDirect3DDevice9* gd3dDevice );
	void ConnectToEffect( ID3DXEffect* effect );

	void Begin ();
	virtual void Render( D3DXMATRIX& worldMat, D3DXMATRIX& viewMat, D3DXMATRIX& projMat );
	void End ();

	inline ID3DXEffect* getEffect(void) { return m_Effect; };
	inline void ToggleTexture() { m_TextureToggle = !m_TextureToggle; };
	inline void ToggleWireframe() { m_WireframeToggle = !m_WireframeToggle; };
};
//=============================================================================
