#pragma once
#include "BaseMaterial.h"

class PhongMaterial : public BaseMaterial
{
protected:
    //ID3DXEffect*        m_Effect;               // the shader associate effect file

    //-------- Material Parameters -------

	// Diffuse
	float				m_DiffuseCoefficient;
	D3DXVECTOR4			m_DiffuseColor;
	LPDIRECT3DTEXTURE9  m_Texture;

	// Ambient
	float				m_AmbientCoefficient;
	D3DXVECTOR4			m_AmbientColor;

	// Spec
	float				m_SpecularCoefficient;
	D3DXVECTOR4			m_SpecularColor;
    float               m_Shininess;            // specular power

	// Lighting
	D3DXVECTOR4			m_LightColor;

    //---------- Shader Handles ----------
    // Generic shader handles
	D3DXHANDLE			m_World;
	D3DXHANDLE			m_gWInvTrans;
	D3DXHANDLE			m_TechniqueHandle;

	// Diffuse Handles
	D3DXHANDLE			m_DiffuseCoefHandle;
    D3DXHANDLE          m_DiffuseColHandle;
	D3DXHANDLE			m_DiffuseTextureHandle;

	// Ambient Handles
	D3DXHANDLE			m_AmbientCoefHandle;
	D3DXHANDLE			m_AmbientColHandle;

	// Specular Handles
	D3DXHANDLE			m_SpecularCoefHandle;
    D3DXHANDLE          m_SpecularColHandle;
    D3DXHANDLE          m_ShininessHandle;

	// Lighting Information Handles
    D3DXHANDLE          m_LightPosWHandle;		// Position (spot/point) / Direction (directional)
    D3DXHANDLE          m_ViewerPosWHandle;
	D3DXHANDLE			m_LightColorHandle;

public:
	PhongMaterial(void);
	~PhongMaterial(void);

	void InitEffect ( IDirect3DDevice9* gd3dDevice );
	void Render( D3DXMATRIX& worldMat, D3DXMATRIX& viewMat, D3DXMATRIX& projMat );
};
//=============================================================================
