#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

#include <Arc/ManagedObject.h>

#include "OpenGL.h"
#include "SceneManager.h"

class ShaderManager;
class ResourceManager;
class Scene;
class Entity;

class GraphicsManager :
	public ManagedObject
{
public:

	static GraphicsManager* GetInstance( void ) { return s_Instance; }

	GraphicsManager( int argc, char* argv[] );

	virtual inline ~GraphicsManager( void ) { term(); }

	virtual inline string getClassName( void ) const { return "GraphicsManager"; }

	SceneManager*    getSceneManager   ( void );
	ResourceManager* getResourceManager( void );
	ShaderManager*   getShaderManager  ( void );

	void term( void );

	void start( void );

	void update( float deltaTime );
	void render( void );
	void draw( void );

	void hookResize( int width, int height );

	void hookKeyDown( int key );
	void hookKeyUp  ( int key );
	void hookKeyHeld( int key );

	void hookMouseDown( int button );
	void hookMouseUp  ( int button );
	void hookMouseMoved( float x, float y );
	void hookMouseScrolled( float scrollX, float scrollY );

	inline string getTitle( void ) const { return m_Title; }
	inline void setTitle( const string& title )
	{
		m_Title = title;
		glfwSetWindowTitle(mp_Window, m_Title.c_str());
	}

	inline int getWidth( void ) const { return m_Width; }
	inline void setWidth( const int& width ) 
	{ 
		m_Width = width; 
		glfwSetWindowSize(mp_Window, m_Width, m_Height);
	}

	inline int getHeight( void ) const { return m_Height; }
	inline void setHeight( const int& height )
	{ 
		m_Height = height;
		glfwSetWindowSize(mp_Window, m_Width, m_Height);
	}

	inline void setSize( int width, int height ) 
	{
		m_Width = width;
		m_Height = height; 
		glfwSetWindowSize(mp_Window, m_Width, m_Height); 
	}

	inline bool isFullscreen( void ) const { return m_Fullscreen; }

	inline int shouldWindowClose() { return glfwWindowShouldClose(mp_Window); }

	void screenshot( const string& filename = "" );

	inline GLFWwindow* getGLFWWindow( void ) { return mp_Window; }
	inline void pollEvents() { glfwPollEvents(); }

	// object creation functions
	string createLine(string name, vec3 start, vec3 end);
	string createLine(string name, vec3 start, vec3 end, vec4 color);
	void setLineThickness(float width);

	string createPlane(string name);
	string createPlane(string name, vec2 dimensions);
	string createPlane(string name, vec2 dimensions, vec3 position);
	string createPlane(string name, vec2 dimensions, vec3 position, vec4 color);

	string createCube(string name);
	string createCube(string name, vec3 position);
	string createCube(string name, vec3 position, vec3 dimensions);
	string createCube(string name, vec3 position, vec3 dimensions, vec4 color);

	// object manipulation functions
	void updateEntityPosition(string name, vec3 pos);
	void updateEntityRotation(string name, vec3 rot);
	void updateEntityScale(string name, vec3 scale);
	//void updateEntityColor(string name, vec4 col);

	void updateLineEnds(string name, vec3 endOne, vec3 endTwo);

	inline bool hasEntity(string &name){ return mp_SceneManager->getCurrentScene()->hasEntity(name); }

private:
	
	void initGL( void );
	void initWindow( void );

	static GraphicsManager*		s_Instance;

	int					m_Width, 
						m_Height;

	bool				m_Fullscreen;

	GLFWwindow*			mp_Window;

	string				m_Title;

	vec4				m_ClearColor;

	ResourceManager*	mp_ResourceManager;

	ShaderManager*		mp_ShaderManager;

	SceneManager*		mp_SceneManager;

	double				m_LastFrameTime;

	//////////////////////////////////////////////////////////////////////////

	

};

#endif // GRAPHICSMANAGER_H