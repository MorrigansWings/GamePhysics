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

#ifndef ARC_CORE_TEST_GROUP_H
#define ARC_CORE_TEST_GROUP_H

#include <iostream>

#include "ManagedObject.h"

#include "Types.h"
#include "Map.h"

#include "TestResult.h"

namespace Arc
{

typedef TestResult (*TestFunction)( void );

class TestGroup
	: public ManagedObject
{
public:

	inline TestGroup( void )
        : m_Passed(false),
		  m_Tests(),
		  m_TestResults()
	{ }

	inline ~TestGroup( void ) { }

	virtual inline string getClassName( void ) const { return "Arc Test Group"; }

	static inline TestResult Success( void ) { return TestResult(true); }

	static inline TestResult Failure( string msg ) { return TestResult(false, msg); }

	inline bool allTestsPassed( void ) const { return m_Passed; }

	inline int getNumPassed( void ) const
	{
		int count = 0;

		for (auto it = m_TestResults.itConstBegin(); it != m_TestResults.itConstEnd(); ++it)
		{
			if (it->second.m_Passed)
				count++;
		}

		return count;
	}

	inline int getNumFailed( void ) const
	{
		return getNumTests() - getNumPassed();
	}

	inline int getNumTests( void ) const
	{
		return m_Tests.getSize();
	}

	inline void addTest( string funcName, TestFunction func )
	{
		m_Tests.add(funcName, func);
	}

	inline bool runTests( bool verbose = false )
	{
		bool passed = true;
		m_TestResults.clear();

		for (auto it = m_Tests.itBegin(); it != m_Tests.itEnd(); ++it)
		{
			if (verbose)
				std::cout << it->first << ": ";

			m_TestResults.add(it->first, it->second());
			if ( ! m_TestResults[it->first].m_Passed)
			{
				passed = false;
				if (verbose)
					std::cout << "[FAIL]" << std::endl
					          << "\tReason: " << m_TestResults[it->first].m_Message
							  << std::endl;
			}
			else
			{
				if (verbose)
					std::cout << "[PASS]" << std::endl;
			}

		}

		m_Passed = passed;

		return passed;
	}

private:

	bool m_Passed;

	Map<string, TestFunction> m_Tests;

	Map<string, TestResult> m_TestResults;

};

} // namespace Arc

#endif // ARC_CORE_TEST_GROUP_H
