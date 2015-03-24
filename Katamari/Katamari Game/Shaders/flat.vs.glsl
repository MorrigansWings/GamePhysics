#version 430 core

layout (location = 0) in vec3 iVertexPosition;
layout (location = 1) in vec3 iVertexNormal;
layout (location = 2) in vec4 iVertexColor;
layout (location = 3) in vec2 iVertexTexCoord;

uniform mat4 uModelViewProj;
uniform vec4 uFlatColor;

layout (location = 0) out vec4 vColor;

void main()
{
	vColor = uFlatColor;

	gl_Position = uModelViewProj * vec4(iVertexPosition, 1.0f);
}