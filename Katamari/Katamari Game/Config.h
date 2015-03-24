#ifndef GRAPHICS_II_CONFIG_H
#define GRAPHICS_II_CONFIG_H

#include <Arc/StringFunctions.h>
#include <Arc/Map.h>
#include <Arc/Buffer.h>
#include <Arc/ParseFunctions.h>

#include "OpenGL.h"

using namespace Arc;

typedef string ConfigKey;

class Scene;
class Camera;
class HeightMap;
class Water;
class Entity;

class Config 
{
public:

	static void LoadFile( const string& filename );

	static inline bool HasString( const string& name ) { return s_ConfigString.containsKey(name); }
	static inline bool HasInt   ( const string& name ) { return s_ConfigInt.containsKey(name); }
	static inline bool HasFloat ( const string& name ) { return s_ConfigFloat.containsKey(name); }
	static inline bool HasBool  ( const string& name ) { return s_ConfigBool.containsKey(name); }
	static inline bool HasVec2  ( const string& name ) { return s_ConfigVec2.containsKey(name); }
	static inline bool HasVec3  ( const string& name ) { return s_ConfigVec3.containsKey(name); }
	static inline bool HasVec4  ( const string& name ) { return s_ConfigVec4.containsKey(name); }
	static inline bool HasColor ( const string& name ) { return s_ConfigVec4.containsKey(name); }

	static inline string GetString( const string& name ) { return (HasString(name) ? s_ConfigString[name] : "" ); }
	static inline int    GetInt   ( const string& name ) { return (HasInt(name)    ? s_ConfigInt[name]    : 0 ); }
	static inline float  GetFloat ( const string& name ) { return (HasFloat(name)  ? s_ConfigFloat[name]  : 0.0f ); }
	static inline bool   GetBool  ( const string& name ) { return (HasBool(name)   ? s_ConfigBool[name]   : false ); }
	static inline vec2   GetVec2  ( const string& name ) { return (HasVec2(name)   ? s_ConfigVec2[name]   : vec2(0.0f) ); }
	static inline vec3   GetVec3  ( const string& name ) { return (HasVec3(name)   ? s_ConfigVec3[name]   : vec3(0.0f) ); }
	static inline vec4   GetVec4  ( const string& name ) { return (HasVec4(name)   ? s_ConfigVec4[name]   : vec4(0.0f) ); }
	static inline vec4   GetColor ( const string& name ) { return (HasColor(name)  ? s_ConfigVec4[name]   : vec4(0.0f) ); }

private:

	static Scene*	  ReadScene    ( const string& name, Buffer& file, const string& dirname );
	static Camera*    ReadCamera   ( const string& name, Buffer& file, const string& dirname );
	static Entity*    ReadEntity   ( const string& name, Buffer& file, const string& dirname );
	static HeightMap* ReadHeightMap( const string& name, Buffer& file, const string& dirname );
	static void       ReadShader   ( const string& name, Buffer& file, const string& dirname );

	static string ReadUntilWhitespace( const string& str, const int& start, int& offset );

	static string ReadString( const string& str, const int& start, int& offset );
	static int    ReadInt   ( const string& str, const int& start, int& offset );
	static float  ReadFloat ( const string& str, const int& start, int& offset );
	static bool   ReadBool  ( const string& str, const int& start, int& offset );
	static vec2   ReadVec2  ( const string& str, const int& start, int& offset );
	static vec3   ReadVec3  ( const string& str, const int& start, int& offset );
	static vec4   ReadVec4  ( const string& str, const int& start, int& offset );
	static vec4   ReadColor ( const string& str, const int& start, int& offset );

	static Map<ConfigKey, int>		s_ConfigInt;

	static Map<ConfigKey, float>	s_ConfigFloat;

	static Map<ConfigKey, bool>		s_ConfigBool;

	static Map<ConfigKey, string>	s_ConfigString;

	static Map<ConfigKey, vec2>		s_ConfigVec2;

	static Map<ConfigKey, vec3>		s_ConfigVec3;

	static Map<ConfigKey, vec4>		s_ConfigVec4;

};

#endif // GRAPHICS_II_CONFIG_H