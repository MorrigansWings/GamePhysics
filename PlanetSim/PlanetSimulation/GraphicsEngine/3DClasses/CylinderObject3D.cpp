//=============================================================================
// CylinderObject3D
// Jak Tiano, 2014
//
// Builds vertex/index buf for a cylinder based on height/radius/facets input
//=============================================================================
#include "CylinderObject3D.h"
#include "../Vertex.h"
#include "../GfxStats.h"
#include <math.h>
//=============================================================================
CylinderObject3D::CylinderObject3D( float height, float radius, int sideFacetsNum, int heightFacetsNum )
{
	m_height = height;
	m_radius = radius;
	m_sideFacetsNum = sideFacetsNum;
	m_heightFacetsNum = heightFacetsNum;
}

//-----------------------------------------------------------------------------
CylinderObject3D::~CylinderObject3D(void)
{
}

//-----------------------------------------------------------------------------
void CylinderObject3D::Create( IDirect3DDevice9* gd3dDevice )
{
	// create a mesh using D3DXCreate()
	HR(D3DXCreateCylinder(gd3dDevice, m_radius, m_radius, m_height, m_sideFacetsNum, m_heightFacetsNum, &m_Mesh, NULL));

	// generate tex coords
	generateTextureCoordinates();

	// get the vertex and index buffers
	HR(m_Mesh->GetVertexBuffer(&m_VertexBuffer));
	HR(m_Mesh->GetIndexBuffer(&m_IndexBuffer));
}

void CylinderObject3D::generateTextureCoordinates()
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

	D3DXVECTOR3 maxPoint(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	D3DXVECTOR3 minPoint(FLT_MAX, FLT_MAX, FLT_MAX);

	for (UINT i = 0; i < temp->GetNumVertices(); ++i)
	{
		D3DXVec3Maximize(&maxPoint, &maxPoint, &vertices[i].pos);
		D3DXVec3Minimize(&minPoint, &minPoint, &vertices[i].pos);
	}

	float a = minPoint.x;
	float b = maxPoint.x;
	float h = b-a;

	for (UINT i = 0; i < temp->GetNumVertices(); ++i)
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		x = vertices[i].pos.x;
		y = vertices[i].pos.z;
		z = vertices[i].pos.y;

		float theta = atan2f(z, x);
		float y2	= y-b;

		float u = theta / (2.0f*D3DX_PI);
		float v = y2	/ -h;

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
	HR(temp->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, decl, gd3dDevice, &m_Mesh));
	ReleaseCOM(temp);
}

void CylinderObject3D::Render( IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection )
{
	HR(gd3dDevice->SetRenderState(D3DRS_WRAP0, D3DWRAPCOORD_0));
	this->BaseObject3D::Render(gd3dDevice, view, projection);
	HR(gd3dDevice->SetRenderState(D3DRS_WRAP0, 0));
}

//=============================================================================
