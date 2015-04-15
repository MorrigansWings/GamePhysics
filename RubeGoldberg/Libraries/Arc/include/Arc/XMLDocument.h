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

#ifndef ARC_DATA_XML_DOCUMENT_H
#define ARC_DATA_XML_DOCUMENT_H

#include <Arc/ManagedObject.h>

#include <Arc/Buffer.h>

#include "XMLElement.h"

namespace Arc
{

class XMLDocument
	: public ManagedObject
{
public:

	inline XMLDocument( void )
		: m_HasError(false),
		  m_Error()
	{ }

	inline XMLDocument( const XMLDocument& rhs )
		: m_HasError(rhs.m_HasError),
		  m_Error(rhs.m_Error)
	{ }

	inline void operator=( const XMLDocument& rhs )
	{
		m_HasError = rhs.m_HasError;
		m_Error = rhs.m_Error;
	}

	inline XMLDocument( const string& filename )
		: m_HasError(false),
		  m_Error()
	{
		loadFile(filename);
	}

	inline XMLDocument( Buffer& buffer )
		: m_HasError(false),
		  m_Error()
	{
		loadBuffer(buffer);
	}

	virtual inline string getClassName( void ) const { return "Arc XML Document"; }

	inline bool loadFile( const string& filename )
	{
		loadBuffer(Buffer::LoadFromFile(filename));
	}

	bool loadBuffer( Buffer& buffer );

	inline bool hasError( void ) const { return m_HasError; }

	inline string getError( void ) const { return m_Error; }

	inline XMLElement* getRoot( void ) { return m_Root; }

private:

	bool m_HasError;

	string m_Error;

	XMLElement* m_Root;

}; // class XMLDocument

} // namespace Arc

#endif // ARC_DATA_XML_DOCUMENT_H