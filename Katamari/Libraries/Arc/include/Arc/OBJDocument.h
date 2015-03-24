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

#ifndef ARC_DATA_OBJ_DOCUMENT_H
#define ARC_DATA_OBJ_DOCUMENT_H

#include <cstdlib>

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

#include <Arc/Buffer.h>
#include <Arc/ParseFunctions.h>
#include <Arc/ArrayList.h>
#include <Arc/Vector2.h>
#include <Arc/Vector3.h>

#include "OBJFace.h"
#include "OBJObject.h"
#include "OBJMaterial.h"

namespace Arc
{

class OBJDocument
	: public ManagedObject
{
public:

	OBJDocument( void )
		: m_Filename(),
		  m_Vertices(),
		  m_Normals(),
		  m_TexVertices(),
		  m_Faces(),
		  m_Objects(),
		  m_Materials()
	{ }

	OBJDocument( const OBJDocument& rhs )
		: m_Filename(),
		  m_Vertices(rhs.m_Vertices),
		  m_Normals(rhs.m_Normals),
		  m_TexVertices(rhs.m_TexVertices),
		  m_Faces(rhs.m_Faces),
		  m_Objects(rhs.m_Objects),
		  m_Materials(rhs.m_Materials)
	{
		resetChildPointers();
	}

	void operator=( const OBJDocument& rhs)
	{
		m_Filename = rhs.m_Filename;
		m_Vertices = rhs.m_Vertices;
		m_Normals = rhs.m_Normals;
		m_TexVertices = rhs.m_TexVertices;
		m_Faces = rhs.m_Faces;
		m_Objects = rhs.m_Objects;
		m_Materials = rhs.m_Materials;

		resetChildPointers();
	}

	virtual inline ~OBJDocument( void ) { }

	virtual inline string getClassName( void ) const { return "Arc OBJ Document"; }

	void loadFile( const string& filename );

	void loadString( const string& data );

	void loadBuffer( Buffer& data );

	void reset( void );

	inline string getFilename( void ) const { return m_Filename; }

	inline unsigned int getNumVertices( void ) const { return m_Vertices.getSize(); }

	inline unsigned int getNumNormals( void ) const { return m_Normals.getSize(); }

	inline unsigned int getNumTextureVertices( void ) const { return m_TexVertices.getSize(); }

	inline unsigned int getNumFaces( void ) const { return m_Faces.getSize(); }

	inline void addVertex( const Vector3& vertex ) { m_Vertices.add(vertex); }

	inline void addNormal( const Vector3& normal ) { m_Normals.add(normal); }

	inline void addTextureVertex( const Vector2& texVertex ) { m_TexVertices.add(texVertex); }

	inline OBJFace& addFace( void ) { m_Faces.add(OBJFace(this)); return m_Faces.getBack(); }

	inline OBJObject& addObject( const string& name ) { m_Objects.add(name, OBJObject(this)); return m_Objects[name]; }

	inline OBJMaterial& addMaterial( const string& name ) { m_Materials.add(name, OBJMaterial()); return m_Materials[name]; }

	inline Vector3 getVertex( const int& index ) const { return (m_Vertices.hasIndex(index) ? m_Vertices[index] : Vector3::NEGATIVE_ONE); }

	inline Vector3 getNormal( const int& index ) const { return (m_Normals.hasIndex(index) ? m_Normals[index] : Vector3::NEGATIVE_ONE); }

	inline Vector2 getTextureVertex( const int& index ) const { return (m_TexVertices.hasIndex(index) ? m_TexVertices[index] : Vector2::NEGATIVE_ONE); }

	inline OBJFace& getFace( const int& index ) { return (m_Faces.hasIndex(index) ? m_Faces[index] : OBJFace::INVALID); }

	inline OBJObject& getObject( const string& name ) { return (m_Objects.containsKey(name) ? m_Objects[name] : OBJObject::INVALID); }

	inline OBJMaterial& getMaterial( const string& name ) { return (m_Materials.containsKey(name) ? m_Materials[name] : OBJMaterial::INVALID); }

	ArrayList<string> getObjectNames( void ) const;

private:

	void resetChildPointers( void );

	void loadMaterialFile( const string& filename );

	string m_Filename;

	ArrayList<Vector3> m_Vertices;

	ArrayList<Vector3> m_Normals;

	ArrayList<Vector2> m_TexVertices;

	ArrayList<OBJFace> m_Faces;

	Map<string, OBJObject> m_Objects;

	Map<string, OBJMaterial> m_Materials;

}; // class OBJDocument

} // namespace Arc

#endif // ARC_DATA_OBJ_DOCUMENT_H
