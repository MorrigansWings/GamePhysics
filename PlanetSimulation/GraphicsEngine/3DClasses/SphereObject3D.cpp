//=============================================================================
// SphereObject3D
// Jak Tiano, 2014
//
// Builds vertex/index buffer for a sphere based on radius/facets input
//=============================================================================
#include "SphereObject3D.h"
#include "../Vertex.h"
#include "../GfxStats.h"
#include <math.h>
//=============================================================================
SphereObject3D::SphereObject3D( float radius, int sideFacetsNum, int heightFacetsNum )
{
	m_radius = radius;
	m_sideFacetsNum = sideFacetsNum;
	m_heightFacetsNum = heightFacetsNum;
}

//-----------------------------------------------------------------------------
SphereObject3D::~SphereObject3D(void)
{
}

//-----------------------------------------------------------------------------
void SphereObject3D::Create( IDirect3DDevice9* gd3dDevice )
{
	// create a mesh using D3DXCreate()
	D3DXCreateSphere(gd3dDevice, m_radius, m_sideFacetsNum, m_heightFacetsNum, &m_Mesh, NULL);

	// generate tex coords
	generateTextureCoordinates();

	// get the vertex and index buffers
	HR(m_Mesh->GetVertexBuffer(&m_VertexBuffer));
	HR(m_Mesh->GetIndexBuffer(&m_IndexBuffer));
}


void SphereObject3D::generateTextureCoordinates()
{
	// clone mesh 
	D3DVERTEXELEMENT9 decl[MAXD3DDECLLENGTH];
	UINT numElements = 0;
	VertexPos::Decl->GetDeclaration( decl, &numElements);

	ID3DXMesh* temp = 0;
	HR(m_Mesh->CloneMesh(D3DXMESH_SYSTEMMEM, decl, gd3dDevice, &temp));
	ReleaseCOM(m_Mesh);

	// lock the vertex buffer and assign UV values
	VertexPos* vertices = 0;
	HR(temp->LockVertexBuffer(0, (void**)&vertices));
	for (UINT i = 0; i < temp->GetNumVertices(); ++i)
	{
		//algorithm adapted from Frank Luna
		//Convert to spherical coordinates
		D3DXVECTOR3 p = vertices[i].pos;
		p.y = vertices[i].pos.z;
		p.z = vertices[i].pos.y;

		float theta = atan2f(p.z, p.x);
		float phi	= acosf(p.y / sqrtf(p.x*p.x + p.y*p.y + p.z*p.z));

		float u = theta / (2.0f*D3DX_PI);
		float v = phi   / D3DX_PI;

		vertices[i].uv_pos.x = u;
		vertices[i].uv_pos.y = v;
	}
	HR(temp->UnlockVertexBuffer());

	//**********************************

	ID3DXMesh* clonedTemp = 0;
	HR(temp->CloneMesh(D3DXMESH_MANAGED, decl, gd3dDevice, &clonedTemp));
	ReleaseCOM(temp);

	HR(D3DXComputeTangentFrameEx(
		clonedTemp, D3DDECLUSAGE_TEXCOORD, 0,
		D3DDECLUSAGE_BINORMAL, 0,
		D3DDECLUSAGE_TANGENT, 0,
		D3DDECLUSAGE_NORMAL, 0,
		0,
		0,
		0.01f, 0.25f, 0.01f,
		&temp,
		0));

	ReleaseCOM(clonedTemp);

	// clone mesh to m_Mesh
	// Removed D3DXMESH_WRITEONLY from first parameter
	HR(temp->CloneMesh(D3DXMESH_MANAGED, decl, gd3dDevice, &m_Mesh));
	ReleaseCOM(temp);
}

void SphereObject3D::Render( IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection )
{
	HR(gd3dDevice->SetRenderState(D3DRS_WRAP0, D3DWRAPCOORD_0));
	this->BaseObject3D::Render(gd3dDevice, view, projection);
	HR(gd3dDevice->SetRenderState(D3DRS_WRAP0, 0));
}
//=============================================================================
