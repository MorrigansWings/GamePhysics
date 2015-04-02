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

void KatamariGame::setup(int framerate, float groundHeight, float groundX, float groundZ)
{
	m_framerate = framerate;
	m_WorldX = groundX;
	m_WorldZ = groundZ;

	// Set up ground plane
	mp_PhysicsManager->setupGround(0.0f, m_WorldX / 2.0f, m_WorldZ / 2.0f);
	m_groundPlane = mp_GraphicsManager->createPlane("ground_plane",
									Physics::Vector2(m_WorldX, m_WorldZ).convertToGLM(),
									Physics::Vector3(0.0f, groundHeight, 0.0f).convertToGLM(),
									Physics::Vector4(0.1f, 0.5f, 0.1f, 1.0f).convertToGLM());

	// Set line width and display test lines
	mp_GraphicsManager->setLineThickness(5.0f);
/*	GraphicsManager::GetInstance()->createLine("testOne", vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
	GraphicsManager::GetInstance()->createLine("testTwo", vec3(0.0f), vec3(1.0f, 1.0f, 1.0f));
	GraphicsManager::GetInstance()->createLine("testThree", vec3(0.0f), vec3(-1.0f, 1.0f, 1.0f));
	GraphicsManager::GetInstance()->createLine("testFour", vec3(0.0f), vec3(1.0f, 1.0f, -1.0f));
	GraphicsManager::GetInstance()->createLine("testFive", vec3(0.0f), vec3(-1.0f, 1.0f, -1.0f));
	*/

	// Graphics test - cube
	string m_testCube = GraphicsManager::GetInstance()->createCube("cubeTest", 
											Physics::Vector3(10.0f, 0.5f, 10.0f).convertToGLM(),
											Physics::Vector3(0.2f, 0.2f, 0.2f).convertToGLM());
	
	// Physics test - gravity
	GameObject* m_testGravity = new GameObject();
	string m_gravityParticle = mp_PhysicsManager->createParticle("gravityParticle", 
											Physics::Vector3(-4.0f, 3.0f, 0.0f));
	string m_gravityEntity = mp_GraphicsManager->createCube("gravityCube", 
											Physics::Vector3(-4.0f, 3.0f, 0.0f).convertToGLM(),
											Physics::Vector3(0.2f, 0.2f, 0.2f).convertToGLM(),
											Physics::Vector4(0.0f, 0.7f, 0.0f, 1.0f).convertToGLM());
	m_testGravity->setGraphicsManager(mp_GraphicsManager);
	m_testGravity->setPhysicsManager(mp_PhysicsManager);
	m_testGravity->init(m_gravityParticle, m_gravityEntity);
	m_testGravity->applyGravity();
	m_gameObjects.add("TestObject", m_testGravity);

	// Physics Test - Cable
	GameObject* m_testCableOne = new GameObject();
	string m_cableParticleOne = mp_PhysicsManager->createParticle("cableParticleOne",
											Physics::Vector3(0.0f, 3.0f, 0.0f));
	string m_cableEntityOne = mp_GraphicsManager->createCube("cableCubeOne",
											Physics::Vector3(0.0f, 3.0f, 0.0f).convertToGLM(),
											Physics::Vector3(0.2f, 0.2f, 0.2f).convertToGLM(),
											Physics::Vector4(0.0f, 0.7f, 0.0f, 1.0f).convertToGLM());
	m_testCableOne->setGraphicsManager(mp_GraphicsManager);
	m_testCableOne->setPhysicsManager(mp_PhysicsManager);
	m_testCableOne->init(m_cableParticleOne, m_cableEntityOne);
	m_testCableOne->applyGravity();
	m_gameObjects.add("TestObject", m_testCableOne);


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
