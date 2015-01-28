#include "Object.h"
#include "../Vertex.h"

Object::Object(void)
{
	m_world = glm::mat4(1.0f); // set world as identity matrix
}

Object::~Object(void)
{
	
}