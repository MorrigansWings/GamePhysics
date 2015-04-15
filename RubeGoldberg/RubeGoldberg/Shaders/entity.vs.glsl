#version 430 core

in vec3 iVertexPosition;
in vec3 iVertexNormal;
in vec4 iVertexColor;
in vec2 iVertexTexCoord;

uniform mat4 uModelView;
uniform mat4 uModelViewProj;

out vec4 vColor;
out vec3 vNormal;
out vec2 vTexCoord;

void main()
{
	vColor    = iVertexColor;
	vNormal   = normalize(mat3(uModelView) * iVertexNormal);
	vTexCoord = iVertexTexCoord;

	gl_Position = uModelViewProj * vec4(iVertexPosition, 1.0f);
}