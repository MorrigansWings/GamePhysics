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
/*	string m_testCube = GraphicsManager::GetInstance()->createCube("cubeTest", 
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
	m_gameObjects.add("AggCableTest", aggCable);*/

	// TEST AGG_CUBE
	createAggCube("TEST_AGG_CUBE", Physics::Vector3(3.0f, 3.0f, 3.0f));

	// TEST AGG_TETRAHEDRON
	createAggTetrahedron("TEST_AGG_TETRA", Physics::Vector3(-3.0f, 3.0f, 3.0f));

	// TEST AGG_DIAMOND
	createAggDiamond("TEST_AGG_DIAMOND", Physics::Vector3(0.0f, 3.0f, 3.0f));

	// Draw connections
	//for (auto iter = m_aggregateObjects.itBegin(); iter != m_aggregateObjects.itEnd(); ++iter)
	//{
	//	std::cout << "KATAMARIGAME::update: Attempting to call drawLines in " << iter->first << std::endl;
	//	//iter->second->drawLines();
	//}


	// Clear lines
	//for (auto iter = m_aggregateObjects.itBegin(); iter != m_aggregateObjects.itEnd(); ++iter)
	//	iter->second->clearLines();

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
	mp_PhysicsManager->update(fixedDeltaTime);

	// Update objects in map
	for (auto iter = m_gameObjects.itBegin(); iter != m_gameObjects.itEnd(); ++iter)
		iter->second->update();

	// Update aggregate objects
	for (auto iter = m_aggregateObjects.itBegin(); iter != m_aggregateObjects.itEnd(); ++iter)
		iter->second->update();
}


// TETRAHEDRON CONSTRUCTION =======================================
string KatamariGame::createAggTetrahedron(string name)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggTetrahedron(name, Physics::Vector3(0.0f, 0.0f, 0.0f));
}

string KatamariGame::createAggTetrahedron(string name, Physics::Vector3 position)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggTetrahedron(name, position, Physics::Vector3(2.0f, 1.0f, 2.0f));
}
																				
string KatamariGame::createAggTetrahedron(string name, Physics::Vector3 position, Physics::Vector3 dimensions)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggTetrahedron(name, position, dimensions, Physics::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
}

string KatamariGame::createAggTetrahedron(string name, Physics::Vector3 position, Physics::Vector3 dimensions, Physics::Vector4 color)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	// Create position variables
	float x = dimensions.x / 2.0f;
	float y = dimensions.y / 2.0f;
	float z = dimensions.z / 2.0f;
	ArrayList<Physics::Vector3> positions;
	// Top
	positions.add(Physics::Vector3(0.0f + position.x,  y + position.y,  0.0f + position.z));
	// Bottom
	positions.add(Physics::Vector3(  -x + position.x, -y + position.y,    -z + position.z));
	positions.add(Physics::Vector3(   x + position.x, -y + position.y,    -z + position.z));
	positions.add(Physics::Vector3(0.0f + position.x, -y + position.y,     z + position.z));

	//std::cout << "KATAMARIGAME:createAggCube: Positions:" << std::endl;
	for (int i = 0; i < 4; ++i)
		std::cout << "\t" << positions[i].ToString() << std::endl;

	// create physics particles
	ArrayList<string> particles;
	for (int i = 0; i < 4; ++i)
		particles.add(mp_PhysicsManager->createParticle(name + "_agg_part_" + std::to_string(i), positions[i]));

	// create graphics cubes
	ArrayList<string> entities;
	for (int i = 0; i < 4; ++i)
		entities.add(mp_GraphicsManager->createCube(name + "_agg_part_" + std::to_string(i), positions[i].GLM(), Physics::Vector3(0.2f, 0.2f, 0.2f).GLM(), color.GLM()));

	// Create Game Objects
	ArrayList<GameObject*> objects;
	for (int i = 0; i < 4; ++i)
	{
		GameObject* obj = new GameObject();
		obj->setGraphicsManager(mp_GraphicsManager);
		obj->setPhysicsManager(mp_PhysicsManager);
		obj->setParticleName(particles[i]);
		obj->setEntityName(entities[i]);
		obj->setName(name + "_object_" + std::to_string(i));
		obj->setPosition(positions[i]);
		obj->applyGravity();
		objects.add(obj);
	}

	// Create Aggregate Object!
	AggregateGameObject* aggObj = new AggregateGameObject();
	aggObj->setGraphicsManager(mp_GraphicsManager);
	aggObj->setPhysicsManager(mp_PhysicsManager);
	aggObj->setName(name);

	// load game object pointers into aggregateobject
	for (int i = 0; i < 4; ++i)
		aggObj->addGameObject(objects[i]->getName(), objects[i]);

	// Create connections!
	// Bottom
	aggObj->createConnection(objects[1], objects[2], ROD);
	aggObj->createConnection(objects[2], objects[3], ROD);
	aggObj->createConnection(objects[3], objects[1], ROD);

	// Vertical
	aggObj->createConnection(objects[0], objects[1], ROD);
	aggObj->createConnection(objects[0], objects[2], ROD);
	aggObj->createConnection(objects[0], objects[3], ROD);

	m_aggregateObjects.add(name, aggObj);
	return name;
}

