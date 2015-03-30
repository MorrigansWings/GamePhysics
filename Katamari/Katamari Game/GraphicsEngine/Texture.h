#ifndef GRAPHICS_II_TEXTURE_H
#define GRAPHICS_II_TEXTURE_H

#include <Arc/ManagedObject.h>

#include "OpenGL.h"

using namespace Arc;

class ResourceManager;

class Texture :
	public ManagedObject
{
	
	friend class ResourceManager;

public:

	virtual inline string getClassName( void ) const { return "Texture"; }

	void bind( void );

	GLint getWidth( void ) const { return m_Width; }
	GLint getHeight( void ) const { return m_Height; }

private:

	inline Texture( GLuint texID, GLint width, GLint height )
		: m_TextureID(texID),
		  m_Width(width),
		  m_Height(height)
	{ }

	virtual ~Texture( void );

	inline GLuint getGLTexture( void ) const { return m_TextureID; }

	GLuint m_TextureID;

	GLint m_Width;
	GLint m_Height;

};

#endif // GRAPHICS_II_TEXTURE_H