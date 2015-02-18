//=============================================================================
//                              BaseMaterial
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that contains the most intrinsic parameters to implement per model
// lighting / shaders effects.
//=============================================================================
#include "BaseMaterial.h"
//=============================================================================
BaseMaterial::BaseMaterial(void)
{
    m_Effect = NULL;
}

//-----------------------------------------------------------------------------
// Relase shader, blah...
BaseMaterial::~BaseMaterial(void)
{
}

//-----------------------------------------------------------------------------
// Need to add here a code that will associate with your shader parameters and 
// register them.
void BaseMaterial::ConnectToEffect( ID3DXEffect* effect )
{
	m_Effect = effect;
}

//=============================================================================
void BaseMaterial::InitEffect ( IDirect3DDevice9* gd3dDevice )
{ 
	m_materialColor = D3DXVECTOR4(0.5, 0.5, 0.5, 1.0);
	D3DXCreateTextureFromFile( gd3dDevice, "Textures/rock.jpg", &m_materialTexture);

	m_TextureToggle = false;
	m_WireframeToggle = false;

	m_gWVP					= m_Effect->GetParameterByName(0, "gWVP");
	m_MaterialColorHandle	= m_Effect->GetParameterByName(0, "materialColor");
	m_TextureHandle			= m_Effect->GetParameterByName(0, "matTexture");
	m_TextureUseHandle		= m_Effect->GetParameterByName(0, "useTexture");
}

void BaseMaterial::Render( D3DXMATRIX& worldMat, D3DXMATRIX& viewMat, D3DXMATRIX& projMat )
{
	// calculate transformations
	m_WorldMat = worldMat;
	m_ViewProjectionMat = viewMat * projMat;

	int useTex = 0;
	if (m_TextureToggle) useTex = 1;

	HR(m_Effect->SetMatrix(m_gWVP, &(m_WorldMat * m_ViewProjectionMat)));
	HR(m_Effect->SetValue(m_MaterialColorHandle, &m_materialColor, sizeof(D3DXVECTOR4)));
	HR(m_Effect->SetTexture(m_TextureHandle, m_materialTexture));
	HR(m_Effect->SetValue(m_TextureUseHandle, &useTex, sizeof(int)));
}

void BaseMaterial::Begin()
{
	if( m_WireframeToggle )
	{
		UINT numPasses = 0;
		HR(m_Effect->Begin(&numPasses,0));
		HR(m_Effect->BeginPass(1));
	}
	else
	{
		UINT numPasses = 0;
		HR(m_Effect->Begin(&numPasses,0));
		HR(m_Effect->BeginPass(0));
	}
}

void BaseMaterial::End()
{
	HR(m_Effect->EndPass());
	HR(m_Effect->End());
}