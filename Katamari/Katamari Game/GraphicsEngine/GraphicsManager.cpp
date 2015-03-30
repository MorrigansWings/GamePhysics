#include "GraphicsManager.h" 

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "SceneManager.h"
#include "ResourceManager.h"
#include "ShaderManager.h"
#include "Log.h"
#include "Debug.h"
#include "Geometry.h"
#include "Entity.h"
#include "Model.h"
#include "Mesh.h"
#include "Scene.h"
#include "HeightMap.h"
#include "Config.h"

GraphicsManager* GraphicsManager::s_Instance = nullptr;

GraphicsManager::GraphicsManager( int argc, char* argv[] ) 
	: mp_Window			(nullptr),
	  mp_ResourceManager(nullptr),
	  mp_ShaderManager	(nullptr),
	  mp_SceneManager   (nullptr),
	  m_Width			(0),
	  m_Height			(0),
	  m_Title			(),
	  m_Fullscreen		(false),
	  m_LastFrameTime	(0.0f),
	  m_ClearColor      ()
{
	s_Instance = this;

	Config::LoadFile("Config/settings.cfg");

	m_Width  = Config::GetInt("WindowWidth");
	m_Height = Config::GetInt("WindowHeight");
	m_Title  = Config::GetString("WindowTitle");
	m_Fullscreen = Config::GetBool("Fullscreen");
	m_ClearColor = Config::GetColor("ClearColor");

	if ( ! glfwInit())
	{
		Log::Error("Main", "Failed to initialize GLFW");
		system("PAUSE");
		term();
		exit(EXIT_FAILURE);
	}

	int sdlFlags = SDL_INIT_TIMER | SDL_INIT_AUDIO;
	if (SDL_Init(sdlFlags) != 0)
	{
		Log::Error(getClassName(), "Failed to initialize SDL");
		system("PAUSE");
		term();
		exit(EXIT_FAILURE);
	}

	int sdlImageFlags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	if ((IMG_Init(sdlImageFlags) & sdlImageFlags) != sdlImageFlags)
	{
		Log::Error(getClassName(), "Failed to initialize SDL_image");
		system("PAUSE");
		term();
		exit(EXIT_FAILURE);
	}

	initWindow();
	initGL();

	glewExperimental = GL_TRUE;
	GLenum ret = glewInit();
	if (ret != GLEW_OK)
	{
		Log::ErrorFmt(getClassName(), "Failed to initialize GLEW (Error #%d, %s)", ret, glewGetErrorString(ret));
		system("PAUSE");
		term();
		exit(EXIT_FAILURE);
	}
	
	Log::InfoFmt(getClassName(), "Running OpenGL Version %s", glGetString(GL_VERSION));
	Log::InfoFmt(getClassName(), "Running OpenGL Shading Language Version %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	mp_ResourceManager = New ResourceManager();
	mp_ShaderManager   = New ShaderManager();
	mp_SceneManager    = New SceneManager();

	Config::LoadFile("Config/resources.cfg");

	Debug::SetBool("wireframe-mode",   false);
	Debug::SetBool("fly-through-mode", false);




	Mesh* pMesh = mp_ResourceManager->addMesh("test-mesh");
	Model* pModel = mp_ResourceManager->addModel("test-model");
	pModel->addMesh(pMesh);

	ArrayList<vec3> verts;
	verts.add(vec3(0.0f, 0.0f, 0.0f));
	verts.add(vec3(0.0f, 5.0f, 0.0f));
	verts.add(vec3(0.0f, 5.0f, 5.0f));
	verts.add(vec3(0.0f, 0.0f, 5.0f));
	verts.add(vec3(5.0f, 0.0f, 5.0f));

	pMesh->begin(GL_LINES, 5);
	pMesh->copyVertexData(verts);
	pMesh->end();

	mp_TestEntity = New Entity(vec3(0.0f), vec3(0.0f), vec3(1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f));
	mp_TestEntity->addModel(pModel);
	mp_SceneManager->getCurrentScene()->addEntity("test-entity", mp_TestEntity);
}

SceneManager* GraphicsManager::getSceneManager( void )
{
	return mp_SceneManager;
}

ResourceManager* GraphicsManager::getResourceManager( void )
{
	return mp_ResourceManager;
}

ShaderManager* GraphicsManager::getShaderManager( void )
{
	return mp_ShaderManager;
}

void GraphicsManager::term( void )
{
	delete mp_TestEntity;

	delete mp_SceneManager;
	delete mp_ShaderManager;
	delete mp_ResourceManager;

	IMG_Quit();
	SDL_Quit();

	glfwTerminate();
}

void GraphicsManager::start( void )
{
	while( ! glfwWindowShouldClose(mp_Window) )
	{
		const float updateInt = 1.0f / 60.0f;
		static float updateTimer = 0.0f;

		double currTime = glfwGetTime();
		float deltaTime = (float)(currTime - m_LastFrameTime);
		m_LastFrameTime = currTime;

		updateTimer += deltaTime;

		if (updateTimer >= updateInt)
		{
			updateTimer = 0.0f;
			deltaTime = updateInt; // Actual time since last update/render

			update(deltaTime);
			render();
			glfwSwapBuffers(mp_Window);
		}

		glfwPollEvents();
	}
}

void GraphicsManager::update( float deltaTime )
{
	mp_SceneManager->update(deltaTime);
}

void GraphicsManager::render( void )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearDepth(1.0f);
	
	mp_SceneManager->render();
}

