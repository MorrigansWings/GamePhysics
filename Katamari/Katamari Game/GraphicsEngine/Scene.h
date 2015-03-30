#ifndef GRAPHICS_II_SCENE_H
#define GRAPHICS_II_SCENE_H

#include <SDL/SDL.h>
#include <Arc/ManagedObject.h>

#include "ResourceManager.h"
#include "Camera.h"

class Entity;
class Skybox;
class Water;
class HeightMap;
struct RenderData;
struct EntityDepthCmp;

using namespace Arc;

class Scene :
	public ManagedObject
{
public:

	Scene( void );
	virtual ~Scene( void );

	virtual inline string getClassName( void ) const { return "Scene"; }

	void hookResize( int width, int height );

	void hookKeyDown( int key );
	void hookKeyUp  ( int key );
	void hookKeyHeld( int key );

	void hookMouseDown ( int button );
	void hookMouseUp   ( int button );
	void hookMouseMoved( float x, float y );
	void hookMouseScrolled( float scrollX, float scrollY );

	void loadSkybox( const string& filename );

	void addEntity( const string& name, Entity* pEntity );
	void addHeightMap( const string& name, HeightMap* pEntity );

	inline Camera* addCamera( const string& name, Camera* pCamera ) { if (m_Cameras.containsKey(name)) { printf("HELP\n"); } m_Cameras.add(name, pCamera); return pCamera; }
	inline Camera* getCamera( const string& name ) { return (m_Cameras.containsKey(name) ? m_Cameras[name] : nullptr); }

	void addWater( const string& name, Water* pWater );
	void addCloud( Entity* pCloud );
	void addShrub( Entity* pShrub );

	inline bool hasCurrentCamera( void ) const { return (mp_CurrentCamera != nullptr); }
	inline void setCurrentCamera( const string& name ) { if (m_Cameras.containsKey(name)) setCurrentCamera(m_Cameras[name]); }
	inline void setCurrentCamera( Camera* pCamera ) { mp_CurrentCamera = pCamera; }
	inline Camera* getCurrentCamera( void ) { return mp_CurrentCamera; }

	void cycleCameras( void );

	void update( float deltaTime );
	void render( void );
	HeightMap* getHeightMap();

private:

	RenderData*				mp_RenderData;

	Map<string, Entity*>	m_Entities;

	ArrayList<Water*>		m_Water;

	ArrayList<Entity*>		m_Clouds;

	ArrayList<Entity*>		m_Foliage;

	Map<string, Camera*>	m_Cameras;

	Camera*					mp_CurrentCamera;

	Skybox*					mp_Skybox;

	//////////////////////////////////////////////////////////////////////////

	bool					m_ChangingView;

	GLfloat					m_MoveSpeed,
							m_LookSpeed,
							m_ElapsedTime;
	HeightMap* mp_HeightMap;
};

#endif // GRAPHICS_II_SCENE_H