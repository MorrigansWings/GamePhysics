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
 * Platform specific defines and functions.
 */

#ifndef ARC_CORE_PLATFORM_H
#define ARC_CORE_PLATFORM_H

namespace Arc
{

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) && !defined(__GNUC__)

#define ARC_OS_WINDOWS

#elif defined(__unix__) || defined(__posix__) || defined(linux) || defined(__linux__)

#define ARC_OS_LINUX

#elif defined(__APPLE__)

#define ARC_OS_MAC

#elif defined(__ANDROID__)

#define _ARC_OS_ANDROID

#endif

#if defined(_DEBUG) || defined(DEBUG)

#define ARC_DEBUG_BUILD

#elif defined(_RELEASE) || defined(RELEASE)

#define ARC_RELEASE_BUILD

#endif

} // namespace Arc

#endif // ARC_CORE_PLATFORM_H
