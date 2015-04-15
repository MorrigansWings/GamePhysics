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

#ifndef ARC_DATA_XML_ELEMENT_H
#define ARC_DATA_XML_ELEMENT_H

#include <Arc/ManagedObject.h>

#include <Arc/Buffer.h>
#include <Arc/ArrayList.h>
#include <Arc/Map.h>

namespace Arc
{

class XMLElement
	: public ManagedObject
{
public:

	inline XMLElement( void )
		: mp_Parent(nullptr),
		  m_Name(),
		  m_Attrs(),
		  m_Data(),
		  m_Children(),
		  m_IsSingle()
	{ }

	inline XMLElement( const XMLElement& rhs )
		: mp_Parent(rhs.mp_Parent),
		  m_Name(rhs.m_Name),
		  m_Attrs(rhs.m_Attrs),
		  m_Data(rhs.m_Data),
		  m_Children(rhs.m_Children),
		  m_IsSingle(rhs.m_IsSingle)
	{
		attachChildren();
	}

	inline void operator=( const XMLElement& rhs )
	{
		mp_Parent = rhs.mp_Parent;
		m_Name = rhs.m_Name;
		m_Attrs = rhs.m_Attrs;
		m_Data = rhs.m_Data;
		m_Children = rhs.m_Children;
		m_IsSingle = rhs.m_IsSingle;

		attachChildren();
	}
	
	inline XMLElement( XMLElement* pParent )
		: mp_Parent(pParent),
		  m_Name(),
		  m_Attrs(),
		  m_Data(),
		  m_Children(),
		  m_IsSingle()
	{ }

	virtual inline string getClassName( void ) const { return "Arc XML Element"; }

	inline bool isRoot( void ) const { return (mp_Parent == nullptr); }

	XMLElement* getParent( void ) const { return mp_Parent; }

	void setParent( XMLElement* pParent ) { mp_Parent = pParent; }

	inline string getName( void ) const { return m_Name; }

	inline void setName( const string& name ) { m_Name = name; }

	inline bool hasAttr( const string& attr ) const { return m_Attrs.containsKey(attr); }

	inline void setAttr( const string& attr, const string& value ) { (hasAttr(attr) ? m_Attrs.add(attr, value) : m_Attrs[attr] = value); }

	inline string getAttr( const string& attr ) { return (hasAttr(attr) ? m_Attrs[attr] : ""); }

	inline void removeAttr( const string& attr ) { m_Attrs.removeKey(attr); }

	inline string getData( void ) const { return m_Data; }

	inline unsigned int getNumChildren( void ) const { return m_Children.getSize(); }

	inline ArrayList<XMLElement*>& getChildren( void ) { return m_Children; }

	inline XMLElement* getFirstChild( const string& name = "" ) { return ( ! m_Children.isEmpty() ? m_Children.getFront() : nullptr); }

	inline XMLElement* getLastChild( const string& name = "" ) { return ( ! m_Children.isEmpty() ? m_Children.getBack() : nullptr); }

	inline bool getIsSingle( void ) const { return m_IsSingle; }

	inline void setIsSingle( const bool& isSingle ) { m_IsSingle = isSingle; }

private:

	void attachChildren( void );

	XMLElement* mp_Parent;

	string m_Name;

	Map<string, string> m_Attrs;

	string m_Data;

	ArrayList<XMLElement*> m_Children;

	bool m_IsSingle;

}; // class XMLElement

} // namespace Arc

#endif // ARC_DATA_XML_ELEMENT_H