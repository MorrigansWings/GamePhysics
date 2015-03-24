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

#ifndef ARC_CORE_MEMORY_TRACKER_H
#define ARC_CORE_MEMORY_TRACKER_H

#include <iostream>

#include "Types.h"
#include "Map.h"

namespace Arc
{

bool Arc_InitMemoryTracker( void );

void Arc_CleanupMemoryTracker( void );

class ManagedObject;

class MemoryTracker
{

	friend bool Arc_InitMemoryTracker( void );
	friend void Arc_CleanupMemoryTracker( void );
	friend class ManagedObject;

private:

	struct AllocationRecord
	{
		int Num;

		int LineNum;

		size_t Size;

		string Filename;

		AllocationRecord(int num, size_t size, int lineNum, string filename)
			: Num(num),
			  LineNum(lineNum),
			  Size(size),
			  Filename(filename)
		{ }

	}; // struct AllocationRecord

	unsigned int m_AllocationIndex;

	Map<ManagedObject*, AllocationRecord> m_Allocations;

	inline MemoryTracker( void )
		: m_AllocationIndex(),
	      m_Allocations()
	{ }

	inline ~MemoryTracker( void ) { }

	MemoryTracker( const MemoryTracker& );
	MemoryTracker& operator=( const MemoryTracker& );

public:

	inline string getClassName( void ) const { return "Arc Memory Tracker"; }

	void addAllocation( ManagedObject *ptr, size_t size, int lineNumber, string filename );

	bool removeAllocation( ManagedObject *ptr );

	inline int getNumAllocations( void ) { return m_Allocations.getSize(); }

	inline void printAllocations( void ) { printAllocations(std::cout); }

	void printAllocations( std::ostream& stream );

}; // class MemoryTracker

extern MemoryTracker* gp_MemoryTracker;

inline unsigned int Arc_GetMemoryAllocationCount( void )
{
	if (gp_MemoryTracker)
		return gp_MemoryTracker->getNumAllocations();

	return -1;
}

inline void Arc_PrintMemoryAllocations( void )
{
	if (gp_MemoryTracker)
		gp_MemoryTracker->printAllocations();
}

inline void Arc_PrintMemoryAllocations( std::ostream& stream )
{
	if (gp_MemoryTracker)
		gp_MemoryTracker->printAllocations(stream);
}


} // namespace Arc

#endif // ARC_CORE_MEMORY_TRACKER_H