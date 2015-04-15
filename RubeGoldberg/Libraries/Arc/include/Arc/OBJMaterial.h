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

#ifndef ARC_DATA_OBJ_MATERIAL_H
#define ARC_DATA_OBJ_MATERIAL_H

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

#include <Arc/Vector4.h>

namespace Arc
{

class OBJMaterial
	: public ManagedObject
{
public:

	static OBJMaterial INVALID;

	OBJMaterial( void )
		: m_AmbientColor(),
		  m_DiffuseColor(),
		  m_SpecularColor(),
		  m_SpecularCoeff(),
		  m_Dissolved(),
		  m_IllumMode(),
		  m_AmbientTexMapFilename(),
		  m_DiffuseTexMapFilename(),
		  m_SpecularTexMapFilename(),
		  m_SpecularHilightMapFilename(),
		  m_AlphaMapFilename(),
		  m_BumpMapFilename(),
		  m_DisplacementMapFilename(),
		  m_DecalMapFilename()
	{ }

	OBJMaterial( const OBJMaterial& rhs )
		: m_AmbientColor(rhs.m_AmbientColor),
		  m_DiffuseColor(rhs.m_DiffuseColor),
		  m_SpecularColor(rhs.m_SpecularColor),
		  m_SpecularCoeff(rhs.m_SpecularCoeff),
		  m_Dissolved(rhs.m_Dissolved),
		  m_IllumMode(rhs.m_IllumMode),
		  m_AmbientTexMapFilename(rhs.m_AmbientTexMapFilename),
		  m_DiffuseTexMapFilename(rhs.m_DiffuseTexMapFilename),
		  m_SpecularTexMapFilename(rhs.m_SpecularTexMapFilename),
		  m_SpecularHilightMapFilename(rhs.m_SpecularHilightMapFilename),
		  m_AlphaMapFilename(rhs.m_AlphaMapFilename),
		  m_BumpMapFilename(rhs.m_BumpMapFilename),
		  m_DisplacementMapFilename(rhs.m_DisplacementMapFilename),
		  m_DecalMapFilename(rhs.m_DecalMapFilename)
	{
	}

	void operator=( const OBJMaterial& rhs)
	{
		m_AmbientColor = rhs.m_AmbientColor;
		m_DiffuseColor = rhs.m_DiffuseColor;
		m_SpecularColor = rhs.m_SpecularColor;
		m_SpecularCoeff = rhs.m_SpecularCoeff;
		m_Dissolved = rhs.m_Dissolved;
		m_IllumMode = rhs.m_IllumMode;
		m_AmbientTexMapFilename = rhs.m_AmbientTexMapFilename;
		m_DiffuseTexMapFilename = rhs.m_DiffuseTexMapFilename;
		m_SpecularTexMapFilename = rhs.m_SpecularTexMapFilename;
		m_SpecularHilightMapFilename = rhs.m_SpecularHilightMapFilename;
		m_AlphaMapFilename = rhs.m_AlphaMapFilename;
		m_BumpMapFilename = rhs.m_BumpMapFilename;
		m_DisplacementMapFilename = rhs.m_DisplacementMapFilename;
		m_DecalMapFilename = rhs.m_DecalMapFilename;
	}

	virtual inline ~OBJMaterial( void ) { }

	virtual inline string getClassName( void ) const { return "Arc OBJ Material"; }

	inline Arc::Vector4 getAmbientColor( void ) const { return m_AmbientColor; }
	inline void setAmbientColor( Arc::Vector4 val ) { m_AmbientColor = val; }

	inline Arc::Vector4 getDiffuseColor( void ) const { return m_DiffuseColor; }
	inline void setDiffuseColor( Arc::Vector4 val ) { m_DiffuseColor = val; }

	inline Arc::Vector4 getSpecularColor( void ) const { return m_SpecularColor; }
	inline void setSpecularColor( Arc::Vector4 val ) { m_SpecularColor = val; }

	inline float getSpecularCoeff( void ) const { return m_SpecularCoeff; }
	inline void setSpecularCoeff( float val ) { m_SpecularCoeff = val; }

	inline float getDissolved( void ) const { return m_Dissolved; }
	inline void setDissolved( float val ) { m_Dissolved = val; }

	inline int getIllumMode( void ) const { return m_IllumMode; }
	inline void setIllumMode( int val ) { m_IllumMode = val; }

	inline string getAmbientTexMapFilename( void ) const { return m_AmbientTexMapFilename; }
	inline void setAmbientTexMapFilename( string val ) { m_AmbientTexMapFilename = val; }

	inline string getDiffuseTexMapFilename( void ) const { return m_DiffuseTexMapFilename; }
	inline void setDiffuseTexMapFilename( string val ) { m_DiffuseTexMapFilename = val; }

	inline string getSpecularTexMapFilename( void ) const { return m_SpecularTexMapFilename; }
	inline void setSpecularTexMapFilename( string val ) { m_SpecularTexMapFilename = val; }

	inline string getSpecularHilightMapFilename( void ) const { return m_SpecularHilightMapFilename; }
	inline void setSpecularHilightMapFilename( string val ) { m_SpecularHilightMapFilename = val; }

	inline string getAlphaMapFilename( void ) const { return m_AlphaMapFilename; }
	inline void setAlphaMapFilename( string val ) { m_AlphaMapFilename = val; }

	inline string getBumpMapFilename( void ) const { return m_BumpMapFilename; }
	inline void setBumpMapFilename( string val ) { m_BumpMapFilename = val; }

	inline string getDisplacementMapFilename( void ) const { return m_DisplacementMapFilename; }
	inline void setDisplacementMapFilename( string val ) { m_DisplacementMapFilename = val; }

	inline string getDecalMapFilename( void ) const { return m_DecalMapFilename; }
	inline void setDecalMapFilename( string val ) { m_DecalMapFilename = val; }

private:

	Vector4 m_AmbientColor;

	Vector4 m_DiffuseColor;

	Vector4 m_SpecularColor;

	float m_SpecularCoeff;

	float m_Dissolved;

	// TODO: Turn into enum
	int m_IllumMode;

	string m_AmbientTexMapFilename;

	string m_DiffuseTexMapFilename;

	string m_SpecularTexMapFilename;

	string m_SpecularHilightMapFilename;

	string m_AlphaMapFilename;

	string m_BumpMapFilename;

	string m_DisplacementMapFilename;

	string m_DecalMapFilename;

}; // class OBJMaterial

} // namespace Arc

#endif // ARC_DATA_OBJ_MATERIAL_H