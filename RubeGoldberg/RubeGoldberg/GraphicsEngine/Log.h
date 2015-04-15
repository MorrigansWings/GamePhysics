#ifndef GRAPHICS_II_LOG_H
#define GRAPHICS_II_LOG_H

#define _CRT_SECURE_NO_WARNINGS

#include <Arc/ManagedObject.h>

#include <iostream>

#include <Arc/ArrayList.h>
#include <Arc/Map.h>

using namespace Arc;

class Log :
	public ManagedObject
{
public:

	static bool AddInfoOutput( const string& filename, bool append = true );
	static bool RemoveInfoOutput( const string& filename );

	static bool AddErrorOutput( const string& filename, bool append = true );
	static bool RemoveErrorOutput( const string& filename );

#define Info(SRC, MSG) ExtInfo(SRC, MSG, string(__FILE__), __LINE__);
#define Error(SRC, MSG) ExtError(SRC, MSG, string(__FILE__), __LINE__);

#define InfoFmt(SRC, FMT, ...) ExtInfoFmt(SRC, FMT, string(__FILE__), __LINE__, __VA_ARGS__);
#define ErrorFmt(SRC, FMT, ...) ExtErrorFmt(SRC, FMT, string(__FILE__), __LINE__, __VA_ARGS__);

	static void ExtInfo( const string& src, const string& msg, const string& file, const int& line );
	static void ExtError( const string& src, const string& msg, const string& file, const int& line );

	static void ExtInfoFmt( const string& src, const string& fmt, const string& file, const int line, ... );
	static void ExtErrorFmt( const string& src, const string& fmt, const string& file, const int line, ... );

	static void CloseOutputs( void );

private:

	Log( void );
	Log( const Log& rhs );

	static string Format( const string& fmt, va_list args );

	static void Output( std::ostream& stream, const string& type, const string& src, const string& msg, const string& file, const int& line );

	static ArrayList<std::ostream*> s_Streams;

	static Map<string, int> s_InfoOutputs;
	static Map<string, int> s_ErrorOutputs;

};

#endif // GRAPHICS_II_LOG_H