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

#ifndef ARC_DATA_PLY_ELEMENT_TYPE_H
#define ARC_DATA_PLY_ELEMENT_TYPE_H

#include <Arc/ManagedObject.h>

#include <Arc/Map.h>

#include "PLYPropertyTypes.h"

namespace Arc
{

class PLYDocument;

class PLYElementType 
	: public ManagedObject
{

	friend class PLYDocument;

public:

	static PLYElementType INVALID;

	explicit inline PLYElementType( void )
		: m_IsList(false),
		  m_ExpectedCount(),
		  m_PropertyNames(),
		  m_PropertyTypes(),
		  m_ListSizeType(PLYPropertyTypes::PROP_TYPE_INVALID),
		  m_ListType(PLYPropertyTypes::PROP_TYPE_INVALID),
		  m_ListName()
	{ }

	explicit inline PLYElementType( const unsigned int& expectedCount )
		: m_IsList(false),
		  m_ExpectedCount(expectedCount),
		  m_PropertyNames(),
		  m_PropertyTypes(),
		  m_ListSizeType(PLYPropertyTypes::PROP_TYPE_INVALID),
		  m_ListType(PLYPropertyTypes::PROP_TYPE_INVALID),
		  m_ListName()
	{ }

	inline PLYElementType( const PLYElementType& rhs )
		: m_IsList(rhs.m_IsList),
		  m_ExpectedCount(rhs.m_ExpectedCount),
		  m_PropertyNames(rhs.m_PropertyNames),
		  m_PropertyTypes(rhs.m_PropertyTypes),
		  m_ListSizeType(rhs.m_ListSizeType),
		  m_ListType(rhs.m_ListType),
		  m_ListName(rhs.m_ListName)
	{ }

	virtual inline string getClassName( void ) const { return "Arc PLY Element Type"; }

	inline bool isList( void ) const { return m_IsList; }

	inline void setIsList( const bool& isList ) { m_IsList = isList; }

	inline PLYPropertyType getListSizeType( void ) const { return m_ListSizeType; }

	inline void setListSizeType( const PLYPropertyType& type ) { m_ListSizeType = type; }

	inline PLYPropertyType getListType( void ) const { return m_ListType; }

	inline void setListType( const PLYPropertyType& type ) { m_ListType = type; }

	inline string getListName( void ) const { return m_ListName; }

	inline void setListName( const string& name ) { m_ListName = name; }

	void addPropertyType( const string& type, const string& name );

	inline unsigned int getNumProperties( void ) const { return m_PropertyNames.getSize(); }

	inline PLYPropertyType getPropertyType( const string& name ) { return (m_PropertyTypes.containsKey(name) ? m_PropertyTypes[name] : PLYPropertyTypes::PROP_TYPE_INVALID); }

	inline PLYPropertyType getPropertyType( const int& index ) { return (m_PropertyNames.hasIndex(index) ? getPropertyType(m_PropertyNames[index]) : PLYPropertyTypes::PROP_TYPE_INVALID); }

	inline string getPropertyName( const int& index ) { return (m_PropertyNames.hasIndex(index) ? m_PropertyNames[index] : ""); }

private:

	inline unsigned int getExpectedCount( void ) const { return m_ExpectedCount; }

	bool m_IsList;

	unsigned int m_ExpectedCount;

	ArrayList<string> m_PropertyNames;

	Map<string, PLYPropertyType> m_PropertyTypes;
	
	PLYPropertyType m_ListSizeType;
	
	PLYPropertyType m_ListType;

	string m_ListName;

}; // class PLYElementType

} // namespace Arc

#endif // ARC_DATA_PLY_ELEMENT_TYPE_H