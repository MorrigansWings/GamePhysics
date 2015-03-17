#include "TeapotObject3D.h"


TeapotObject3D::TeapotObject3D(void)
{
}


TeapotObject3D::~TeapotObject3D(void)
{
}

void TeapotObject3D::Create( IDirect3DDevice9* gd3dDevice )
{
	// create mesh with D3DXCreate function
	D3DXCreateTeapot( gd3dDevice, &m_Mesh, NULL );

	// get the vertex and index buffers
	HR(m_Mesh->GetVertexBuffer(&m_VertexBuffer));
	HR(m_Mesh->GetIndexBuffer(&m_IndexBuffer));
}