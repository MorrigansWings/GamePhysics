#version 430 core

layout (location = 0) in vec3 iVertexPosition;
layout (location = 3) in vec2 iVertexTexCoord;

uniform mat4 uModelViewProj;

out vec2 vTexCoord;

void main()
{
	vTexCoord = iVertexTexCoord;

	gl_Position = uModelViewProj * vec4(iVertexPosition, 1.0f);
}