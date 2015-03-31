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
	delete mp_SceneManager;
	delete mp_ShaderManager;
	delete mp_ResourceManager;

	IMG_Quit();
	SDL_Quit();

	glfwTerminate();
}

void GraphicsManager::start( void )
{
/*	while( ! glfwWindowShouldClose(mp_Window) )
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
	*/
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

void GraphicsManager::draw( void )
{
	render();
	glfwSwapBuffers(mp_Window);
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

// object creation functions ======================================================
string GraphicsManager::createLine(string name, vec3 start, vec3 end)
{
	return createLine(name, start, end, vec4(0.4f, 0.4f, 0.4f, 1.0f));
}

string GraphicsManager::createLine(string name, vec3 start, vec3 end, vec4 color)
{
	Entity* mp_Entity;
	Mesh* pMesh = mp_ResourceManager->addMesh(name + "-mesh");
	Model* pModel = mp_ResourceManager->addModel(name + "-model");

	ArrayList<vec3> verts;
	verts.add(start);
	verts.add(end);

	ArrayList<vec3> norms;
	for (int i = 0; i < 2; ++i)
		norms.add(vec3(0.0f, 1.0f, 0.0f));

	pMesh->begin(GL_LINES, 2);
	pMesh->copyVertexData(verts);
	pMesh->copyNormalData(norms);
	pMesh->end();

	pModel->addMesh(pMesh);

	mp_Entity = New Entity(vec3(0.0f), vec3(0.0f), vec3(1.0f), color);
	mp_Entity->addModel(pModel);
	mp_SceneManager->getCurrentScene()->addEntity(name + "-entity", mp_Entity);

	return name + "-entity";
}

void GraphicsManager::setLineThickness(float width)
{
	glLineWidth(width);
}


string GraphicsManager::createPlane(string name)
{
	return createPlane(name, vec2(1.0f));
}

string GraphicsManager::createPlane(string name, vec2 dimensions)
{
	return createPlane(name, dimensions, vec3(0.0f));
}

string GraphicsManager::createPlane(string name, vec2 dimensions, vec3 position)
{
	return createPlane(name, dimensions, position, vec4(0.4f));
}

string GraphicsManager::createPlane(string name, vec2 dimensions, vec3 position, vec4 color)
{
	Entity* mp_Entity;
	Mesh* pMesh = mp_ResourceManager->addMesh(name + "-mesh");
	Model* pModel = mp_ResourceManager->addModel(name + "-model");
	
	float x = dimensions.x / 2.0f;
	float z = dimensions.y / 2.0f;

	ArrayList<vec3> verts;
	verts.add(vec3(-x, 0.0f, -z));
	verts.add(vec3(-x, 0.0f, z));
	verts.add(vec3(x, 0.0f, z));
	verts.add(vec3(x, 0.0f, -z));

	ArrayList<vec3> norms;
	for (int i = 0; i < 4; ++i)
		norms.add(vec3(0.0f, 1.0f, 0.0f));

	pMesh->begin(GL_QUADS, 4);
	pMesh->copyVertexData(verts);
	pMesh->copyNormalData(norms);
	pMesh->end();

	pModel->addMesh(pMesh);

	mp_Entity = New Entity(position, vec3(0.0f), vec3(1.0f), color);
	mp_Entity->addModel(pModel);
	mp_SceneManager->getCurrentScene()->addEntity(name + "-entity", mp_Entity);

	return name + "-entity";
}


string GraphicsManager::createCube(string name)
{
	return createCube(name, vec3(0.0f, 0.5f, 0.0f));
}

string GraphicsManager::createCube(string name, vec3 position)
{
	return createCube(name, position, vec3(1.0f));
}

string GraphicsManager::createCube(string name, vec3 position, vec3 dimensions)
{
	return createCube(name, position, dimensions, vec4(vec3(0.4f), 1.f));
}

string GraphicsManager::createCube(string name, vec3 position, vec3 dimensions, vec4 color)
{
	Entity* mp_Entity;
	Model* pModel = mp_ResourceManager->getModel("mdl_cube");

	mp_Entity = New Entity(position, vec3(0.0f), dimensions, color);
	mp_Entity->addModel(pModel);
	mp_SceneManager->getCurrentScene()->addEntity(name + "-entity", mp_Entity);

	return name + "-entity";
}

// object manipulation functions ===========================================================
void GraphicsManager::updateEntityPosition(string name, vec3 pos)
{
	// get entity from list
	Entity* mp_thing = mp_SceneManager->getCurrentScene()->getEntity(name);

	if (mp_thing != nullptr)
	{
		// set new position
		mp_thing->setPos(pos);
	}
}

void GraphicsManager::updateEntityRotation(string name, vec3 rot)
{
	// get entity from list
	Entity* mp_thing = mp_SceneManager->getCurrentScene()->getEntity(name);

	if (mp_thing != nullptr)
	{
		// set new position
		mp_thing->setRot(rot);
	}
}

void GraphicsManager::updateEntityScale(string name, vec3 scale)
{
	// get entity from list
	Entity* mp_thing = mp_SceneManager->getCurrentScene()->getEntity(name);

	if (mp_thing != nullptr)
	{
		// set new position
		mp_thing->setScale(scale);
	}
}