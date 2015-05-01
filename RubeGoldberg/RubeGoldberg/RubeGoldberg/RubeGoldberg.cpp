#include "RubeGoldberg.h"

using namespace Physics;

RubeGoldberg::RubeGoldberg(int argc, char* argv[])
{
	New GraphicsManager(argc, argv);
	mp_GraphicsManager = GraphicsManager::GetInstance();
	GLFWwindow* pWindow = mp_GraphicsManager->getGLFWWindow();

	mp_PhysicsManager = new PhysicsManager();
}

RubeGoldberg::~RubeGoldberg()
{
	delete mp_GraphicsManager;
	delete mp_PhysicsManager;
}

void RubeGoldberg::setup(int framerate, float groundHeight, float groundX, float groundZ)
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

	// set up invisible bounding box!
	mp_PhysicsManager->setupBounds(Physics::Vector2(10.0f, 10.0f));

	// Set line width and display test lines
	mp_GraphicsManager->setLineThickness(5.0f);

	// TEST AGG_CUBE
	//createAggCube("TEST_AGG_CUBE", Physics::Vector3(3.0f, 3.0f, 3.0f));

	// TEST AGG_TETRAHEDRON
	//createAggTetrahedron("TEST_AGG_TETRA", Physics::Vector3(-3.0f, 3.0f, 3.0f));

	// TEST AGG_DIAMOND
	//createAggDiamond("TEST_AGG_DIAMOND", Physics::Vector3(0.0f, 3.0f, 3.0f));

	// TEST RIGID BODY - SPHERE
	//createRigidSphere("TEST_RIGIDBODY_SPHERE", Physics::Vector3(0.0f, 10.0f, 0.0f));

	// TEST RIGID BODY - SPHERE GRAVITY
	createRigidSphere("TEST_RIGIDBODY_SPHERE_GRAVITY", Physics::Vector3(0.0f, 5.0f, 0.0f));
	m_rigidBodyObjects["TEST_RIGIDBODY_SPHERE_GRAVITY"]->setColliderName(
				mp_PhysicsManager->addCollisionSphere(string("TEST_RIGIDBODY_SPHERE_GRAVITY_COLLIDER"), string("TEST_RIGIDBODY_SPHERE_GRAVITY")));

	//// TEST RIGID BODY - SPHERE ON SPHERE
	createRigidSphere("TEST_RIGIDBODY_SPHERE_ON_SPHERE", Physics::Vector3(0.0f, 15.0f, 0.0f));
	m_rigidBodyObjects["TEST_RIGIDBODY_SPHERE_ON_SPHERE"]->setColliderName(
		mp_PhysicsManager->addCollisionSphere(string("TEST_RIGIDBODY_SPHERE_ON_SPHERE_COLLIDER"), string("TEST_RIGIDBODY_SPHERE_ON_SPHERE")));

	// TEST RIGID BODY - BOX ON SPHERE
	createRigidBox("TEST_RIGIDBODY_BOX_ON_SPHERE", Physics::Vector3(0.75f, 20.0f, 0.0f));
	m_rigidBodyObjects["TEST_RIGIDBODY_BOX_ON_SPHERE"]->setColliderName(
		mp_PhysicsManager->addCollisionSphere(string("TEST_RIGIDBODY_BOX_ON_SPHERE_COLLIDER"), string("TEST_RIGIDBODY_BOX_ON_SPHERE")));
	
	// TEST RIGID BODY - BOX ON BOX
	createRigidBox("TEST_RIGIDBODY_BOX_ON_BOX", Physics::Vector3(-0.75f, 30.0f, 0.0f));
	m_rigidBodyObjects["TEST_RIGIDBODY_BOX_ON_BOX"]->setColliderName(
		mp_PhysicsManager->addCollisionSphere(string("TEST_RIGIDBODY_BOX_ON_BOX_COLLIDER"), string("TEST_RIGIDBODY_BOX_ON_BOX")));

	createRigidBox("TEST_RIGIDBODY_BOX_ON_BOX_2", Physics::Vector3(-0.75f, 30.0f, 0.0f));
	m_rigidBodyObjects["TEST_RIGIDBODY_BOX_ON_BOX_2"]->setColliderName(
		mp_PhysicsManager->addCollisionSphere(string("TEST_RIGIDBODY_BOX_ON_BOX_2_COLLIDER"), string("TEST_RIGIDBODY_BOX_ON_BOX_2")));

	createRigidBox("TEST_RIGIDBODY_BOX_ON_BOX_3", Physics::Vector3(0.0f, 30.0f, 0.75f));
	m_rigidBodyObjects["TEST_RIGIDBODY_BOX_ON_BOX"]->setColliderName(
		mp_PhysicsManager->addCollisionSphere(string("TEST_RIGIDBODY_BOX_ON_BOX_3_COLLIDER"), string("TEST_RIGIDBODY_BOX_ON_BOX_3")));

	createRigidBox("TEST_RIGIDBODY_BOX_ON_BOX", Physics::Vector3(-0.75f, 30.0f, -0.75f));
	m_rigidBodyObjects["TEST_RIGIDBODY_BOX_ON_BOX"]->setColliderName(
		mp_PhysicsManager->addCollisionSphere(string("TEST_RIGIDBODY_BOX_ON_BOX_3_COLLIDER"), string("TEST_RIGIDBODY_BOX_ON_BOX_3")));


	// apply gravity to all rigid bodies
	for (auto iter = m_rigidBodyObjects.itBegin(); iter != m_rigidBodyObjects.itEnd(); ++iter)
	{
		iter->second->applyGravity();
	}
}