void GraphicsManager::hookResize( int width, int height )
{
	m_Width = width;
	m_Height = height;

	glViewport(0, 0, m_Width, m_Height);

	mp_SceneManager->hookResize(width, height);
}

void GraphicsManager::hookKeyDown( int key )
{
	switch (key)
	{
	case 27: // ESCAPE

		term();

		break;
	case GLFW_KEY_ESCAPE:

		glfwDestroyWindow(mp_Window);

		break;
	case GLFW_KEY_TAB:

		Debug::ToggleBool("fly-through-mode");

		break;
	case GLFW_KEY_F1:

		if (mp_SceneManager->getCurrentScene()->hasCurrentCamera())
			mp_SceneManager->getCurrentScene()->getCurrentCamera()->reset();

		break;
	case GLFW_KEY_F2:

		screenshot();

		break;
	case GLFW_KEY_F3:

		Debug::ToggleBool("wireframe-mode");

		if (Debug::GetBool("wireframe-mode"))
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		else
			glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

		break;
	}

	mp_SceneManager->hookKeyDown(key);
}

void GraphicsManager::hookKeyUp( int key )
{
	//switch (key)
	//{
	//}

	mp_SceneManager->hookKeyUp(key);
}

void GraphicsManager::hookKeyHeld( int key )
{
	//switch (key)
	//{
	//}

	mp_SceneManager->hookKeyHeld(key);
}

void GraphicsManager::hookMouseDown( int button )
{
	switch (button)
	{
	case 0: // Left

		break;
	case 1: // Right

		break;
	}

	mp_SceneManager->hookMouseDown(button);
}

void GraphicsManager::hookMouseUp( int button )
{
	switch (button)
	{
	case 0: // Left

		break;
	case 1: // Right

		break;
	}

	mp_SceneManager->hookMouseUp(button);
}

void GraphicsManager::hookMouseMoved( float x, float y )
{
	mp_SceneManager->hookMouseMoved(x, y);
}

void GraphicsManager::hookMouseScrolled( float scrollX, float scrollY )
{
	mp_SceneManager->hookMouseScrolled(scrollX, scrollY);
}

void GraphicsManager::initGL( void )
{
	glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);

	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GraphicsManager::initWindow( void )
{
	glfwWindowHint(GLFW_DEPTH_BITS, 16);

	GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();

	if (m_Fullscreen)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(pMonitor);

		if (mode->width > 0 && mode->height > 0)
		{
			m_Width = mode->width;
			m_Height = mode->height;
		}
	}

	mp_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), (m_Fullscreen ? pMonitor : NULL), NULL);

	if ( ! mp_Window )
	{
		Log::Error("Main", "Failed to open GLFW window");
		system("PAUSE");
		term();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(mp_Window);

	glfwSwapInterval(0);
}

void GraphicsManager::screenshot( const string& filename /*= "" */ )
{
	string tmpFilename = filename;
	if (tmpFilename == "")
	{
		stringstream ss;
		ss << "Screenshot_" << time(0) << ".bmp";

		tmpFilename = ss.str();
	}

	SDL_Surface* pTmp = SDL_CreateRGBSurface(SDL_SWSURFACE, m_Width, m_Height, 24, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);

	char * pixels = new char [3 * m_Width * m_Height];

	glReadPixels(0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	for (int i = 0 ; i < m_Height ; i++)
		std::memcpy( ((char *) pTmp->pixels) + pTmp->pitch * i, pixels + 3 * m_Width * (m_Height - i - 1), m_Width * 3 );

	delete [] pixels;

	SDL_SaveBMP(pTmp, tmpFilename.c_str());

	SDL_FreeSurface(pTmp);

	Log::InfoFmt(getClassName(), "Screenshot saved to %s", tmpFilename.c_str());
}
