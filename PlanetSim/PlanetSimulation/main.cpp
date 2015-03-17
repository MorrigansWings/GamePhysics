#include "GraphicsEngine/GraphicsManager.h"
#include "Input/DirectInput.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	GraphicsManager gManager(hInstance, "Planet Simulation", D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING);
	gd3dApp = &gManager;

	DirectInput di(DISCL_NONEXCLUSIVE | DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	gDInput = &di;

/*	if (!gManager.createBox((std::string)"cube", 2.0f))
	{
		printf("GraphicsManager could not create CUBE. Exiting...\n");
		return -1;
	}*/

	if (!gManager.createSphere((std::string)"sphere", 1.0f))
	{
		printf("GraphicsManager could not create SPHERE. Exiting...\n");
		return -1;
	}

	return gd3dApp->run();
}