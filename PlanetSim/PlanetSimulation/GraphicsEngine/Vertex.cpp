//=============================================================================
//              Adopted from Franc Luna's CubeDemo sample project.
//
// Please use this file to add classes / inherit and create various vertex classes
//=============================================================================
#include "Vertex.h"
#include "d3dUtil.h"
//=============================================================================
// Initialize static variables.
IDirect3DVertexDeclaration9* VertexPos::Decl = 0;
//=============================================================================
void InitAllVertexDeclarations()
{
	// VertexPos
	D3DVERTEXELEMENT9 VertexPosElements[] =
	{
		{0,	 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0,	12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{0, 20, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,	  0},
		{0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0},
		{0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
		D3DDECL_END()
	};

	HR(gd3dDevice->CreateVertexDeclaration(VertexPosElements, &VertexPos::Decl));
}
//-----------------------------------------------------------------------------
void DestroyAllVertexDeclarations()
{
	ReleaseCOM(VertexPos::Decl);
}
//=============================================================================