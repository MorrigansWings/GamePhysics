#include "Core/Shader_Loader.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace Core;
using namespace std;

Shader_Loader::Shader_Loader(void){}
Shader_Loader::~Shader_Loader(void){}

string Shader_Loader::ReadShader(char *filename)
{
	string shaderCode;
	ifstream file(filename, ios::in);

	if (!file.good())
	{
		cout << "Can't read file " << filename << endl;
		terminate();
	}

	file.seekg(0, ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint Shader_Loader::CreateShader(GLenum shaderType, string source, char *shaderName)
{
	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	if (compile_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		cout << "ERROR compiling shader: " << shaderName << endl << &shader_log[0] << endl;
		return 0;
	}
	return shader;
}

GLuint Shader_Loader::CreateProgram(char *vertexShaderFilename, char *fragmentShaderFilename)
{
	// Read shader files
	string vertex_shader_code = ReadShader(vertexShaderFilename);
	string fragment_shader_code = ReadShader(fragmentShaderFilename);

	GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	int link_result = 0;

	// Make program handle
	GLuint program = glCreateProgram();
	
	// Attach shaders
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	
	// Link and check for errors
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		int info_log_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		vector<char> program_log(info_log_length);
		glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
		cout << "Shader Loader : LINK ERROR" << endl << &program_log[0] << endl;
		return 0;
	}
	return program;
}