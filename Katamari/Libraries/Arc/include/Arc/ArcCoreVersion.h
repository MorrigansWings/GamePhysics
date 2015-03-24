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
 * 
 */

#ifndef ARC_CORE_ARC_VERSION_H
#define ARC_CORE_ARC_VERSION_H

#include "Types.h"

#include <cstdio>

namespace Arc
{

#define ARC_CORE_MAJOR_VERSION 2
#define ARC_CORE_MINOR_VERSION 0
#define ARC_CORE_PATCH_VERSION 10

typedef struct Arc_Version
{
	Arc_uint8_t Major;
	Arc_uint8_t Minor;
	Arc_uint8_t Patch;

} Arc_Version;

inline Arc_uint8_t Arc_GetMajorVersion( void )
{
	return ARC_CORE_MAJOR_VERSION;
}

inline Arc_uint8_t Arc_GetMinorVersion( void )
{
	return ARC_CORE_MINOR_VERSION;
}

inline Arc_uint8_t Arc_GetPatchVersion( void )
{
	return ARC_CORE_PATCH_VERSION;
}

inline Arc_Version Arc_GetVersion( void )
{
	Arc_Version current;
	current.Major = ARC_CORE_MAJOR_VERSION;
	current.Minor = ARC_CORE_MINOR_VERSION;
	current.Patch = ARC_CORE_PATCH_VERSION;
	return current;
}

inline string Arc_GetVersionString( void )
{
	char version[15];

#if defined(ARC_OS_WINDOWS)

	sprintf_s(version, "%d.%d.%d", ARC_CORE_MAJOR_VERSION, ARC_CORE_MINOR_VERSION, ARC_CORE_PATCH_VERSION);

#else

	sprintf(version, "%d.%d.%d", ARC_CORE_MAJOR_VERSION, ARC_CORE_MINOR_VERSION, ARC_CORE_PATCH_VERSION);

#endif

	return string(version);
}

inline bool Arc_AboveVersion( Arc_uint8_t major, Arc_uint8_t minor, Arc_uint8_t patch )
{
	return ( (major >= ARC_CORE_MAJOR_VERSION) && (minor >= ARC_CORE_MINOR_VERSION) && (patch >= ARC_CORE_PATCH_VERSION) );
}

inline bool Arc_AboveVersion( const Arc_Version& version )
{
	return Arc_AboveVersion(version.Major, version.Minor, version.Patch);
}

} // namespace Arc

#endif // ARC_CORE_ARC_VERSION_H