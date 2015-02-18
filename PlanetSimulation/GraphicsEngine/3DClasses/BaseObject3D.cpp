//=============================================================================
//                              BaseObject3D
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendergin via Vertex and Index buffer
//=============================================================================
#include "BaseObject3D.h"
#include "../Vertex.h"
#include "../GfxStats.h"
//=============================================================================
BaseObject3D::BaseObject3D(void)
{
    D3DXMatrixIdentity(&m_World);
}

//-----------------------------------------------------------------------------
BaseObject3D::~BaseObject3D(void)
{
    ReleaseCOM(m_Mesh);
}

//-----------------------------------------------------------------------------
void BaseObject3D::Render( IDirect3DDevice9* gd3dDevice,
	D3DXMATRIX& view, D3DXMATRIX& projection )
{
    // Update the statistics singlton class
	GfxStats::GetInstance()->addVertices(m_Mesh->GetNumVertices());
    GfxStats::GetInstance()->addTriangles(m_Mesh->GetNumFaces());

    // Set the buffers and format
	HR(gd3dDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VertexPos)));
	HR(gd3dDevice->SetIndices(m_IndexBuffer));
	HR(gd3dDevice->SetVertexDeclaration(VertexPos::Decl));

	m_Material->Render( m_World, view, projection );

	m_Material->Begin();
    // Send to render
	HR(m_Mesh->DrawSubset(0));
	m_Material->End();
}

void BaseObject3D::generateTangents(void)
{
	// clone mesh 
	D3DVERTEXELEMENT9 decl[MAXD3DDECLLENGTH];
	UINT numElements;
	VertexPos::Decl->GetDeclaration( decl, &numElements);

	ID3DXMesh* temp = 0;
	HR(m_Mesh->CloneMesh(D3DXMESH_SYSTEMMEM, decl, gd3dDevice, &temp));

	HR(D3DXComputeTangentFrameEx(
		temp,
		D3DDECLUSAGE_TEXCOORD, 0,
		D3DDECLUSAGE_BINORMAL, 0,
		D3DDECLUSAGE_TANGENT, 0,
		D3DDECLUSAGE_NORMAL, 0,
		0,
		0,
		0.01f, 0.25f, 0.01f,
		&m_Mesh,
		0));

	ReleaseCOM(temp);
}

//-----------------------------------------------------------------------------
void BaseObject3D::Translate( float dx, float dy, float dz )
{
	D3DXMatrixTranslation(&m_World, dx, dy, dz);
}

//-----------------------------------------------------------------------------
void BaseObject3D::Rotate( D3DXMATRIX rotationMatrix )
{
	D3DXMatrixIdentity(&m_World);
	D3DXMatrixMultiply(&m_World, &rotationMatrix, &m_World);
}
//=============================================================================
