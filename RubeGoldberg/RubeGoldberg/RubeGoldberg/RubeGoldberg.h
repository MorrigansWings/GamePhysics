#ifndef _KATAMARI_GAME_
#define _KATAMARI_GAME_

#include "../GraphicsEngine/GraphicsManager.h"
#include "../PhysicsEngine/PhysicsManager.h"
#include "../PhysicsEngine/Vectors.h"
#include "Object.h"
#include "GameObject.h"
#include "AggregateGameObject.h"

class RubeGoldberg
{
public:
	RubeGoldberg(int argc, char* argv[]);
	~RubeGoldberg();

	void setup(int framerate, float groundHeight, float groundx, float groundZ);

	void start();
	void update(float deltaTime);
	void fixedUpdate(float deltaTime);

	void drawConnections();
	void clearConnections();

	string createAggTetrahedron(string name);
	string createAggTetrahedron(string name, Physics::Vector3 position);
	string createAggTetrahedron(string name, Physics::Vector3 position, Physics::Vector3 dimensions);
	string createAggTetrahedron(string name, Physics::Vector3 position, Physics::Vector3 dimensions, Physics::Vector4 color);

	string createAggCube(string name);
	string createAggCube(string name, Physics::Vector3 position);
	string createAggCube(string name, Physics::Vector3 position, Physics::Vector3 dimensions);
	string createAggCube(string name, Physics::Vector3 position, Physics::Vector3 dimensions, Physics::Vector4 color);

	string createAggDiamond(string name);
	string createAggDiamond(string name, Physics::Vector3 position);
	string createAggDiamond(string name, Physics::Vector3 position, Physics::Vector3 dimensions);
	string createAggDiamond(string name, Physics::Vector3 position, Physics::Vector3 dimensions, Physics::Vector4 color);


	inline GLFWwindow* getGLFWwindow() { return GraphicsManager::GetInstance()->getGLFWWindow(); }

private:
	GraphicsManager* mp_GraphicsManager;
	PhysicsManager* mp_PhysicsManager;

	Map<string, Object*> m_gameObjects;

	Map<string, AggregateGameObject*> m_aggregateObjects;

	//GameObject* m_testObject;

	//Physics::Vector3 m_testPosition;

	string	m_groundPlane;
//			m_testCube,
//			m_testParticle;

	double	m_LastFrameTime;

	float	m_WorldX, // size of the world ground plane
			m_WorldZ;
	
	int		m_framerate;


};

#endif //_KATAMARI_GAME_
