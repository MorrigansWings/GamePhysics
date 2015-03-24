#ifndef GRAPHICS_II_BATCH_H
#define GRAPHICS_II_BATCH_H

#include <Arc/ManagedObject.h>

#include <Arc/ArrayList.h>

#include "OpenGL.h"

class ResourceManager;

using namespace Arc;

typedef GLuint MeshAttrID;

class Mesh :
	public ManagedObject
{

	friend class ResourceManager;

public:

	static const MeshAttrID ATTR_VERTEX;
	static const MeshAttrID ATTR_NORMALS;
	static const MeshAttrID ATTR_COLORS;
	static const MeshAttrID ATTR_TEXTURE_COORDS;

	inline Mesh( void )
		: m_BatchDone(false),
		  m_PrimitiveType(0),
		  m_NumVerts(0),
		  m_VertBuffer(0),
		  m_NormBuffer(0),
		  m_ColorBuffer(0),
		  m_TexCoordBuffer(0),
		  m_VertArray(0)
	{ }

	virtual ~Mesh( void );

	virtual inline string getClassName( void ) const { return "Mesh"; }

	void begin( const GLenum& primitiveType, const GLuint& numVerts );

	void end( void );

	void render( void );

	void copyVertexData( const GLfloat* pVerts );

	void copyNormalData( const GLfloat* pNorms );

	void copyColorData( const GLfloat* pColors );

	void copyTextureCoordData( const GLfloat* pTexCoords );

	inline void copyVertexData( const vec3* pVerts ) { copyVertexData((const GLfloat*)pVerts); }

	inline void copyNormalData( const vec3* pNorms ) { copyNormalData((const GLfloat*)pNorms); }

	inline void copyColorData( const vec4* pColors ) { copyColorData((const GLfloat*)pColors); }

	inline void copyTextureCoordData( vec2* pTexCoords ) { copyTextureCoordData((const GLfloat*)pTexCoords); }

	inline void copyVertexData( const ArrayList<vec3>& verts ) { if (verts.isEmpty()) return; copyVertexData((const GLfloat*)&verts[0]); }

	inline void copyNormalData( const ArrayList<vec3>& norms ) { if (norms.isEmpty()) return; copyNormalData((const GLfloat*)&norms[0]); }

	inline void copyColorData( const ArrayList<vec4>& colors ) { if (colors.isEmpty()) return; copyColorData((const GLfloat*)&colors[0]); }

	inline void copyTextureCoordData( const ArrayList<vec2>& texCoords ) { if (texCoords.isEmpty()) return; copyTextureCoordData((const GLfloat*)&texCoords[0]); }

private:

	Mesh( const Mesh& rhs );

	void operator=( const Mesh& rhs );

	bool m_BatchDone;

	GLenum m_PrimitiveType;

	int m_NumVerts;

	GLuint m_VertBuffer;

	GLuint m_NormBuffer;

	GLuint m_ColorBuffer;

	GLuint m_TexCoordBuffer;

	GLuint m_VertArray;
};

#endif // GRAPHICS_II_BATCH_H