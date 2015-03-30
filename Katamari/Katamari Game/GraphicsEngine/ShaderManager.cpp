#include "ShaderManager.h"

#include "Shader.h"

bool ShaderManager::loadProgram( const string& name, const ArrayList<Shader>& shaders )
{
	ArrayList<GLuint> shaderIDs;
	for (unsigned int i = 0; i < shaders.getSize(); ++i)
	{
		const Shader& shader = shaders[i];

		shaderIDs.add(loadShaderFromFile(shader.Filename, shader.Type));
	}

	GLuint program;

	program = glCreateProgram();

	for (unsigned int i = 0; i < shaders.getSize(); ++i)
	{
		glAttachShader(program, shaderIDs[i]);
	}

	glLinkProgram(program);

	GLint programLinked = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &programLinked);

	if (programLinked != GL_TRUE)
	{
		Log::ErrorFmt(getClassName(), "Failed to link program %d\n", program);
		printProgramLog(program);
		glDeleteProgram(program);
		program = 0;
	}

	for (unsigned int i = 0; i < shaders.getSize(); ++i)
	{
		glDeleteShader(shaderIDs[i]);
	}

	if (program == 0)
		return false;

	m_Programs.add(name, program);
	m_UniformLocations.add(name, Map<string, GLint>());

	int uniformCount = -1;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniformCount); 

	for (GLuint i = 0; i < (unsigned)uniformCount; ++i)
	{
		int nameLength;
		int num;
		GLenum uniformType = GL_ZERO;
		char uniformName[100];

		glGetActiveUniform(program, i, sizeof(uniformName) - 1, &nameLength, &num, &uniformType, uniformName );

		uniformName[nameLength] = '\0';
		GLuint location = i;
		//GLuint location = glGetUniformLocation(program, uniformName);

		m_UniformLocations[name].add(uniformName, location);
	}

	return true;
}

bool ShaderManager::useProgram( const string& name )
{
	if ( ! m_Programs.containsKey(name))
	{
		glUseProgram(0);
		return false;
	}

	if (m_CurrProg == m_Programs[name])
		return true;

	glUseProgram(0);
	m_CurrProg = m_Programs[name];
	m_CurrProgName = name;
	glUseProgram(m_CurrProg);

	return true;
}

void ShaderManager::printProgramLog( const GLuint& program )
{
	if( glIsProgram( program ) )
	{
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

		char* infoLog = new char[ maxLength ];

		glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			Log::ErrorFmt(getClassName(), "Log for Program %d:\n%s", program, infoLog);
		}

		delete[] infoLog;
	}
	else
	{
		//Log::ErrorFmt(getClassName(), "Cannot print program log, %d is not a program", program);
	}
}

void ShaderManager::printShaderLog( const GLuint& shader )
{
	if( glIsShader( shader ) )
	{
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

		char* infoLog = new char[ maxLength ];

		glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			Log::ErrorFmt(getClassName(), "Log for Shader %d:\n%s", shader, infoLog);
		}

		delete[] infoLog;
	}
	else
	{
		Log::ErrorFmt(getClassName(), "Cannot print shader log, %d is not a shader", shader);
	}
}

GLuint ShaderManager::loadShaderFromFile( const string& filename, const GLenum& shaderType )
{
	Log::InfoFmt(getClassName(), "Load from file \"%s\"", filename.c_str());
	GLuint shader = 0;
	string shaderString;
	std::ifstream file(filename);

	if (file)
	{
		shaderString.assign( (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>() );
		shader = glCreateShader(shaderType);

		const GLchar* shaderSource = shaderString.c_str();

		glShaderSource(shader, 1, (const GLchar**)&shaderSource, NULL);

		glCompileShader(shader);

		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
		if (shaderCompiled != GL_TRUE)
		{
			Log::ErrorFmt(getClassName(), "Failed to compile shader %d \"%s", shader, filename.c_str());
			printShaderLog(shader);
			glDeleteShader(shader);
			shader = 0;
		}
	}
	else
	{
		Log::ErrorFmt(getClassName(), "Unable to open file \"%s\"", filename.c_str());
		return 0;
	}

	Log::InfoFmt(getClassName(), "Shader \"%s\" Loaded", filename.c_str());

	return shader;
}

GLint ShaderManager::getUniformLocation( const string& programName, const string& uniformName )
{
	if (m_CurrProg == 0)
		return -1;

	if ( ! m_UniformLocations.containsKey(programName))
		return -1;

	if ( ! m_UniformLocations[programName].containsKey(uniformName))
		return -1;

	return m_UniformLocations[programName][uniformName];
}

void ShaderManager::checkUniformError( void )
{
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		Log::ErrorFmt(getClassName(), "Uniform Error, #%d %s", error, gluGetString(error));
	}
}
