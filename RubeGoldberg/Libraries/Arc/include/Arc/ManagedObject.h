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

#ifndef ARC_CORE_MANAGED_OBJECT_H
#define ARC_CORE_MANAGED_OBJECT_H

#include "Types.h"

namespace Arc
{

class ManagedObject
{
protected:

	inline ManagedObject( void ) { }

public:

	virtual inline ~ManagedObject( void ) { }

	virtual string getClassName( void ) const = 0;

	// Normal new operator
	void* operator new  ( size_t size );
	void* operator new[]( size_t size );

	// Operator for placement new, takes in the filename and line number 
	void* operator new  ( size_t size, int lineNumber, const char *filename );
	void* operator new[]( size_t size, int lineNumber, const char *filename );

	// Normal delete operator
	void operator delete  ( void *ptr);
	void operator delete[]( void *ptr);

	// Required because of the placement new operator, should not be used
	inline void operator delete  ( void *ptr, int lineNumber, const char *filename ) { ::operator delete(ptr); }
	inline void operator delete[]( void *ptr, int lineNumber, const char *filename ) { ::operator delete[](ptr); }

#ifdef ARC_DEBUG_BUILD

// Used to pass the filename and line number into the placement new operator
#define New new(__LINE__, __FILE__)

#else

// When not debugging, use the normal new operator
#define New new

#endif

}; // class ArcManagedObject

} // namespace Arc

#endif // ARC_CORE_MANAGED_OBJECT_H