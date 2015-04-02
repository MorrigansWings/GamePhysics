#include "KatamariGame.h"

using namespace Physics;

KatamariGame::KatamariGame(int argc, char* argv[])
{
	New GraphicsManager(argc, argv);
	mp_GraphicsManager = GraphicsManager::GetInstance();
	GLFWwindow* pWindow = mp_GraphicsManager->getGLFWWindow();

	mp_PhysicsManager = new PhysicsManager();
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
									Physics::Vector2(m_WorldX, m_WorldZ).GLM(),
									Physics::Vector3(0.0f, groundHeight, 0.0f).GLM(),
									Physics::Vector4(0.1f, 0.5f, 0.1f, 1.0f).GLM());

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
											Physics::Vector3(10.0f, 0.5f, 10.0f).GLM(),
											Physics::Vector3(0.2f, 0.2f, 0.2f).GLM());
	
	// Physics test - gravity
	GameObject* m_testGravity = new GameObject();
	string m_gravityParticle = mp_PhysicsManager->createParticle("gravityParticle", 
											Physics::Vector3(-4.0f, 3.0f, 0.0f));
	string m_gravityEntity = mp_GraphicsManager->createCube("gravityCube", 
											Physics::Vector3(-4.0f, 3.0f, 0.0f).GLM(),
											Physics::Vector3(0.2f, 0.2f, 0.2f).GLM(),
											Physics::Vector4(0.0f, 0.7f, 0.0f, 1.0f).GLM());
	m_testGravity->setGraphicsManager(mp_GraphicsManager);
	m_testGravity->setPhysicsManager(mp_PhysicsManager);
	m_testGravity->init("gravityObject", m_gravityParticle, m_gravityEntity);
	m_testGravity->applyGravity();
	m_gameObjects.add(m_testGravity->getName(), m_testGravity);

	// Physics Test - Cable ==================================================================
	GameObject* m_testCableOne = new GameObject();
	string m_cableParticleOne = mp_PhysicsManager->createParticle("cableParticleOne",
											Physics::Vector3(-1.0f, 3.0f, 0.0f));
	string m_cableEntityOne = mp_GraphicsManager->createCube("cableCubeOne",
											Physics::Vector3(-1.0f, 3.0f, 0.0f).GLM(),
											Physics::Vector3(0.2f, 0.2f, 0.2f).GLM(),
											Physics::Vector4(0.0f, 0.7f, 0.7f, 1.0f).GLM());
	m_testCableOne->setGraphicsManager(mp_GraphicsManager);
	m_testCableOne->setPhysicsManager(mp_PhysicsManager);
	m_testCableOne->init("cableObjectOne", m_cableParticleOne, m_cableEntityOne);
	m_testCableOne->applyGravity();

	GameObject* m_testCableTwo = new GameObject();
	string m_cableParticleTwo = mp_PhysicsManager->createParticle("cableParticleTwo",
											Physics::Vector3(1.0f, 2.0f, 0.0f));
	string m_cableEntityTwo = mp_GraphicsManager->createCube("cableCubeTwo",
											Physics::Vector3(1.0f, 3.0f, 0.0f).GLM(),
											Physics::Vector3(0.2f, 0.2f, 0.2f).GLM(),
											Physics::Vector4(0.0f, 0.7f, 0.7f, 1.0f).GLM());
	m_testCableTwo->setGraphicsManager(mp_GraphicsManager);
	m_testCableTwo->setPhysicsManager(mp_PhysicsManager);
	m_testCableTwo->init("cableObjectTwo", m_cableParticleTwo, m_cableEntityTwo);
	m_testCableTwo->applyGravity();
	//m_gameObjects.add(m_testCableTwo->getName(), m_testCableTwo);

	AggregateGameObject* aggCable = new AggregateGameObject();
	aggCable->setGraphicsManager(mp_GraphicsManager);
	aggCable->setPhysicsManager(mp_PhysicsManager);
	aggCable->addGameObject("left", m_testCableOne);
	aggCable->addGameObject("right", m_testCableTwo);
	aggCable->createConnection(m_testCableOne, m_testCableTwo, ROD);
	m_gameObjects.add("AggCableTest", aggCable);


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

void KatamariGame::createAggCube(string &name)
{
	createAggCube(name, Physics::Vector3(1.0f, 1.0f, 1.0f));
}

void KatamariGame::createAggCube(string &name, Physics::Vector3 dimensions)
{
	createAggCube(name, dimensions, Physics::Vector3(0.0f, 3.0f, 0.0f));
}

void KatamariGame::createAggCube(string &name, Physics::Vector3 dimensions, Physics::Vector3 position)
{
	createAggCube(name, position, dimensions, Physics::Vector4(0.6f, 0.6f, 0.6f, 0.6f));
}

void KatamariGame::createAggCube(string &name, Physics::Vector3 dimensions, Physics::Vector3 position, Physics::Vector4 color)
{
	// Create position variables
	float x = dimensions.x / 2.0f;
	float y = dimensions.y / 2.0f;
	float z = dimensions.z / 2.0f;
	// Top 4
	ArrayList<Physics::Vector3> positions;
	positions[0] = Physics::Vector3(-x, y, -z);
	positions[1] = Physics::Vector3(x, y, -z);
	positions[2] = Physics::Vector3(-x, y, z);
	positions[3] = Physics::Vector3(x, y, z);
	// Bottom 4			
	positions[4] = Physics::Vector3(-x, -y, -z);
	positions[5] = Physics::Vector3(x, -y, -z);
	positions[6] = Physics::Vector3(-x, -y, z);
	positions[7] = Physics::Vector3(x, -y, z);

	// create physics particles
	ArrayList<string> particles;
	for (int i = 0; i < 8; ++i)
		particles[i] = mp_PhysicsManager->createParticle(name + "_agg_part_" + std::to_string(i), positions[i]);

	// create graphics cubes
	ArrayList<string> entities;
	for (int i = 0; i < 8; ++i)
		entities[i] = mp_GraphicsManager->createCube(name + "_agg_part_" + std::to_string(i), positions[i].GLM(), Physics::Vector3(0.2f, 0.2f, 0.2f).GLM(), color.GLM());

	// Create Game Objects
	ArrayList<GameObject*> objects;
	for (int i = 0; i < 8; ++i)
	{
		objects[i] = new GameObject();
//		objects[i]
	}

	GameObject* object_1 = new GameObject();
	GameObject* object_2 = new GameObject();
	GameObject* object_3 = new GameObject();
	GameObject* object_4 = new GameObject();
	GameObject* object_5 = new GameObject();
	GameObject* object_6 = new GameObject();
	GameObject* object_7 = new GameObject();
	GameObject* object_8 = new GameObject();




}
