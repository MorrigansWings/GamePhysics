#include "OpenGL.h"
#include "GraphicsManager.h"
#include "KatamariGame/KatamariGame.h"
#include "Log.h"

#include <Arc/ArcCore.h>
#include <Arc/MemoryTracker.h>

#include <SDL/SDL.h>
#undef main

void glfwError( int error, const char* description )
{
	Log::ErrorFmt("GLFW", "%s (code %d)", description, error);
}

void glfwResize( GLFWwindow* window, int width, int height )
{
	GraphicsManager::GetInstance()->hookResize(width, height);
}

void glfwKey( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	switch (action)
	{
	case GLFW_PRESS:

		GraphicsManager::GetInstance()->hookKeyDown(key);

		break;
	case GLFW_RELEASE:

		GraphicsManager::GetInstance()->hookKeyUp(key);

		break;
	case GLFW_REPEAT:

		GraphicsManager::GetInstance()->hookKeyHeld(key);

		break;
	}
}

void glfwMouseMove( GLFWwindow* window, double x, double y )
{
	GraphicsManager::GetInstance()->hookMouseMoved((float)x, (float)y);
}

void glfwMouse( GLFWwindow* window, int button, int action, int mods )
{
	switch (action)
	{
	case GLFW_PRESS:
		
		GraphicsManager::GetInstance()->hookMouseDown(button);

		break;
	case GLFW_RELEASE:

		GraphicsManager::GetInstance()->hookMouseUp(button);

		break;
	}
}

void glfwMouseScroll( GLFWwindow* window, double x, double y )
{
	GraphicsManager::GetInstance()->hookMouseScrolled((float)x, (float)y);
}

int main( int argc, char* argv[] )
{
	Log::AddInfoOutput("stdout");
	Log::AddErrorOutput("stderr");
	
	Log::AddInfoOutput("info.log", false);
	Log::AddErrorOutput("error.log", false);

	Log::Info("Main", "Starting Up");

	if ( ! Arc_InitCore() )
	{
		Log::Error("Main", "Failed to initialize Arc");
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	Log::InfoFmt("Main", "Running Arc version %s", Arc_GetVersionString().c_str());

	Arc_InitMemoryTracker();

	glfwSetErrorCallback(glfwError);

	//New GraphicsManager(argc, argv);
	//GLFWwindow* pWindow = GraphicsManager::GetInstance()->getGLFWWindow();

	KatamariGame* pGame = new KatamariGame(argc, argv);
	pGame->setup(60, 10.0f, 10.0f);

	GLFWwindow* pWindow = pGame->getGLFWwindow();

	if (pWindow != nullptr)
	{
		glfwSetFramebufferSizeCallback(pWindow, glfwResize);
		glfwSetKeyCallback(pWindow, glfwKey);
		glfwSetMouseButtonCallback(pWindow, glfwMouse);
		glfwSetCursorPosCallback(pWindow, glfwMouseMove);
		glfwSetScrollCallback(pWindow, glfwMouseScroll);

		//GraphicsManager::GetInstance()->start();
		pGame->start();
	}

	delete pGame;

	if (Arc_GetMemoryAllocationCount() > 0)
	{
		Arc_PrintMemoryAllocations();
		system("PAUSE");
	}

	Arc_CleanupMemoryTracker();

	Log::CloseOutputs();

	return EXIT_SUCCESS;
}