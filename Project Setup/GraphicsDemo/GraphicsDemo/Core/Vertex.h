#ifndef VERTEX_H
#define VERTEX_H

#include "..\Dependencies\glm\glm\glm.hpp"
#include "..\Dependencies\glm\glm\gtx\string_cast.hpp"
#include <iostream>

/***********************************************************************/
// Position-only vertex struct declaration
struct VertexP
{
private:
	glm::vec3 position;

public:
	VertexP(const glm::vec3 &pos)
		:position(pos)
	{}
};

/***********************************************************************/
// Vertex struct declaration including position and color info
struct VertexPC
{
private:
	glm::vec3 position;
	glm::vec4 color;

public:
	VertexPC(const glm::vec3 &pos, const glm::vec4 &col)
		:position(pos)
		, color(col)
	{}
};

/***********************************************************************/
// Vertex struct declaration including position and texture information
struct VertexPT
{
private:
	glm::vec3 position;
	glm::vec2 texture;

public:
	VertexPT(const glm::vec3 &pos, const glm::vec2 &tex)
		:position(pos)
		, texture(tex)
	{}
};

/***********************************************************************/
// Vertex struct declaration including position, texture and normal information
struct VertexPTN
{
private:
	glm::vec3 position;
	glm::vec2 texture;
	glm::vec3 normal;

public:
	VertexPTN(const glm::vec3 &pos, const glm::vec2 &tex, const glm::vec3 &norm)
		:position(pos)
		, texture(tex)
		, normal(norm)
	{}
};

#endif