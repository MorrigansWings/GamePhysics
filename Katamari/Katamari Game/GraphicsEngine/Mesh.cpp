#include "Mesh.h"
#include "ResourceManager.h"

const MeshAttrID Mesh::ATTR_VERTEX         = 0;
const MeshAttrID Mesh::ATTR_NORMALS        = 1;
const MeshAttrID Mesh::ATTR_COLORS         = 2;
const MeshAttrID Mesh::ATTR_TEXTURE_COORDS = 3;

Mesh::~Mesh( void )
{
	if (m_VertBuffer != 0)
		glDeleteBuffers(1, &m_VertBuffer);

	if (m_NormBuffer != 0)
		glDeleteBuffers(1, &m_NormBuffer);

	if (m_ColorBuffer != 0)
		glDeleteBuffers(1, &m_ColorBuffer);

	if (m_TexCoordBuffer != 0)
		glDeleteBuffers(1, &m_TexCoordBuffer);

	if (m_VertArray != 0)
		glDeleteVertexArrays(1, &m_VertArray);
}

void Mesh::begin( const GLenum& primitiveType, const GLuint& numVerts )
{
	m_BatchDone = false;
	m_PrimitiveType = primitiveType;
	m_NumVerts = numVerts;

	glGenVertexArrays(1, &m_VertArray);
	glBindVertexArray(m_VertArray);
}

void Mesh::end( void )
{
	glBindVertexArray(m_VertArray);

	if (m_VertBuffer != 0)
	{
		glEnableVertexAttribArray(ATTR_VERTEX);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertBuffer);
		glVertexAttribPointer(ATTR_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (m_NormBuffer != 0)
	{
		glEnableVertexAttribArray(ATTR_NORMALS);
		glBindBuffer(GL_ARRAY_BUFFER, m_NormBuffer);
		glVertexAttribPointer(ATTR_NORMALS, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (m_ColorBuffer != 0)
	{
		glEnableVertexAttribArray(ATTR_COLORS);
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
		glVertexAttribPointer(ATTR_COLORS, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (m_TexCoordBuffer != 0)
	{
		glEnableVertexAttribArray(ATTR_TEXTURE_COORDS);
		glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordBuffer);
		glVertexAttribPointer(ATTR_TEXTURE_COORDS, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glBindVertexArray(0);

	m_BatchDone = true;
}

void Mesh::render( void )
{
	if ( ! m_BatchDone)
		return;

	glBindVertexArray(m_VertArray);

	glDrawArrays(m_PrimitiveType, 0, m_NumVerts);

	glBindVertexArray(0);
}

void Mesh::copyVertexData( const GLfloat* pVerts )
{
	if (m_VertBuffer == 0)
	{
		glGenBuffers(1, &m_VertBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_NumVerts, pVerts, GL_DYNAMIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VertBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * m_NumVerts, pVerts);
	}
}

void Mesh::copyNormalData( const GLfloat* pNorms )
{
	if (m_NormBuffer == 0)
	{
		glGenBuffers(1, &m_NormBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_NormBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * m_NumVerts, pNorms, GL_DYNAMIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_NormBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * m_NumVerts, pNorms);
	}
}

void Mesh::copyColorData( const GLfloat* pColors )
{
	if (m_ColorBuffer == 0)
	{
		glGenBuffers(1, &m_ColorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * m_NumVerts, pColors, GL_DYNAMIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * m_NumVerts, pColors);
	}
}

void Mesh::copyTextureCoordData( const GLfloat* pTexCoords )
{
	if (m_TexCoordBuffer == 0)
	{
		glGenBuffers(1, &m_TexCoordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * m_NumVerts, pTexCoords, GL_DYNAMIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 2 * m_NumVerts, pTexCoords);
	}
}

