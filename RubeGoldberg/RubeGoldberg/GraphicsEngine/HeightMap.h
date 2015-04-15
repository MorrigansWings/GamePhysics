#ifndef GRAPHICS_II_HEIGHT_MAP_H
#define GRAPHICS_II_HEIGHT_MAP_H

#include "Entity.h"

#include "OpenGL.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

using namespace Arc;

class HeightMap :
	public Entity
{
public:

	HeightMap( void );
	HeightMap( const string& heightMapFilename, const string& textureFilename, const GLfloat& resultWidth, const GLfloat& resultHeight, const GLfloat& topLevel, const GLfloat& bottomLevel, const int& samples );
	virtual ~HeightMap( void );

	virtual inline string getClassName( void ) const { return "Height Map"; }

	bool load( const string& heightMapFilename, const string& textureFilename, const GLfloat& resultWidth, const GLfloat& resultHeight, const GLfloat& topLevel, const GLfloat& bottomLevel, const int& samples );

	float getHeightAt( vec2 pos );

private:

	ArrayList<ArrayList<float>> m_Heights;

	float m_Width, m_Height;

};

#endif // GRAPHICS_II_HEIGHT_MAP_H