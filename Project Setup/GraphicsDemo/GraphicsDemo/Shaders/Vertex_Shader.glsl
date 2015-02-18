#version 430 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;

uniform mat4 uModelViewProj;

out vec4 color;

void main(void)
{
	color = in_color;
	//color = vec4(1.0f, 0.0f, 0.0f, 1.0f);

	gl_Position = uModelViewProj * vec4(in_position, 1);
	//gl_Position = vec4(in_position, 1);
}