void RubeGoldberg::start()
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

void RubeGoldberg::update(float deltaTime)
{	
	//std::cout << "Calling update! deltaTime = " << deltaTime << std::endl;

	mp_GraphicsManager->draw();
}

void RubeGoldberg::fixedUpdate(float fixedDeltaTime)
{
	mp_PhysicsManager->update(fixedDeltaTime);

	// Update objects in map
	//for (auto iter = m_gameObjects.itBegin(); iter != m_gameObjects.itEnd(); ++iter)
	//	iter->second->update();

	// Update aggregate objects
	//for (auto iter = m_aggregateObjects.itBegin(); iter != m_aggregateObjects.itEnd(); ++iter)
	//	iter->second->update();

	// Update rigid body objects
	for (auto iter = m_rigidBodyObjects.itBegin(); iter != m_rigidBodyObjects.itEnd(); ++iter)
		iter->second->update();
}


// TETRAHEDRON CONSTRUCTION =======================================
string RubeGoldberg::createAggTetrahedron(string name)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggTetrahedron(name, Physics::Vector3(0.0f, 0.0f, 0.0f));
}

string RubeGoldberg::createAggTetrahedron(string name, Physics::Vector3 position)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggTetrahedron(name, position, Physics::Vector3(2.0f, 1.0f, 2.0f));
}
																				
string RubeGoldberg::createAggTetrahedron(string name, Physics::Vector3 position, Physics::Vector3 dimensions)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggTetrahedron(name, position, dimensions, Physics::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
}

string RubeGoldberg::createAggTetrahedron(string name, Physics::Vector3 position, Physics::Vector3 dimensions, Physics::Vector4 color)
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

	//std::cout << "RubeGoldberg:createAggCube: Positions:" << std::endl;
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
string RubeGoldberg::createAggCube(string name)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggCube(name, Physics::Vector3(0.0f, 0.0f, 0.0f));
}

string RubeGoldberg::createAggCube(string name, Physics::Vector3 position)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggCube(name, position, Physics::Vector3(2.0f, 2.0f, 2.0f));
}

string RubeGoldberg::createAggCube(string name, Physics::Vector3 position, Physics::Vector3 dimensions)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggCube(name, position, dimensions, Physics::Vector4(0.0f, 1.0f, 0.0f, 1.0f));
}

string RubeGoldberg::createAggCube(string name, Physics::Vector3 position, Physics::Vector3 dimensions, Physics::Vector4 color)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	// Create position variables
	float x = dimensions.x / 2.0f;
	float y = dimensions.y / 2.0f;
	float z = dimensions.z / 2.0f;
	//std::cout << "RubeGoldberg::createAggCube: Adjusted dimension variables: { " << x << ", " << y << ", " << z << "}" << std::endl;
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
	
	//std::cout << "RubeGoldberg:createAggCube: Positions:" << std::endl;
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
string RubeGoldberg::createAggDiamond(string name)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggDiamond(name, Physics::Vector3(0.0f, 0.0f, 0.0f));
}

