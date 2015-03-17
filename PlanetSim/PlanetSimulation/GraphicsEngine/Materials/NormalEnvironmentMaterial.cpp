#include "NormalEnvironmentMaterial.h"


NormalEnvironmentMaterial::NormalEnvironmentMaterial(void)
{
	m_Effect = NULL;
}

NormalEnvironmentMaterial::~NormalEnvironmentMaterial(void)
{
}

void NormalEnvironmentMaterial::InitEffect ( IDirect3DDevice9* gd3dDevice )
{
	// load texture from file
	m_Texture = 0;
	D3DXCreateTextureFromFile( gd3dDevice, "Textures/rock.jpg", &m_Texture);
	m_DiffuseTextureHandle	 = m_Effect->GetParameterByName(0, "DiffuseTexture");
	m_TextureUseHandle		= m_Effect->GetParameterByName(0, "useTexture");
	
	// load normal map texture from file
	m_NormalMapTexture = 0;
	D3DXCreateTextureFromFile( gd3dDevice, "Textures/checkers.png", &m_NormalMapTexture );

	// load cube map from file
	m_EnvironmentMapTexture = 0;
	D3DXCreateCubeTextureFromFile( gd3dDevice, "Textures/env.dds", &m_EnvironmentMapTexture );
	m_Reflectivity = 0.75;

	// set color
	m_DiffuseCoefficient = 0.75f;
	m_DiffuseColor		 = D3DXVECTOR4(1.0, 1.0, 1.0, 1.0);

	m_AmbientCoefficient = 0.05f;
	m_AmbientColor		 = D3DXVECTOR4(1.0, 1.0, 1.0, 1.0);

	m_SpecularCoefficient= 0.3f;
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

	m_EnvironmentMapTextureHandle = m_Effect->GetParameterByName(0, "gEnvMap");
	m_EnvironmentToggleHandle = m_Effect->GetParameterByName(0, "useEnvironment");
	m_ReflectivityHandle = m_Effect->GetParameterByName(0, "gReflectivity");

	HR(m_Effect->SetTechnique(m_TechniqueHandle));

	m_WireframeToggle = false;
	m_TextureToggle = true;
	m_NormalToggle = true;
	m_EnvironmentToggle = true;
}

void NormalEnvironmentMaterial::Render( D3DXMATRIX& worldMat, D3DXMATRIX& viewMat, D3DXMATRIX& projMat )
{
	int useEnvironment = 0;
	if (m_EnvironmentToggle) useEnvironment = 1;
	this->NormalMaterial::Render( worldMat, viewMat, projMat );
	HR(m_Effect->SetTexture( m_EnvironmentMapTextureHandle, m_EnvironmentMapTexture ));
	HR(m_Effect->SetValue( m_EnvironmentToggleHandle, &useEnvironment, sizeof(int)));
	HR(m_Effect->SetValue( m_ReflectivityHandle, &m_Reflectivity, sizeof(float)));
}