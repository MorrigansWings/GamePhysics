#ifndef _OBJECT_H_
#define _OBJECT_H_

#pragma once

#include "../../Dependencies/glew/glew.h"

class Object
{
protected:
	int m_numVertices;
	int m_numTriangles;

//	glm::mat4 m_world;

	

public:
	Object(void);
	~Object(void);

};

#endif // _OBJECT_H_