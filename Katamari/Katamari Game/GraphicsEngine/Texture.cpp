#include "Texture.h"

#include "ResourceManager.h"

Texture::~Texture( void )
{
	if (m_TextureID)
		glDeleteTextures(1, &m_TextureID);
}

void Texture::bind( void )
{
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}
