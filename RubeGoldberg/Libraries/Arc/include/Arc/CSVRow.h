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

#ifndef ARC_DATA_CSV_ROW_H
#define ARC_DATA_CSV_ROW_H

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

namespace Arc
{

class CSVDocument;

class CSVRow
	: public ManagedObject
{
public:

	string getCol( const int& index );
	string getCol( const string& index );

	ArrayList<string> getCols( void );
	ArrayList<string> getCols( const int& start, const int& end );
	ArrayList<string> getCols( const ArrayList<int>& indexes );
	ArrayList<string> getCols( const ArrayList<string>& indexes );

	virtual ~CSVRow( void );

	virtual inline string getClassName( void ) const { return "CSV Row"; }

private:

	CSVRow( CSVDocument& document );

	CSVDocument* mp_Document;

	ArrayList<string> m_Cols;

}; // class CSVRow

} // namespace Arc

#endif // ARC_DATA_CSV_ROW_H
