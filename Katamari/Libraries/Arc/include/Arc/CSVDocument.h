/* This file is part of ArcData.
 *
 * ArcData is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ArcData is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcData; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Author: Stephen Lane-Walsh
 *
 */

#ifndef ARC_DATA_CSV_DOCUMENT_H
#define ARC_DATA_CSV_DOCUMENT_H

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

#include "CSVRow.h"

namespace Arc
{

class CSVDocument
	: public ManagedObject
{
public:

	inline CSVDocument( void )
		: m_UseHeadings(false),
		  m_Headings(),
		  m_Rows()
	{ }

	explicit inline CSVDocument( const CSVDocument& rhs )
		: m_UseHeadings(rhs.m_UseHeadings),
		  m_Headings(rhs.m_Headings),
		  m_Rows(rhs.m_Rows)
	{ }

	virtual inline void operator=( const CSVDocument& rhs)
	{
		m_UseHeadings = rhs.m_UseHeadings;
		m_Headings = rhs.m_Headings;
		m_Rows = rhs.m_Rows;
	}

	virtual ~CSVDocument( void );

	virtual inline string getClassName( void ) const { return "Arc CSV Document"; }

	void loadFile( const string& filename );

	void loadFileWithHeadings( const string& filename );

	void loadString( const string& data );

	void loadStringWithHeadings( const string& data );

private:

	bool m_UseHeadings;

	Map<string, int> m_Headings;

	ArrayList<CSVRow> m_Rows;

}; // class CSVDocument

} // namespace Arc

#endif // ARC_DATA_CSV_DOCUMENT_H
