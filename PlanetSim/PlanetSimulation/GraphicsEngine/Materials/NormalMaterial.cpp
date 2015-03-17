#include "NormalMaterial.h"


NormalMaterial::NormalMaterial(void)
{
	m_Effect = NULL;
}

NormalMaterial::~NormalMaterial(void)
{
}

void NormalMaterial::InitEffect ( IDirect3DDevice9* gd3dDevice )
{
	// load texture from file
	m_Texture = 0;
	D3DXCreateTextureFromFile( gd3dDevice, "Textures/rock.jpg", &m_Texture);
	m_DiffuseTextureHandle	 = m_Effect->GetParameterByName(0, "DiffuseTexture");
	m_TextureUseHandle		= m_Effect->GetParameterByName(0, "useTexture");
	
	// load normal map texture from file
	m_NormalMapTexture = 0;
	D3DXCreateTextureFromFile( gd3dDevice, "Textures/upholstry.png", &m_NormalMapTexture );

	// set color
	m_DiffuseCoefficient = 0.75f;
	m_DiffuseColor		 = D3DXVECTOR4(1.0, 1.0, 1.0, 1.0);

	m_AmbientCoefficient = 0.05f;
	m_AmbientColor		 = D3DXVECTOR4(1.0, 1.0, 1.0, 1.0);

	m_SpecularCoefficient= 0.20f;
	m_SpecularColor		 = D3DXVECTOR4(1.0, 1.0, 1.0, 1.0);
	m_Shininess			 = 64.0f;

	m_LightColor		 = D3DXVECTOR4(1.0, 1.0, 1.0, 1.0);

	// get all the D3DXHANDLEs
	m_World				 = m_Effect->GetParameterByName(0, "gWorld");
	m_gWVP				 = m_Effect->GetParameterByName(0, "gWVP");
	m_gWInvTrans		 = m_Effect->GetParameterByName(0, "gWorldInverseTranspose");
	m_TechniqueHandle	 = m_Effect->GetTechniqueByName("PhongTech");

	m_DiffuseCoefHandle  = m_Effect->GetParameterByName(0, "gDiffuseCoefficient");
	m_DiffuseColHandle	 = m_Effect->GetParameterByName(0, "gDiffuseMtrl");

	m_AmbientCoefHandle  = m_Effect->GetParameterByName(0, "gAmbientCoefficient");
	m_AmbientColHandle	 = m_Effect->GetParameterByName(0, "gAmbientMtrl");

	m_SpecularCoefHandle = m_Effect->GetParameterByName(0, "gSpecularCoefficient");
	m_SpecularColHandle  = m_Effect->GetParameterByName(0, "gSpecularMtrl");
	m_ShininessHandle	 = m_Effect->GetParameterByName(0, "gSpecularPower");

	m_LightPosWHandle	 = m_Effect->GetParameterByName(0, "gLightVecW");
	m_ViewerPosWHandle   = m_Effect->GetParameterByName(0, "gViewerPos");
	m_LightColorHandle	 = m_Effect->GetParameterByName(0, "gLightColor");
	
	m_NormalMapTextureHandle = m_Effect->GetParameterByName(0, "gNormalMap");
	m_NormalToggleHandle = m_Effect->GetParameterByName(0, "useNormal");

	HR(m_Effect->SetTechnique(m_TechniqueHandle));

	m_WireframeToggle = false;
	m_TextureToggle = true;
	m_NormalToggle = true;
}

void NormalMaterial::Render( D3DXMATRIX& worldMat, D3DXMATRIX& viewMat, D3DXMATRIX& projMat )
{
	int useNormal = 0;
	if (m_NormalToggle) useNormal = 1;
	this->PhongMaterial::Render( worldMat, viewMat, projMat );
	HR(m_Effect->SetTexture( m_NormalMapTextureHandle, m_NormalMapTexture ));
	HR(m_Effect->SetValue(m_NormalToggleHandle, &useNormal, sizeof(int)));
}