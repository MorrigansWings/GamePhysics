#version 430 core

layout(location = 0) out vec4 out_color;

in vec4 color;

void main(void)
{
	//out_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	out_color = color;
}