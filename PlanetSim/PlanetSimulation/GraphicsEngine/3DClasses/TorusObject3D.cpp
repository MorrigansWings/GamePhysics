#include "TorusObject3D.h"


TorusObject3D::TorusObject3D( float _innerRadius, float _outerRadius, int _sides, int _rings)
{
	innerRadius = _innerRadius;
	outerRadius = _outerRadius;
	sides = _sides;
	rings = _rings;
}


TorusObject3D::~TorusObject3D(void)
{
}

void TorusObject3D::Create( IDirect3DDevice9* gd3dDevice )
{
	// create a mesh using D3DXCreate()
	D3DXCreateTorus(gd3dDevice, innerRadius, outerRadius, sides, rings, &m_Mesh, NULL);

	// get the vertex and index buffers
	HR(m_Mesh->GetVertexBuffer(&m_VertexBuffer));
	HR(m_Mesh->GetIndexBuffer(&m_IndexBuffer));
}