// CUBE CONSTRUCTION =======================================
string KatamariGame::createAggCube(string name)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggCube(name, Physics::Vector3(0.0f, 0.0f, 0.0f));
}

string KatamariGame::createAggCube(string name, Physics::Vector3 position)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggCube(name, position, Physics::Vector3(2.0f, 2.0f, 2.0f));
}

string KatamariGame::createAggCube(string name, Physics::Vector3 position, Physics::Vector3 dimensions)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggCube(name, position, dimensions, Physics::Vector4(0.0f, 1.0f, 0.0f, 1.0f));
}

string KatamariGame::createAggCube(string name, Physics::Vector3 position, Physics::Vector3 dimensions, Physics::Vector4 color)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	// Create position variables
	float x = dimensions.x / 2.0f;
	float y = dimensions.y / 2.0f;
	float z = dimensions.z / 2.0f;
	//std::cout << "KATAMARIGAME::createAggCube: Adjusted dimension variables: { " << x << ", " << y << ", " << z << "}" << std::endl;
	// Top 4
	ArrayList<Physics::Vector3> positions;
	positions.add(Physics::Vector3(-x + position.x, y + position.y, -z + position.z));;
	positions.add(Physics::Vector3( x + position.x, y + position.y, -z + position.z));
	positions.add(Physics::Vector3( x + position.x, y + position.y,  z + position.z));
	positions.add(Physics::Vector3(-x + position.x, y + position.y,  z + position.z));
	
	// Bottom 4			
	positions.add(Physics::Vector3(-x + position.x, -y + position.y, -z + position.z));
	positions.add(Physics::Vector3( x + position.x, -y + position.y, -z + position.z));
	positions.add(Physics::Vector3( x + position.x, -y + position.y,  z + position.z));
	positions.add(Physics::Vector3(-x + position.x, -y + position.y,  z + position.z));
	
	//std::cout << "KATAMARIGAME:createAggCube: Positions:" << std::endl;
	for (int i = 0; i < 8; ++i)
		std::cout << "\t" << positions[i].ToString() << std::endl;

	// create physics particles
	ArrayList<string> particles;
	for (int i = 0; i < 8; ++i)
		particles.add(mp_PhysicsManager->createParticle(name + "_agg_part_" + std::to_string(i), positions[i]));

	// create graphics cubes
	ArrayList<string> entities;
	for (int i = 0; i < 8; ++i)
		entities.add(mp_GraphicsManager->createCube(name + "_agg_part_" + std::to_string(i), positions[i].GLM(), Physics::Vector3(0.2f, 0.2f, 0.2f).GLM(), color.GLM()));

	// Create Game Objects
	ArrayList<GameObject*> objects;
	for (int i = 0; i < 8; ++i)
	{
		GameObject* obj = new GameObject();
		obj->setGraphicsManager(mp_GraphicsManager);
		obj->setPhysicsManager(mp_PhysicsManager);
		obj->setParticleName(particles[i]);
		obj->setEntityName(entities[i]);
		obj->setName(name + "_object_" + std::to_string(i));
		obj->setPosition(positions[i]);
		obj->applyGravity();
		objects.add(obj);
	}

	// Create Aggregate Object!
	AggregateGameObject* aggObj = new AggregateGameObject();
	aggObj->setGraphicsManager(mp_GraphicsManager);
	aggObj->setPhysicsManager(mp_PhysicsManager);
	aggObj->setName(name);

	// load game object pointers into aggregateobject
	for (int i = 0; i < 8; ++i)
		aggObj->addGameObject(objects[i]->getName(), objects[i]);

	// Create connections!
	// Top
	aggObj->createConnection(objects[0], objects[1], ROD);
	aggObj->createConnection(objects[1], objects[2], ROD);
	aggObj->createConnection(objects[2], objects[3], ROD);
	aggObj->createConnection(objects[3], objects[0], ROD);
	
	// Bottom
	aggObj->createConnection(objects[4], objects[5], ROD);
	aggObj->createConnection(objects[5], objects[6], ROD);
	aggObj->createConnection(objects[6], objects[7], ROD);
	aggObj->createConnection(objects[7], objects[4], ROD);

	// Vertical
	aggObj->createConnection(objects[0], objects[4], ROD);
	aggObj->createConnection(objects[1], objects[5], ROD);
	aggObj->createConnection(objects[2], objects[6], ROD);
	aggObj->createConnection(objects[3], objects[7], ROD);

	// Cross
	aggObj->createConnection(objects[0], objects[6], CABLE);
	aggObj->createConnection(objects[1], objects[7], CABLE);
	aggObj->createConnection(objects[3], objects[5], CABLE);
	aggObj->createConnection(objects[2], objects[4], CABLE);
	
	m_aggregateObjects.add(name, aggObj);
	return name;
}

