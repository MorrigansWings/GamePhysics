#ifndef GRAPHICS_II_RENDER_DATA_H
#define GRAPHICS_II_RENDER_DATA_H

#include <Arc/ManagedObject.h>

#include "Scene.h"

using namespace Arc;

struct RenderData
	: public ManagedObject
{
public:

	virtual inline string getClassName( void ) const { return "Render Data"; }

	Scene*					pScene;
	mat4x4					View;
	mat4x4					Proj;
	mat4x4					ViewProj;
	vec3					AmbientLightAmount;
	vec3					GlobalLightColor;
	vec3					GlobalLightDirection;
	GLfloat					ElapsedTime;
	GLfloat					TimeOfDay;
};

#endif // GRAPHICS_II_RENDER_DATA_H