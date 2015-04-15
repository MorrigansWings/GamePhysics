#version 430 core

uniform sampler2D uTex;

in vec2 vTexCoord;

layout (location = 0) out vec4 oFragColor;

void main()
{	
	vec2 texCoord = vTexCoord;
	texCoord.y = 1.0f - vTexCoord.y;

	oFragColor = texture(uTex, texCoord);

	return;
}