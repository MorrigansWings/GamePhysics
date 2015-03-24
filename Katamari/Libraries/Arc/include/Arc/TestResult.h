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

#ifndef ARC_CORE_TEST_RESULT_H
#define ARC_CORE_TEST_RESULT_H

#include "Types.h"

namespace Arc
{

class TestGroup;

struct TestResult
{

	friend class TestGroup;

public:

	TestResult( void )
		: m_Passed(false),
		m_Message()
	{ }

	TestResult( const TestResult& rhs )
		: m_Passed(rhs.m_Passed),
		m_Message(rhs.m_Message)
	{ }

private:

	bool m_Passed;
	string m_Message;

	inline TestResult( bool passed, string msg = "" )
		: m_Passed(passed),
		m_Message(msg)
	{ }

};

} // namespace Arc

#endif // ARC_CORE_TEST_RESULT_H
