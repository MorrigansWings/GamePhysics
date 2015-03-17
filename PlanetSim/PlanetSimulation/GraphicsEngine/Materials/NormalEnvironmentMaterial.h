#pragma once
#include "NormalMaterial.h"

class NormalEnvironmentMaterial : public NormalMaterial
{
protected:
	LPDIRECT3DCUBETEXTURE9  m_EnvironmentMapTexture;
	D3DXHANDLE m_EnvironmentMapTextureHandle;

	bool m_EnvironmentToggle;
	D3DXHANDLE m_EnvironmentToggleHandle;

	float m_Reflectivity;
	D3DXHANDLE m_ReflectivityHandle;

public:
	NormalEnvironmentMaterial(void);
	~NormalEnvironmentMaterial(void);

	void InitEffect ( IDirect3DDevice9* gd3dDevice );
	void Render( D3DXMATRIX& worldMat, D3DXMATRIX& viewMat, D3DXMATRIX& projMat );
	inline void ToggleEnvironment() { m_EnvironmentToggle = !m_EnvironmentToggle; };
};
