#include "BoxObject3D.h"
#include "../Vertex.h"

BoxObject3D::BoxObject3D(float _width, float _height, float _depth)
{
	width = _width;
	height = _height;
	depth = _depth;
}

BoxObject3D::~BoxObject3D(void)
{
}

void BoxObject3D::Create( IDirect3DDevice9* gd3dDevice )
{
	// create a mesh using D3DXCreate()
	HR(D3DXCreateBox(gd3dDevice, width, height, depth, &m_Mesh, NULL));

	// generate tex coords
	generateTextureCoordinates();
	generateTangents();

	// get the vertex and index buffers
	HR(m_Mesh->GetVertexBuffer(&m_VertexBuffer));
	HR(m_Mesh->GetIndexBuffer(&m_IndexBuffer));
}

void BoxObject3D::generateTextureCoordinates()
{
	// clone mesh 
	D3DVERTEXELEMENT9 decl[MAXD3DDECLLENGTH];
	UINT numElements;
	VertexPos::Decl->GetDeclaration( decl, &numElements);

	ID3DXMesh* temp = 0;
	HR(m_Mesh->CloneMesh(D3DXMESH_SYSTEMMEM, decl, gd3dDevice, &temp));
	ReleaseCOM(m_Mesh);

	// lock the vertex buffer and assign UV values
	VertexPos* vertices = 0;
	HR(temp->LockVertexBuffer(0, (void**)&vertices));
	for (UINT i = 0; i < temp->GetNumVertices(); i+=4)
	{
		vertices[i].uv_pos.x = 0.0f;
		vertices[i].uv_pos.y = 0.0f;

		vertices[i+1].uv_pos.x = 0.0f;
		vertices[i+1].uv_pos.y = 1.0f;

		vertices[i+2].uv_pos.x = 1.0f;
		vertices[i+2].uv_pos.y = 1.0f;

		vertices[i+3].uv_pos.x = 1.0f;
		vertices[i+3].uv_pos.y = 0.0f;
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