#include "KatamariGame.h"

using namespace Physics;

KatamariGame::KatamariGame(int argc, char* argv[])
{
	New GraphicsManager(argc, argv);
	mp_GraphicsManager = GraphicsManager::GetInstance();
	GLFWwindow* pWindow = mp_GraphicsManager->getGLFWWindow();

	mp_PhysicsManager = new PhysicsManager();

	//GameObject::setGraphicsManager(mp_GraphicsManager);
	//GameObject::setPhysicsManager(mp_PhysicsManager);
}

KatamariGame::~KatamariGame()
{
	delete mp_GraphicsManager;
	delete mp_PhysicsManager;
}

void KatamariGame::setup(int framerate, float groundX, float groundZ)
{
	m_framerate = framerate;
	m_WorldX = groundX;
	m_WorldZ = groundZ;

	// Set up ground plane
	m_groundPlane = mp_GraphicsManager->createPlane("ground_plane",
									Physics::Vector2(m_WorldX, m_WorldZ).convertToGLM(),
									Physics::Vector3(0).convertToGLM(),
									Physics::Vector4(0.1f, 0.5f, 0.1f, 1.0f).convertToGLM());

	// Set line width and display test lines
	mp_GraphicsManager->setLineThickness(5.0f);
/*	GraphicsManager::GetInstance()->createLine("testOne", vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	GraphicsManager::GetInstance()->createLine("testTwo", vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	GraphicsManager::GetInstance()->createLine("testThree", vec3(0.0f), vec3(-1.0f, 1.0f, 1.0f));
	GraphicsManager::GetInstance()->createLine("testFour", vec3(0.0f), vec3(1.0f, 1.0f, -1.0f));
	GraphicsManager::GetInstance()->createLine("testFive", vec3(0.0f), vec3(-1.0f, 1.0f, -1.0f));
	*/

	// Cube test
	m_testPosition = Physics::Vector3(0.0f, 10.0f, 0.0f);
	m_testCube = GraphicsManager::GetInstance()->createCube("testOne", m_testPosition.convertToGLM());

	// Particle test
	m_testParticle = mp_PhysicsManager->createParticle("testParticle", m_testPosition);
	std::cout << "KATAMARIGAME::setup(): Got back " << m_testParticle << " from createParticle function in PhysicsManager!" << std::endl;

	// GameObject test
	m_testObject = new GameObject();
	m_testObject->setGraphicsManager(mp_GraphicsManager);
	m_testObject->setPhysicsManager(mp_PhysicsManager);
	m_testObject->init(m_testParticle, m_testCube);
	mp_PhysicsManager->applyGravity(m_testParticle);
	m_gameObjects.add("TestObject", m_testObject);
	//m_testObject->applyGravity();
}

void KatamariGame::start()
{
	while (!mp_GraphicsManager->shouldWindowClose())
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

		mp_GraphicsManager->pollEvents();
	}
}

void KatamariGame::update(float deltaTime)
{
	//std::cout << "Calling update! deltaTime = " << deltaTime << std::endl;
	mp_GraphicsManager->draw();
}

void KatamariGame::fixedUpdate(float fixedDeltaTime)
{
	//std::cout << "Calling fixedUpdate! fixedDeltaTime = " << fixedDeltaTime << std::endl;
//	m_testPosition += Vector3(0.0f, 0.1f, 0.0f);
//	GraphicsManager::GetInstance()->updateEntityPosition(m_testCube, m_testPosition.convertToGLM());
	mp_PhysicsManager->update(fixedDeltaTime);
	//m_testObject->update();

	// Update objects in map
	for (auto iter = m_gameObjects.itBegin(); iter != m_gameObjects.itEnd(); ++iter)
		iter->second->update();

}
