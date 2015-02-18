#pragma once

#include "PhongMaterial.h"

class NormalMaterial : public PhongMaterial
{
protected:
	LPDIRECT3DTEXTURE9  m_NormalMapTexture;
	D3DXHANDLE m_NormalMapTextureHandle;

	bool m_NormalToggle;
	D3DXHANDLE m_NormalToggleHandle;

public:
	NormalMaterial(void);
	~NormalMaterial(void);

	void InitEffect ( IDirect3DDevice9* gd3dDevice );
	void Render( D3DXMATRIX& worldMat, D3DXMATRIX& viewMat, D3DXMATRIX& projMat );

	inline void ToggleNormal() { m_NormalToggle = !m_NormalToggle; };
};
