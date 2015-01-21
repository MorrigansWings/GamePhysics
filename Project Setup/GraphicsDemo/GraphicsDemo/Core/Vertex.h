#ifndef VERTEX_H
#define VERTEX_H

#include "glm\glm.hpp"

// Position-only vertex struct declaration
struct VertexP
{
public:
	VertexP()
		:position(glm::vec3(0.0f, 0.0f, 0.0f))
	{}

	VertexP(const float x, const float y, const float z)
		:position(glm::vec3(x, y, z))
	{}

	VertexP(const glm::vec3 &pos)
		:position(pos)
	{}

	void setPosition(const float x, const float y, const float z) { position = glm::vec3(x, y, z); }
	void setPosition(const glm::vec3 &pos) { position = pos; }

	void setPositionX(const float x) { position.x = x; }
	void setPositionY(const float y) { position.y = y; }
	void setPositionZ(const float z) { position.z = z; }
	const glm::vec3 getPosition() { return position; }
	const float getPositionX() { return position.x; }
	const float getPositionY() { return position.y; }
	const float getPositionZ() { return position.z; }

private:
	glm::vec3 position;
};

// Vertex struct declaration including position and UV information
struct VertexPT
{
public:
	VertexPT()
		:position(glm::vec3(0.0f, 0.0f, 0.0f))
		, texture(glm::vec2(0.0f, 0.0f))
	{}

	VertexPT(const float x, const float y, const float z)
		:position(glm::vec3(x, y, z))
		, texture(glm::vec2(0.0f, 0.0f))
	{}

	VertexPT(const glm::vec3 &pos)
		:position(pos)
		, texture(glm::vec2(0.0f, 0.0f))
	{}

	VertexPT(const glm::vec3 &pos, const glm::vec2 &tex)
		:position(pos)
		, texture(tex)
	{}

	void setPosition(const float x, const float y, const float z) { position = glm::vec3(x, y, z); }
	void setPosition(const glm::vec3 &pos) { position = pos; }
	void setPositionX(const float x) { position.x = x; }
	void setPositionY(const float y) { position.y = y; }
	void setPositionZ(const float z) { position.z = z; }
	const glm::vec3 getPosition() { return position; }
	const float getPositionX() { return position.x; }
	const float getPositionY() { return position.y; }
	const float getPositionZ() { return position.z; }

	void setUV(const float u, const float v) { texture = glm::vec2(u, v); }
	void setUV(const glm::vec2 &tex) { texture = tex; }
	void setTextureU(const float u) { texture.x = u; }
	void setTextureV(const float v) { texture.y = v; }
	const glm::vec2 getUV() { return texture; }
	const float getTextureU() { return texture.x; }
	const float getTextureV() { return texture.y; }

private:
	glm::vec3 position;
	glm::vec2 texture;
};


// Vertex struct declaration including position, UV and normal information
struct VertexPTN
{
public:
	VertexPTN()
		:position(glm::vec3(0.0f, 0.0f, 0.0f))
		, texture(glm::vec2(0.0f, 0.0f))
		, normal(glm::vec3(0.0f, 0.0f, 0.0f))
	{}

	VertexPTN(const float x, const float y, const float z)
		:position(glm::vec3(x, y, z))
		, texture(glm::vec2(0.0f, 0.0f))
		, normal(glm::vec3(0.0f, 0.0f, 0.0f))
	{}

	VertexPTN(const glm::vec3 &pos)
		:position(pos)
		, texture(glm::vec2(0.0f, 0.0f))
		, normal(glm::vec3(0.0f, 0.0f, 0.0f))
	{}

	VertexPTN(const glm::vec3 &pos, const glm::vec2 &tex)
		:position(pos)
		, texture(tex)
		, normal(glm::vec3(0.0f, 0.0f, 0.0f))
	{}

	VertexPTN(const glm::vec3 &pos, const glm::vec2 &tex, const glm::vec3 &norm)
		:position(pos)
		, texture(tex)
		, normal(norm)
	{}

	void setPosition(const float x, const float y, const float z) { position = glm::vec3(x, y, z); }
	void setPosition(const glm::vec3 &pos) { position = pos; }
	void setPositionX(const float x) { position.x = x; }
	void setPositionY(const float y) { position.y = y; }
	void setPositionZ(const float z) { position.z = z; }
	const glm::vec3 getPosition() { return position; }
	const float getPositionX() { return position.x; }
	const float getPositionY() { return position.y; }
	const float getPositionZ() { return position.z; }

	void setUV(const float u, const float v) { texture = glm::vec2(u, v); }
	void setUV(const glm::vec2 &tex) { texture = tex; }
	void setTextureU(const float u) { texture.x = u; }
	void setTextureV(const float v) { texture.y = v; }
	const glm::vec2 getUV() { return texture; }
	const float getTextureU() { return texture.x; }
	const float getTextureV() { return texture.y; }

	void setNormal(const float x, const float y, const float z) { normal = glm::vec3(x, y, z); }
	void setNormal(const glm::vec3 &norm) { normal = norm; }
	const glm::vec3 getNormal() { return normal; }
	const float getNormalX() { return normal.x; }
	const float getNormalY() { return normal.y; }
	const float getNormalZ() { return normal.z; }

private:
	glm::vec3 position;
	glm::vec2 texture;
	glm::vec3 normal;


};

#endif