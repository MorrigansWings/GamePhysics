#ifndef VERTEX_H
#define VERTEX_H

#pragma once

#include <iostream>
#include "Vectors.h"

/***********************************************************************/
// Position-only vertex struct declaration
struct VertexP
{
	Vector3 position;

	VertexP(const Vector3 &pos)
		:position(pos)
	{}
};

/***********************************************************************/
// Vertex struct declaration including position and color info
struct VertexPC
{
	Vector3 position;
	Vector4 color;

	VertexPC(const Vector3 &pos, const Vector4 &col)
		:position(pos)
		, color(col)
	{}
};

/***********************************************************************/
// Vertex struct declaration including position and texture information
struct VertexPT
{
	Vector3 position;
	Vector2 texture;

	VertexPT(const Vector3 &pos, const Vector2 &tex)
		:position(pos)
		, texture(tex)
	{}
};

/***********************************************************************/
// Vertex struct declaration including position, texture and normal information
struct VertexPTN
{
	Vector3 position;
	Vector2 texture;
	Vector3 normal;

	VertexPTN(const Vector3 &pos, const Vector2 &tex, const Vector3 &norm)
		:position(pos)
		, texture(tex)
		, normal(norm)
	{}
};

#endif