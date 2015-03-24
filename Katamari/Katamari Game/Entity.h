#ifndef GRAPHICS_II_ENTITY_H
#define GRAPHICS_II_ENTITY_H

#include <Arc/ManagedObject.h>

#include "OpenGL.h"

#include "ShaderManager.h"
#include "Model.h"

class Camera;
struct RenderData;

using namespace Arc;

class Entity :
	public ManagedObject
{
public:

	inline Entity( void )
		: m_Models	(),
		  m_Pos		(0.0f, 0.0f, 0.0f),
		  m_Rot		(0.0f, 0.0f, 0.0f),
		  m_Scale	(1.0f, 1.0f, 1.0f),
		  m_LightingAffected(true)
	{ }

	inline Entity( const vec3& pos, const vec3& rot = vec3(0.0f, 0.0f, 0.0f), const vec3& scale = vec3(1.0f, 1.0f, 1.0f) )
		: m_Models	(),
		  m_Pos		(pos),
		  m_Rot		(rot),
		  m_Scale	(scale),
		  m_LightingAffected(true)
	{ }

	inline Entity( const Entity& rhs )
		: m_Models	(rhs.m_Models),
		  m_Pos		(rhs.m_Pos),
		  m_Rot		(rhs.m_Rot),
		  m_Scale	(rhs.m_Scale),
		  m_LightingAffected(rhs.m_LightingAffected)
	{ }

	virtual inline ~Entity( void ) { }

	virtual inline string getClassName( void ) const { return "Entity"; }

	virtual void render( const RenderData* pData );
	virtual void update( const double& deltaTime );

	virtual void preRender ( const RenderData* pData );
	virtual void doRender  ( const RenderData* pData );
	virtual void postRender( const RenderData* pData );

	void addModel( Model* pModel ) { m_Models.add(pModel); }

	void removeModels( void );

	inline vec3 getPos( void ) const { return m_Pos; }
	inline void setPos( vec3 pos ) { m_Pos = pos; }

	inline vec3 getRot( void ) const { return m_Rot; }
	inline void setRot( vec3 rot ) { m_Rot = rot; }

	inline vec3 getScale( void ) const { return m_Scale; }
	inline void setScale( vec3 scale ) { m_Scale = scale; }

	inline bool isLightingAffected( void ) const { return m_LightingAffected; }
	inline void setLightingAffected( bool lightingAffected ) { m_LightingAffected = lightingAffected; }
	
	float getDistanceFromCamera( Camera* pCamera ) const;

protected:

	ArrayList<Model*>		m_Models;

	vec3					m_Pos,
							m_Rot,
							m_Scale;

	bool					m_LightingAffected;

};

#endif // GRAPHICS_II_ENTITY_H