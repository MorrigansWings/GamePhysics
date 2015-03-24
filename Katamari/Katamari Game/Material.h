#ifndef GRAPHICS_II_MATERIAL_H
#define GRAPHICS_II_MATERIAL_H

#include <Arc/ManagedObject.h>

#include "Texture.h"
#include "ShaderManager.h"

class ResourceManager;

using namespace Arc;

class Material :
	public ManagedObject
{

	friend class ResourceManager;

public:

	virtual inline ~Material( void ) { }

	virtual inline string getClassName( void ) const { return "Material"; }

	void bind( void );

	inline vec4 getDiffuseColor( void ) const { return vec4(m_DiffuseColor, 1.0f); }
	inline void setDiffuseColor( const vec4& color ) { m_DiffuseColor = vec3(color); }

	inline vec4 getAmbientColor( void ) const { return vec4(m_AmbientColor, 1.0f); }
	inline void setAmbientColor( const vec4& color ) { m_AmbientColor = vec3(color); }

	inline vec4 getSpecularColor( void ) const { return vec4(m_SpecularColor, 1.0f); }
	inline void setSpecularColor( const vec4& color ) { m_SpecularColor = vec3(color); }

	inline bool hasDiffuseMap( void ) const { return (mp_DiffuseMap != nullptr); }
	inline Texture* getDiffuseMap( void ) const { return mp_DiffuseMap; }
	inline void setDiffuseMap( Texture* pTex ) { mp_DiffuseMap = pTex; }

	inline bool hasAmbientMap( void ) const { return (mp_AmbientMap != nullptr); }
	inline Texture* getAmbientMap( void ) const { return mp_AmbientMap; }
	inline void setAmbientMap( Texture* pTex ) { mp_AmbientMap = pTex; }

	inline bool hasSpecularMap( void ) const { return (mp_SpecularMap != nullptr); }
	inline Texture* getSpecularMap( void ) const { return mp_SpecularMap; }
	inline void setSpecularMap( Texture* pTex ) { mp_SpecularMap = pTex; }

	inline bool hasSpecularHilightMap( void ) const { return (mp_SpecularHilightMap != nullptr); }
	inline Texture* getSpecularHilightMap( void ) const { return mp_SpecularHilightMap; }
	inline void setSpecularHilightMap( Texture* pTex ) { mp_SpecularHilightMap = pTex; }

	inline bool hasAlphaMap( void ) const { return (mp_AlphaMap != nullptr); }
	inline Texture* getAlphaMap( void ) const { return mp_AlphaMap; }
	inline void setAlphaMap( Texture* pTex ) { mp_AlphaMap = pTex; }

	inline bool hasBumpMap( void ) const { return (mp_BumpMap != nullptr); }
	inline Texture* getBumpMap( void ) const { return mp_BumpMap; }
	inline void setBumpMap( Texture* pTex ) { mp_BumpMap = pTex; }

	inline bool hasDisplacementMap( void ) const { return (mp_DisplacementMap != nullptr); }
	inline Texture* getDisplacementMap( void ) const { return mp_DisplacementMap; }
	inline void setDisplacementMap( Texture* pTex ) { mp_DisplacementMap = pTex; }

	inline bool hasDecalMap( void ) const { return (mp_DecalMap != nullptr); }
	inline Texture* getDecalMap( void ) const { return mp_DecalMap; }
	inline void setDecalMap( Texture* pTex ) { mp_DecalMap = pTex; }

private:

	inline Material( void )
		: m_DiffuseColor(1.0f, 1.0f, 1.0f),
		  m_AmbientColor(),
		  m_SpecularColor(),
		  mp_DiffuseMap(nullptr),
		  mp_AmbientMap(nullptr),
		  mp_SpecularMap(nullptr),
		  mp_SpecularHilightMap(nullptr),
		  mp_AlphaMap(nullptr),
		  mp_BumpMap(nullptr),
		  mp_DisplacementMap(nullptr),
		  mp_DecalMap(nullptr)
	{ }

	vec3 m_AmbientColor;

	vec3 m_DiffuseColor;

	vec3 m_SpecularColor;

	Texture* mp_DiffuseMap;

	Texture* mp_AmbientMap;

	Texture* mp_SpecularMap;

	Texture* mp_SpecularHilightMap;

	Texture* mp_AlphaMap;

	Texture* mp_BumpMap;

	Texture* mp_DisplacementMap;

	Texture* mp_DecalMap;

};

#endif // GRAPHICS_II_MATERIAL_H