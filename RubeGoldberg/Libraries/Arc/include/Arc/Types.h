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
 * Define a standard set of types
 */

#ifndef ARC_CORE_TYPES_H
#define ARC_CORE_TYPES_H

#include "Platform.h"

#include <string>

using std::string;

#if defined(ARC_OS_WINDOWS)

typedef signed char        Arc_int8_t;
typedef short              Arc_int16_t;
typedef int                Arc_int32_t;
typedef long long          Arc_int64_t;
typedef unsigned char      Arc_uint8_t;
typedef unsigned short     Arc_uint16_t;
typedef unsigned int       Arc_uint32_t;
typedef unsigned long long Arc_uint64_t;

#elif defined(ARC_OS_LINUX) || defined(ARC_OS_MAC)

typedef signed char        Arc_int8_t;
typedef short              Arc_int16_t;
typedef int                Arc_int32_t;
typedef long long          Arc_int64_t;
typedef unsigned char      Arc_uint8_t;
typedef unsigned short     Arc_uint16_t;
typedef unsigned int       Arc_uint32_t;
typedef unsigned long long Arc_uint64_t;

#endif

#endif // ARC_CORE_TYPES_H