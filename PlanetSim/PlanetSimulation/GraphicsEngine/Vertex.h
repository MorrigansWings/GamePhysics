//=============================================================================
//              Adopted from Franc Luna's CubeDemo sample project.
//
// Please use this file to add classes / inherit and create various vertex classes
//=============================================================================
#ifndef VERTEX_H
#define VERTEX_H
//=============================================================================
#include <d3dx9.h>
//=============================================================================
// Call in constructor and destructor, respectively, of derived application class.
void InitAllVertexDeclarations();
void DestroyAllVertexDeclarations();
//=============================================================================
struct VertexPos
{
	//VertexPos():pos(0.0f, 0.0f, 0.0f){}
	//VertexPos(float x, float y, float z):pos(x,y,z){}
	//VertexPos(const D3DXVECTOR3& v):pos(v){}

	D3DXVECTOR3 pos;
	D3DXVECTOR2 uv_pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR3 tangent;
	D3DXVECTOR3 binormal;

	static IDirect3DVertexDeclaration9* Decl;
};
//=============================================================================
#endif // VERTEX_H