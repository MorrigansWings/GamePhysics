/* This file is part of ArcCore.
 *
 * ArcCore is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ArcCore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcCore; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Author: Stephen Lane-Walsh
 *
 */

#ifndef ARC_CORE_STRING_FUNCTIONS_H
#define ARC_CORE_STRING_FUNCTIONS_H

#include "Types.h"
#include "ArrayList.h"

namespace Arc
{

extern const size_t StringBadLength;
extern const size_t StringBadPosition;

string Arc_Basename( const string& path );

string Arc_Dirname( const string& path );

string Arc_FileExtension( const string& path );

void Arc_StringToLower( string& str );

void Arc_StringToUpper( string& str );

inline string Arc_StringGetLower( const string& str )
{
	string copy = str;
	Arc_StringToLower(copy);
	return copy;
}

inline string Arc_StringGetUpper( const string& str )
{
	string copy = str;
	Arc_StringToUpper(copy);
	return copy;
}

void Arc_StringUCWords( string& str );

void Arc_StringUCFirst( string& str );

string Arc_StringGetUCWords( const string& str );

string Arc_StringGetUCFirst( const string& str );

void Arc_TrimLeft( string& str );

void Arc_TrimRight( string& str );

inline void Arc_Trim( string& str )
{
	Arc_TrimLeft(str);
	Arc_TrimRight(str);
}

string Arc_GetTrimLeft( const string& str );

string Arc_GetTrimRight( const string& str );

string Arc_GetTrim( const string& str );

int Arc_StringReplaceNext( string& str, const string& search, const string& replace );

int Arc_StringReplaceAll( string& str, const string& search, const string& replace );

string Arc_Substring( const string& str, const unsigned int& begin,
					  const int& maxLength = -1 );

inline bool Arc_StringContains( const string& str, const char& search )
{
	return (str.find(search) != StringBadPosition);
}

inline bool Arc_StringContains( const string& str, const string& search )
{
	return (str.find(search) != StringBadPosition);
}

ArrayList<string> Arc_StringSplit( const string& str, const string& sep,
								   const int& limit = -1 );

inline ArrayList<string> Arc_StringSplit( const string& str, const char& sep,
								          const int& limit = -1 )
{
	string newSep;
	newSep += sep;
	return Arc_StringSplit(str, newSep, limit);
}

string Arc_StringJoin( const string& glue, const ArrayList<string>& pieces );

} // namespace Arc

#endif // ARC_CORE_STRING_FUNCTIONS_H
