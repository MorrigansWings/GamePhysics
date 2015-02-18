#include "PhongMaterial.h"
#include "BaseMaterial.h"

PhongMaterial::PhongMaterial(void)
{
    m_Effect = NULL;
}

//-----------------------------------------------------------------------------
// Release shader, blah...
PhongMaterial::~PhongMaterial(void)
{
}

//=============================================================================
void PhongMaterial::InitEffect ( IDirect3DDevice9* gd3dDevice )
{
	// load texture from file
	m_Texture = 0;
	D3DXCreateTextureFromFile( gd3dDevice, "Textures/rock.jpg", &m_Texture);
	m_DiffuseTextureHandle	 = m_Effect->GetParameterByName(0, "DiffuseTexture");
	m_TextureUseHandle		= m_Effect->GetParameterByName(0, "useTexture");
	
	// set color
	m_DiffuseCoefficient = 0.75f;
	m_DiffuseColor		 = D3DXVECTOR4(1.0, 1.0, 1.0, 1.0);

	m_AmbientCoefficient = 0.05f;
	m_AmbientColor		 = D3DXVECTOR4(1.0, 1.0, 1.0, 1.0);

	m_SpecularCoefficient= 0.35f;
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

	m_LightPosWHandle	 = m_Effect->GetParameterByName(0, "gLightVecW");      // Position (spot/point) / Direction (directional)
	m_ViewerPosWHandle   = m_Effect->GetParameterByName(0, "gViewerPos");
	m_LightColorHandle	 = m_Effect->GetParameterByName(0, "gLightColor");
	
	HR(m_Effect->SetTechnique(m_TechniqueHandle));

	m_WireframeToggle = false;
	m_TextureToggle = true;
}

void PhongMaterial::Render( D3DXMATRIX& worldMat, D3DXMATRIX& viewMat, D3DXMATRIX& projMat )
{
	// calculate transformations
	m_WorldMat = worldMat;
	m_ViewProjectionMat = viewMat * projMat;

	// world inverse transpose
	D3DXMATRIX worldInverseTranspose;
	D3DXMatrixInverse(&worldInverseTranspose, 0, &m_WorldMat);
	//D3DXMatrixTranspose(&worldInverseTranspose, &worldInverseTranspose);

	// get viewer pos from matrix
	D3DXMATRIX tempView(viewMat);
	D3DXVECTOR3 vPos;
	vPos.x = -viewMat._41;
	vPos.y = -viewMat._42;
	vPos.z = -viewMat._43;
	D3DXMatrixTranspose(&tempView, &tempView);
	D3DXVec3TransformNormal(&vPos, &vPos, &tempView);

	int useTex = 0;
	if (m_TextureToggle) useTex = 1;

	// set shader parameters
	HR(m_Effect->SetMatrix(m_World, &m_WorldMat));
	HR(m_Effect->SetMatrix(m_gWVP, &(m_WorldMat * m_ViewProjectionMat)));
	HR(m_Effect->SetMatrix(m_gWInvTrans, &worldInverseTranspose));

	HR(m_Effect->SetTexture(m_DiffuseTextureHandle, m_Texture));
	HR(m_Effect->SetValue(m_TextureUseHandle, &useTex, sizeof(int)));

	HR(m_Effect->SetValue(m_DiffuseCoefHandle, &m_DiffuseCoefficient, sizeof(float)));
	HR(m_Effect->SetValue(m_DiffuseColHandle, &m_DiffuseColor, sizeof(D3DXVECTOR4)));

	HR(m_Effect->SetValue(m_AmbientCoefHandle, &m_AmbientCoefficient, sizeof(float)));
	HR(m_Effect->SetValue(m_AmbientColHandle, &m_AmbientColor, sizeof(D3DXVECTOR4)));

	HR(m_Effect->SetValue(m_SpecularCoefHandle, &m_SpecularCoefficient, sizeof(float)));
	HR(m_Effect->SetValue(m_SpecularColHandle, &m_SpecularColor, sizeof(D3DXVECTOR4)));
	HR(m_Effect->SetValue(m_ShininessHandle, &m_Shininess, sizeof(float)));

	HR(m_Effect->SetValue(m_LightPosWHandle, D3DXVECTOR3(1.0, 1.0, -1.0), sizeof(D3DXVECTOR3)));
	HR(m_Effect->SetValue(m_ViewerPosWHandle, &vPos, sizeof(D3DXVECTOR3)));
	HR(m_Effect->SetValue(m_LightColorHandle, &m_LightColor, sizeof(D3DXVECTOR4)));
}