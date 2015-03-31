#include "KatamariGame.h"

KatamariGame::KatamariGame(int argc, char* argv[])
{
	New GraphicsManager(argc, argv);
	GLFWwindow* pWindow = GraphicsManager::GetInstance()->getGLFWWindow();

	mp_PhysicsManager = new PhysicsManager();
}

KatamariGame::~KatamariGame()
{
	delete GraphicsManager::GetInstance();
	delete mp_PhysicsManager;
}

void KatamariGame::setup(int framerate, float groundX, float groundZ)
{
	m_framerate = framerate;
	m_WorldX = groundX;
	m_WorldZ = groundZ;

	// Set up ground plane
	m_groundPlane = GraphicsManager::GetInstance()->createPlane("ground_plane", 
														vec2(m_WorldX, m_WorldZ), 
														vec3(0.0f), 
														vec4(0.1f, 0.5f, 0.1f, 1.0f));

	// Set line width and display test lines
	GraphicsManager::GetInstance()->setLineThickness(5.0f);
/*	GraphicsManager::GetInstance()->createLine("testOne", vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	GraphicsManager::GetInstance()->createLine("testTwo", vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	GraphicsManager::GetInstance()->createLine("testThree", vec3(0.0f), vec3(-1.0f, 1.0f, 1.0f));
	GraphicsManager::GetInstance()->createLine("testFour", vec3(0.0f), vec3(1.0f, 1.0f, -1.0f));
	GraphicsManager::GetInstance()->createLine("testFive", vec3(0.0f), vec3(-1.0f, 1.0f, -1.0f));
	*/

	// Cube test
	m_testCube = GraphicsManager::GetInstance()->createCube("testOne");

}

void KatamariGame::start()
{
	while ( ! GraphicsManager::GetInstance()->shouldWindowClose())
	{
		const float fixedDeltaTime = 1.0f / m_framerate;
		static float updateTimer = 0.0f;

		double currTime = glfwGetTime();
		float deltaTime = (float)(currTime - m_LastFrameTime);
		m_LastFrameTime = currTime;

		updateTimer += deltaTime;

		// Track time for fixed update
		if (updateTimer >= fixedDeltaTime)
		{
			updateTimer = 0.0f;

			fixedUpdate(fixedDeltaTime);
		}

		// call update for unfixed update
		update(deltaTime);

		GraphicsManager::GetInstance()->pollEvents();
	}
}

void KatamariGame::update(float deltaTime)
{
	GraphicsManager::GetInstance()->draw();
}

void KatamariGame::fixedUpdate(float fixedDeltaTime)
{

	mp_PhysicsManager->update(fixedDeltaTime);
}
