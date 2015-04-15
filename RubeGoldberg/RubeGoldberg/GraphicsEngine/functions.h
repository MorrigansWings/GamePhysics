#ifndef GRAPHICS_II_FUNCTIONS_H
#define GRAPHICS_II_FUNCTIONS_H

#include <Arc/Vector2.h>
#include <Arc/Vector3.h>
#include <Arc/Vector4.h>

#include "OpenGL.h"

using namespace Arc;

inline void vec2_glm_to_arc( const vec2& from, Vector2& to )
{
	to.setX(from.x);
	to.setY(from.y);
}

inline void vec2_arc_to_glm( const Vector2& from, vec2& to )
{
	to.x = from.getX();
	to.y = from.getY();
}

inline void vec3_glm_to_arc( const vec3& from, Vector3& to )
{
	to.setX(from.x);
	to.setY(from.y);
	to.setZ(from.z);
}

inline void vec3_arc_to_glm( const Vector3& from, vec3& to )
{
	to.x = from.getX();
	to.y = from.getY();
	to.z = from.getZ();
}

inline void vec4_glm_to_arc( const vec4& from, Vector4& to )
{
	to.setX(from.x);
	to.setY(from.y);
	to.setZ(from.z);
	to.setW(from.w);
}

inline void vec4_arc_to_glm( const Vector4& from, vec4& to )
{
	to.x = from.getX();
	to.y = from.getY();
	to.z = from.getZ();
	to.w = from.getW();
}

#endif // GRAPHICS_II_FUNCTIONS_H