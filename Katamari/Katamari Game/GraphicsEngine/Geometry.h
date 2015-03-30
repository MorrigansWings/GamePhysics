#ifndef GRAPHICS_II_GEOMETRY_H
#define GRAPHICS_II_GEOMETRY_H

#include "OpenGL.h"

#include <Arc/ArrayList.h>

class Mesh;

using namespace Arc;

class Geometry
{
public:

	static ArrayList<vec3> GetPlaneVerts( const GLenum& primitiveType, const vec3& pos, const GLfloat& width, const GLfloat& height, const unsigned int& resX, const unsigned int& resY );

	static ArrayList<vec3> GetCubeVerts( const GLenum& primitiveType, const vec3& pos, const GLfloat& width, const GLfloat& height, const GLfloat& depth );

	static Mesh* CreatePlane( const string& name, const GLenum& primitiveType, const vec3& pos, const GLfloat& width, const GLfloat& height, const unsigned int& resX, const unsigned int& resZ );

	static Mesh* CreateCube( const string& name, const GLenum& primitiveType, const vec3& pos, const GLfloat& width, const GLfloat& height, const GLfloat& depth );

	//static Mesh* CreateSphere( GLenum primitiveType );

	//static Mesh* CreateTorus( GLenum primitiveType );

private:

	Geometry( void );
	Geometry( const Geometry& rhs );
	void operator=( const Geometry& rhs );

	static Mesh* CreateMesh( const string& name, const GLenum& primitiveType, const ArrayList<vec3>& verts );

};

#endif // GRAPHICS_II_GEOMETRY_H