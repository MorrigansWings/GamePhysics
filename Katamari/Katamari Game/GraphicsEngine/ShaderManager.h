#ifndef GRAPHICS_II_SHADER_MANAGER_H
#define GRAPHICS_II_SHADER_MANAGER_H

#include <Arc/ManagedObject.h>

#include <fstream>

#include "OpenGL.h"
#include <cmath>

#include "Log.h"

using namespace Arc;

struct Shader;

class ShaderManager :
	public ManagedObject
{
public:

	inline ShaderManager( void )
		: m_CurrProg(),
		  m_Programs()
	{ }

	virtual inline ~ShaderManager( void )
	{ }

	virtual inline string getClassName( void ) const { return "Shader Manager"; }

	bool loadProgram( const string& name, const ArrayList<Shader>& shaders );

	bool useProgram( const string& name );
	GLint getProgram( const string& name ) { return (m_Programs.containsKey(name) ? m_Programs[name] : -1); }

	inline GLint getUniformLocation( const string& uniformName ) { return getUniformLocation(m_CurrProgName, uniformName); }
	GLint getUniformLocation( const string& programName, const string& uniformName );

	inline void setUniform1f( const GLint& location, const GLfloat& val0 ) { glUniform1f(location, val0);  checkUniformError(); }
	inline void setUniform1i( const GLint& location, const GLint& val0 )   { glUniform1i(location, val0);  checkUniformError(); }
	inline void setUniform1ui( const GLint& location, const GLuint& val0 ) { glUniform1ui(location, val0); checkUniformError(); }

	inline void setUniform2f( const GLint& location, const GLfloat& val0, const GLfloat& val1 ) { glUniform2f(location, val0, val1);  checkUniformError(); }
	inline void setUniform2i( const GLint& location, const GLint& val0, const GLint& val1 )     { glUniform2i(location, val0, val1);  checkUniformError(); }
	inline void setUniform2ui( const GLint& location, const GLuint& val0, const GLuint& val1 )  { glUniform2ui(location, val0, val1); checkUniformError(); }
	inline void setUniform2f( const GLint& location, const vec2& val ) { setUniform2f(location, val.x, val.y); }

	inline void setUniform3f( const GLint& location, const GLfloat& val0, const GLfloat& val1, const GLfloat& val2 ) { glUniform3f(location, val0, val1, val2);  checkUniformError(); }
	inline void setUniform3i( const GLint& location, const GLint& val0, const GLint& val1, const GLint& val2 )       { glUniform3i(location, val0, val1, val2);  checkUniformError(); }
	inline void setUniform3ui( const GLint& location, const GLuint& val0, const GLuint& val1, const GLuint& val2 )   { glUniform3ui(location, val0, val1, val2); checkUniformError(); }
	inline void setUniform3f( const GLint& location, const vec3& val ) { setUniform3f(location, val.x, val.y, val.z); }

	inline void setUniform4f( const GLint& location, const GLfloat& val0, const GLfloat& val1, const GLfloat& val2, const GLfloat& val3 ) { glUniform4f(location, val0, val1, val2, val3);  checkUniformError(); }
	inline void setUniform4i( const GLint& location, const GLint& val0, const GLint& val1, const GLint& val2, const GLint& val3 )         { glUniform4i(location, val0, val1, val2, val3);  checkUniformError(); }
	inline void setUniform4ui( const GLint& location, const GLuint& val0, const GLuint& val1, const GLuint& val2, const GLuint& val3 )    { glUniform4ui(location, val0, val1, val2, val3); checkUniformError(); }
	inline void setUniform4f( const GLint& location, const vec4& val ) {  setUniform4f(location, val.x, val.y, val.z, val.w); }

	inline void setUniform1fv( const GLint& location, const GLsizei& count, const GLfloat* pVal ) { glUniform1fv(location, count, pVal); checkUniformError(); }
	inline void setUniform2fv( const GLint& location, const GLsizei& count, const GLfloat* pVal ) { glUniform2fv(location, count, pVal); checkUniformError(); }
	inline void setUniform3fv( const GLint& location, const GLsizei& count, const GLfloat* pVal ) { glUniform3fv(location, count, pVal); checkUniformError(); }
	inline void setUniform4fv( const GLint& location, const GLsizei& count, const GLfloat* pVal ) { glUniform4fv(location, count, pVal); checkUniformError(); }

	inline void setUniform2fv( const GLint& location, const GLsizei& count, const vec2* pVal ) { setUniform2fv(location, count, (GLfloat*)pVal); }
	inline void setUniform3fv( const GLint& location, const GLsizei& count, const vec3* pVal ) { setUniform3fv(location, count, (GLfloat*)pVal); }
	inline void setUniform4fv( const GLint& location, const GLsizei& count, const vec4* pVal ) { setUniform4fv(location, count, (GLfloat*)pVal); }

	inline void setUniform1iv( const GLint& location, const GLsizei& count, const GLint* pVal ) { glUniform1iv(location, count, pVal); checkUniformError(); }
	inline void setUniform2iv( const GLint& location, const GLsizei& count, const GLint* pVal ) { glUniform2iv(location, count, pVal); checkUniformError(); }
	inline void setUniform3iv( const GLint& location, const GLsizei& count, const GLint* pVal ) { glUniform3iv(location, count, pVal); checkUniformError(); }
	inline void setUniform4iv( const GLint& location, const GLsizei& count, const GLint* pVal ) { glUniform4iv(location, count, pVal); checkUniformError(); }

	inline void setUniform1uiv( const GLint& location, const GLsizei& count, const GLuint* pVal ) { glUniform1uiv(location, count, pVal); checkUniformError(); }
	inline void setUniform2uiv( const GLint& location, const GLsizei& count, const GLuint* pVal ) { glUniform2uiv(location, count, pVal); checkUniformError(); }
	inline void setUniform3uiv( const GLint& location, const GLsizei& count, const GLuint* pVal ) { glUniform3uiv(location, count, pVal); checkUniformError(); }
	inline void setUniform4uiv( const GLint& location, const GLsizei& count, const GLuint* pVal ) { glUniform4uiv(location, count, pVal); checkUniformError(); }

	inline void setUniformMatrix2fv( const GLint& location, const GLsizei& count, const GLfloat* pVal, const GLboolean& transpose = false ) { glUniformMatrix2fv(location, count, transpose, pVal); checkUniformError(); }
	inline void setUniformMatrix3fv( const GLint& location, const GLsizei& count, const GLfloat* pVal, const GLboolean& transpose = false ) { glUniformMatrix3fv(location, count, transpose, pVal); checkUniformError(); }
	inline void setUniformMatrix4fv( const GLint& location, const GLsizei& count, const GLfloat* pVal, const GLboolean& transpose = false ) { glUniformMatrix4fv(location, count, transpose, pVal); checkUniformError(); }

	inline void setUniformMatrix2fv( const GLint& location, const GLsizei& count, const mat2* pVal, const GLboolean& transpose = false ) { glUniformMatrix2fv(location, count, transpose, (GLfloat*)pVal); checkUniformError(); }
	inline void setUniformMatrix3fv( const GLint& location, const GLsizei& count, const mat3* pVal, const GLboolean& transpose = false ) { glUniformMatrix3fv(location, count, transpose, (GLfloat*)pVal); checkUniformError(); }
	inline void setUniformMatrix4fv( const GLint& location, const GLsizei& count, const mat4* pVal, const GLboolean& transpose = false ) { glUniformMatrix4fv(location, count, transpose, (GLfloat*)pVal); checkUniformError(); }

	inline void setUniformMatrix2x3fv( const GLint& location, const GLsizei& count, const GLfloat* pVal, const GLboolean& transpose = false ) { glUniformMatrix2x3fv(location, count, transpose, pVal); checkUniformError(); }
	inline void setUniformMatrix3x2fv( const GLint& location, const GLsizei& count, const GLfloat* pVal, const GLboolean& transpose = false ) { glUniformMatrix3x2fv(location, count, transpose, pVal); checkUniformError(); }

	inline void setUniformMatrix2x3fv( const GLint& location, const GLsizei& count, const mat2x3* pVal, const GLboolean& transpose = false ) { glUniformMatrix2x3fv(location, count, transpose, (GLfloat*)pVal); checkUniformError(); }
	inline void setUniformMatrix3x2fv( const GLint& location, const GLsizei& count, const mat3x2* pVal, const GLboolean& transpose = false ) { glUniformMatrix3x2fv(location, count, transpose, (GLfloat*)pVal); checkUniformError(); }

	inline void setUniformMatrix2x4fv( const GLint& location, const GLsizei& count, const GLfloat* pVal, const GLboolean& transpose = false ) { glUniformMatrix2x4fv(location, count, transpose, pVal); checkUniformError(); }
	inline void setUniformMatrix4x2fv( const GLint& location, const GLsizei& count, const GLfloat* pVal, const GLboolean& transpose = false ) { glUniformMatrix4x2fv(location, count, transpose, pVal); checkUniformError(); }

	inline void setUniformMatrix2x4fv( const GLint& location, const GLsizei& count, const mat2x4* pVal, const GLboolean& transpose = false ) { glUniformMatrix2x4fv(location, count, transpose, (GLfloat*)pVal); checkUniformError(); }
	inline void setUniformMatrix4x2fv( const GLint& location, const GLsizei& count, const mat4x2* pVal, const GLboolean& transpose = false ) { glUniformMatrix4x2fv(location, count, transpose, (GLfloat*)pVal); checkUniformError(); }

	inline void setUniformMatrix3x4fv( const GLint& location, const GLsizei& count, const GLfloat* pVal, const GLboolean& transpose = false ) { glUniformMatrix3x4fv(location, count, transpose, pVal); checkUniformError(); }
	inline void setUniformMatrix4x3fv( const GLint& location, const GLsizei& count, const GLfloat* pVal, const GLboolean& transpose = false ) { glUniformMatrix4x3fv(location, count, transpose, pVal); checkUniformError(); }

	inline void setUniformMatrix3x4fv( const GLint& location, const GLsizei& count, const mat3x4* pVal, const GLboolean& transpose = false ) { glUniformMatrix3x4fv(location, count, transpose, (GLfloat*)pVal); checkUniformError(); }
	inline void setUniformMatrix4x3fv( const GLint& location, const GLsizei& count, const mat4x3* pVal, const GLboolean& transpose = false ) { glUniformMatrix4x3fv(location, count, transpose, (GLfloat*)pVal); checkUniformError(); }


	void printProgramLog( const GLuint& program );

	void printShaderLog( const GLuint& shader );

private:

	GLuint loadShaderFromFile( const string& filename, const GLenum& shaderType );

	void checkUniformError( void );

	Map<string, GLuint> m_Programs;

	Map<string, Map<string, GLint>> m_UniformLocations;

	GLuint m_CurrProg;

	string m_CurrProgName;

};

#endif // GRAPHICS_II_SHADER_MANAGER_H