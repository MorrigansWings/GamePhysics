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

#ifndef ARC_DATA_CSV_FACE_H
#define ARC_DATA_CSV_FACE_H

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

#include <Arc/Buffer.h>
#include <Arc/Vector3.h>

#include "CSVRow.h"

namespace Arc
{

class OBJDocument;

class OBJFace
	: public ManagedObject
{

	friend class OBJDocument;

public:

	static OBJFace INVALID;

	inline OBJFace( const OBJFace& rhs )
		: mp_Document(rhs.mp_Document),
		  m_VertexIndexes(rhs.m_VertexIndexes),
		  m_NormalIndexes(rhs.m_NormalIndexes),
		  m_TextureVertexIndexes(rhs.m_TextureVertexIndexes)
	{ }

	inline void operator=( const OBJFace& rhs )
	{ 
		mp_Document = rhs.mp_Document;
		m_VertexIndexes = rhs.m_VertexIndexes;
		m_NormalIndexes = rhs.m_NormalIndexes;
		m_TextureVertexIndexes = rhs.m_TextureVertexIndexes;
	}

	virtual inline ~OBJFace( void ) { }

	virtual inline string getClassName( void ) const { return "Arc OBJ Face"; }

	inline int getNumVertices( void ) const { return m_VertexIndexes.getSize(); }

	inline int getNumNormals( void ) const { return m_NormalIndexes.getSize(); }

	inline int getNumTextureVertices( void ) const { return m_TextureVertexIndexes.getSize(); }

	Vector3 getVertex( const int& index ) const;

	Vector3 getNormal( const int& index ) const;

	Vector2 getTextureVertex( const int& index ) const;

	inline bool hasVertices( void ) const { return ! m_VertexIndexes.isEmpty(); }

	inline bool hasNormals( void ) const { return ! m_NormalIndexes.isEmpty(); }

	inline bool hasTextureVertices( void ) const { return ! m_TextureVertexIndexes.isEmpty(); }

private:

	inline OBJFace( const OBJDocument* pDocument )
		: mp_Document(pDocument),
		  m_VertexIndexes(),
		  m_NormalIndexes(),
		  m_TextureVertexIndexes()
	{ }

	inline void addVertexIndex( const int& vertexIndex ) { m_VertexIndexes.add(vertexIndex); }

	inline void addNormalIndex( const int& normalIndex ) { m_NormalIndexes.add(normalIndex); }

	inline void addTextureVertexIndex( const int& texVertexIndex ) { m_TextureVertexIndexes.add(texVertexIndex); }

	inline void setDocument( const OBJDocument* pDocument ) { mp_Document = pDocument; }

	const OBJDocument* mp_Document;

	ArrayList<int> m_VertexIndexes;

	ArrayList<int> m_NormalIndexes;

	ArrayList<int> m_TextureVertexIndexes;

}; // class CSVDocument

} // namespace Arc

#endif // ARC_DATA_CSV_FACE_H
