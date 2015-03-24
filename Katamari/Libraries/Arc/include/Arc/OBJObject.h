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

#ifndef ARC_DATA_OBJ_OBJECT_H
#define ARC_DATA_OBJ_OBJECT_H

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

namespace Arc
{

class OBJDocument;
class OBJFace;
class OBJMaterial;

class OBJObject
	: public ManagedObject
{

	friend class OBJDocument;

public:

	static OBJObject INVALID;

	inline OBJObject( void )
		: mp_Document(nullptr),
		  m_MaterialName(),
		  m_FaceStartInd(),
		  m_FaceEndInd()
	{ }

	inline OBJObject( const OBJObject& rhs )
		: mp_Document(rhs.mp_Document),
		  m_MaterialName(rhs.m_MaterialName),
		  m_FaceStartInd(rhs.m_FaceStartInd),
		  m_FaceEndInd(rhs.m_FaceEndInd)
	{ }

	inline void operator=( const OBJObject& rhs )
	{
		mp_Document = rhs.mp_Document;
		m_MaterialName = rhs.m_MaterialName;
		m_FaceStartInd = rhs.m_FaceStartInd;
		m_FaceEndInd = rhs.m_FaceEndInd;
	}

	virtual inline ~OBJObject( void ) { }

	virtual inline string getClassName( void ) const { return "Arc OBJ Object"; }

	inline unsigned int getNumFaces( void ) const { return (m_FaceEndInd - m_FaceStartInd) + 1; }

	OBJFace& getFace( const int& index );

	OBJMaterial& getMaterial( void );

	inline string getMaterialName( void ) const { return m_MaterialName; }
	inline void setMaterialName( string val ) { m_MaterialName = val; }

	inline int getFaceStartInd( void ) const { return m_FaceStartInd; }
	inline void setFaceStartInd( int val ) { m_FaceStartInd = val; }

	inline int getFaceEndInd( void ) const { return m_FaceEndInd; }
	inline void setFaceEndInd( int val ) { m_FaceEndInd = val; }

private:

	inline OBJObject( OBJDocument* pDocument )
		: mp_Document(pDocument),
		  m_MaterialName(),
		  m_FaceStartInd(),
		  m_FaceEndInd()
	{ }

	inline void setDocument( OBJDocument* pDocument ) { mp_Document = pDocument; }

	OBJDocument* mp_Document;

	string m_MaterialName;

	int m_FaceStartInd;

	int m_FaceEndInd;

	
}; // class OBJObject

} // namespace Arc

#endif // ARC_DATA_OBJ_OBJECT_H