// DIAMOND CONSTRUCTION =========================================
string KatamariGame::createAggDiamond(string name)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggDiamond(name, Physics::Vector3(0.0f, 0.0f, 0.0f));
}

string KatamariGame::createAggDiamond(string name, Physics::Vector3 position)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggDiamond(name, position, Physics::Vector3(2.0f, 2.0f, 2.0f));
}

string KatamariGame::createAggDiamond(string name, Physics::Vector3 position, Physics::Vector3 dimensions)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggDiamond(name, position, dimensions, Physics::Vector4(0.0f, 0.0f, 1.0f, 1.0f));
}

string KatamariGame::createAggDiamond(string name, Physics::Vector3 position, Physics::Vector3 dimensions, Physics::Vector4 color)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	// Create position variables
	float x = dimensions.x / 2.0f;
	float y = dimensions.y / 2.0f;
	float z = dimensions.z / 2.0f;
	//std::cout << "KATAMARIGAME::createAggCube: Adjusted dimension variables: { " << x << ", " << y << ", " << z << "}" << std::endl;
	// Top
	ArrayList<Physics::Vector3> positions;
	positions.add(Physics::Vector3(0.0f + position.x,  y + position.y, 0.0f + position.z));;

	// Bottom 4			
	positions.add(Physics::Vector3(-x + position.x, 0.0f + position.y, -z + position.z));
	positions.add(Physics::Vector3( x + position.x, 0.0f + position.y, -z + position.z));
	positions.add(Physics::Vector3( x + position.x, 0.0f + position.y,  z + position.z));
	positions.add(Physics::Vector3(-x + position.x, 0.0f + position.y,  z + position.z));

	// Bottom
	positions.add(Physics::Vector3(0.0f + position.x, -y + position.y, 0.0f + position.z));

	//std::cout << "KATAMARIGAME:createAggCube: Positions:" << std::endl;
	for (int i = 0; i < 6; ++i)
		std::cout << "\t" << positions[i].ToString() << std::endl;

	// create physics particles
	ArrayList<string> particles;
	for (int i = 0; i < 6; ++i)
		particles.add(mp_PhysicsManager->createParticle(name + "_agg_part_" + std::to_string(i), positions[i]));

	// create graphics cubes
	ArrayList<string> entities;
	for (int i = 0; i < 6; ++i)
		entities.add(mp_GraphicsManager->createCube(name + "_agg_part_" + std::to_string(i), positions[i].GLM(), Physics::Vector3(0.2f, 0.2f, 0.2f).GLM(), color.GLM()));

	// Create Game Objects
	ArrayList<GameObject*> objects;
	for (int i = 0; i < 6; ++i)
	{
		GameObject* obj = new GameObject();
		obj->setGraphicsManager(mp_GraphicsManager);
		obj->setPhysicsManager(mp_PhysicsManager);
		obj->setParticleName(particles[i]);
		obj->setEntityName(entities[i]);
		obj->setName(name + "_object_" + std::to_string(i));
		obj->setPosition(positions[i]);
		obj->applyGravity();
		objects.add(obj);
	}

	// Create Aggregate Object!
	AggregateGameObject* aggObj = new AggregateGameObject();
	aggObj->setGraphicsManager(mp_GraphicsManager);
	aggObj->setPhysicsManager(mp_PhysicsManager);
	aggObj->setName(name);

	// load game object pointers into aggregateobject
	for (int i = 0; i < 6; ++i)
		aggObj->addGameObject(objects[i]->getName(), objects[i]);

	// Create connections!
	// Top
	aggObj->createConnection(objects[0], objects[1], CABLE);
	aggObj->createConnection(objects[0], objects[2], CABLE);
	aggObj->createConnection(objects[0], objects[3], CABLE);
	aggObj->createConnection(objects[0], objects[4], CABLE);

	// Middle
	aggObj->createConnection(objects[1], objects[2], ROD);
	aggObj->createConnection(objects[2], objects[3], ROD);
	aggObj->createConnection(objects[3], objects[4], ROD);
	aggObj->createConnection(objects[4], objects[1], ROD);

	// Bottom
	aggObj->createConnection(objects[5], objects[1], CABLE);
	aggObj->createConnection(objects[5], objects[2], CABLE);
	aggObj->createConnection(objects[5], objects[3], CABLE);
	aggObj->createConnection(objects[5], objects[4], CABLE);

	// Cross
	aggObj->createConnection(objects[0], objects[5], ROD);
	aggObj->createConnection(objects[1], objects[3], CABLE);
	aggObj->createConnection(objects[2], objects[4], CABLE);

	m_aggregateObjects.add(name, aggObj);
	return name;
}

