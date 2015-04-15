#ifndef GRAPHICS_II_SCENE_MANAGER_H
#define GRAPHICS_II_SCENE_MANAGER_H

#include "OpenGL.h"
#include <Arc/ManagedObject.h>

#include <Arc/Map.h>

#include "Scene.h"

using namespace Arc;

class Game;

class SceneManager :
	public ManagedObject
{

	friend class Game;

public:

	SceneManager( void );
	virtual ~SceneManager( void );

	virtual inline string getClassName( void ) const { return "Scene Manager"; }

	void hookResize( int width, int height );

	void hookKeyDown( int key );
	void hookKeyUp  ( int key );
	void hookKeyHeld( int key );

	void hookMouseDown ( int button );
	void hookMouseUp   ( int button );
	void hookMouseMoved( float x, float y );
	void hookMouseScrolled( float scrollX, float scrollY );

	inline Scene* getCurrentScene( void ) { return mp_CurrentScene; }
	bool   setCurrentScene( const string& name );

	inline bool   hasScene( const string& name ) { return m_Scenes.containsKey(name); }
	inline Scene* getScene( const string& name ) { return (hasScene(name) ? m_Scenes[name] : nullptr); }
	inline Scene* addScene( const string& name ) { return addScene(name, New Scene()); }
	inline Scene* addScene( const string& name, Scene* pScene ) { m_Scenes.add(getSafeSceneName(name), pScene); return pScene; }

	void update( float deltaTime );
	void render( void );

	void cycleScenes( void );

private:

	string getSafeSceneName( const string& name );

	Map<string, Scene*>		m_Scenes;
	
	Scene*					mp_CurrentScene;

};

#endif // GRAPHICS_II_SCENE_MANAGER_H