string RubeGoldberg::createAggDiamond(string name, Physics::Vector3 position)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggDiamond(name, position, Physics::Vector3(2.0f, 2.0f, 2.0f));
}

string RubeGoldberg::createAggDiamond(string name, Physics::Vector3 position, Physics::Vector3 dimensions)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	return createAggDiamond(name, position, dimensions, Physics::Vector4(0.0f, 0.0f, 1.0f, 1.0f));
}

string RubeGoldberg::createAggDiamond(string name, Physics::Vector3 position, Physics::Vector3 dimensions, Physics::Vector4 color)
{
	if (m_aggregateObjects.containsKey(name))
		return "";
	// Create position variables
	float x = dimensions.x / 2.0f;
	float y = dimensions.y / 2.0f;
	float z = dimensions.z / 2.0f;
	//std::cout << "RubeGoldberg::createAggCube: Adjusted dimension variables: { " << x << ", " << y << ", " << z << "}" << std::endl;
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

	//std::cout << "RubeGoldberg:createAggCube: Positions:" << std::endl;
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

// RIGID BODY SPHERE CONSTRUCTION =====================================
string RubeGoldberg::createRigidSphere(string name)
{
	if (m_rigidBodyObjects.containsKey(name))
		return "";
	return createRigidSphere(name, Physics::Vector3(0.0f));
}

string RubeGoldberg::createRigidSphere(string name, Physics::Vector3 position)
{
	if (m_rigidBodyObjects.containsKey(name))
		return "";
	return createRigidSphere(name, position, 0.5f);
}

string RubeGoldberg::createRigidSphere(string name, Physics::Vector3 position, float radius)
{
	if (m_rigidBodyObjects.containsKey(name))
		return "";
	return createRigidSphere(name, position, radius, Physics::Vector4(0.5f, 0.5f, 0.5f, 1.0f));
}

string RubeGoldberg::createRigidSphere(string name, Physics::Vector3 position, float radius, Physics::Vector4 color)
{
	if (m_rigidBodyObjects.containsKey(name))
		return "";

	// create physics object
	string rigidbody = mp_PhysicsManager->createRigidBody(name, position);
	mp_PhysicsManager->setRigidBodyDimensions(rigidbody, radius);

	// create graphics object
	string entity = mp_GraphicsManager->createSphere(name, radius, position.GLM(), color.GLM());

	// create rigid body!
	RigidBodyObject* body = new RigidBodyObject();
	body->setGraphicsManager(mp_GraphicsManager);
	body->setPhysicsManager(mp_PhysicsManager);
	body->setName(name);
	body->setEntityName(entity);
	body->setRigidBodyName(rigidbody);
	m_rigidBodyObjects.add(name, body);

	return name;
}

// RIGID BODY BOX CONSTRUCTION =========================================
string RubeGoldberg::createRigidBox(string name)
{
	return createRigidBox(name, Physics::Vector3(0.0f));
}

string RubeGoldberg::createRigidBox(string name, Physics::Vector3 position)
{
	return createRigidBox(name, position, Physics::Vector3(1.0f));
}

string RubeGoldberg::createRigidBox(string name, Physics::Vector3 position, Physics::Vector3 dimensions)
{
	return createRigidBox(name, position, dimensions, Physics::Vector4(0.5f, 0.5f, 0.5f, 1.0f));
}

string RubeGoldberg::createRigidBox(string name, Physics::Vector3 position, Physics::Vector3 dimensions, Physics::Vector4 color)
{
	if (m_rigidBodyObjects.containsKey(name))
		return "";

	// create physics object
	string rigidbody = mp_PhysicsManager->createRigidBody(name, position);
	mp_PhysicsManager->setRigidBodyDimensions(rigidbody, dimensions * 0.5f);

	// create graphics object
	string entity = mp_GraphicsManager->createCube(name, position.GLM(), dimensions.GLM(), color.GLM());

	// create rigid body!
	RigidBodyObject* body = new RigidBodyObject();
	body->setGraphicsManager(mp_GraphicsManager);
	body->setPhysicsManager(mp_PhysicsManager);
	body->setName(name);
	body->setEntityName(entity);
	body->setRigidBodyName(rigidbody);
	m_rigidBodyObjects.add(name, body);

	return name;
}


