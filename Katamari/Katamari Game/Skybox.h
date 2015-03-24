#ifndef GRAPHICS_II_SKYBOX_H
#define GRAPHICS_II_SKYBOX_H

#include "Entity.h"

class Skybox :
	public Entity
{
public:

	inline Skybox( void ) 
		: Entity(),
		  mp_Tex(nullptr)
	{
		m_LightingAffected = false;
	}

	inline Skybox( const string& filename ) 
		: Entity(),
		  mp_Tex(nullptr)
	{
		m_LightingAffected = false;
		load(filename);
	}

	virtual inline ~Skybox( void ) { }

	virtual inline string getClassName( void ) const { return "Skybox"; }

	bool load( const string& filename );

	virtual void preRender ( const RenderData* pData );
	virtual void postRender( const RenderData* pData );

private:

	Texture				*mp_Tex;

};

#endif // GRAPHICS_II_SKYBOX_H