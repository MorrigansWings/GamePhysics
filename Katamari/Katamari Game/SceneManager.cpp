#include "SceneManager.h"

#include "Game.h"

SceneManager::SceneManager( void )
	: m_Scenes(),
	  mp_CurrentScene(nullptr)
{
}

SceneManager::~SceneManager( void )
{
	for (auto it = m_Scenes.itBegin(); it != m_Scenes.itEnd(); ++it)
	{
		Scene* pScene = it->second;
		delete pScene;
	}
	m_Scenes.clear();
}

bool SceneManager::setCurrentScene( const string& name )
{
	if ( ! hasScene(name))
		return false;

	mp_CurrentScene = getScene(name);
	return true;
}

string SceneManager::getSafeSceneName( const string& name )
{
	if ( ! m_Scenes.containsKey(name))
		return name;

	stringstream ss;
	int index = 0;

	do 
	{
		ss.clear(); ss.str(name);
		ss << index;
		++index;
	}
	while (m_Scenes.containsKey(ss.str()));

	return ss.str();
}

void SceneManager::update( float deltaTime )
{
	if (mp_CurrentScene)
		mp_CurrentScene->update(deltaTime);
}

void SceneManager::render( void )
{
	if (mp_CurrentScene)
		mp_CurrentScene->render();
}

void SceneManager::hookResize( int width, int height )
{
	if (mp_CurrentScene)
		mp_CurrentScene->hookResize(width, height);
}

void SceneManager::hookKeyDown( int key )
{
	switch (key)
	{
	case GLFW_KEY_F4:

		cycleScenes();

		break;
	}

	if (mp_CurrentScene)
		mp_CurrentScene->hookKeyDown(key);
}

void SceneManager::hookKeyUp( int key )
{
	if (mp_CurrentScene)
		mp_CurrentScene->hookKeyUp(key);
}

void SceneManager::hookKeyHeld( int key )
{
	if (mp_CurrentScene)
		mp_CurrentScene->hookKeyHeld(key);
}

void SceneManager::hookMouseDown( int button )
{
	if (mp_CurrentScene)
		mp_CurrentScene->hookMouseDown(button);
}

void SceneManager::hookMouseUp( int button )
{
	if (mp_CurrentScene)
		mp_CurrentScene->hookMouseUp(button);
}

void SceneManager::hookMouseMoved( float x, float y )
{
	if (mp_CurrentScene)
		mp_CurrentScene->hookMouseMoved(x, y);
}

void SceneManager::hookMouseScrolled( float scrollX, float scrollY )
{
	if (mp_CurrentScene)
		mp_CurrentScene->hookMouseScrolled(scrollX, scrollY);
}

void SceneManager::cycleScenes( void )
{
	if (m_Scenes.getSize() <= 1)
		return;

	const string& key = m_Scenes.getIndexOf(mp_CurrentScene);
	auto it = m_Scenes.find(key);

	++it;

	if (it == m_Scenes.itEnd())
	{
		it = m_Scenes.itBegin();
	}

	mp_CurrentScene = it->second;
}
