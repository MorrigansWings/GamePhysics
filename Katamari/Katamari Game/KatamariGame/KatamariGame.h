#ifndef _KATAMARI_GAME_
#define _KATAMARI_GAME_

#include "../GraphicsEngine/GraphicsManager.h"
#include "../PhysicsEngine/PhysicsManager.h"
#include "../PhysicsEngine/Vectors.h"
#include "GameObject.h"
#include "Object.h"

class KatamariGame
{
public:
	KatamariGame(int argc, char* argv[]);
	~KatamariGame();

	void setup(int framerate, float groundHeight, float groundx, float groundZ);

	void start();
	void update(float deltaTime);
	void fixedUpdate(float deltaTime);

	inline GLFWwindow* getGLFWwindow() { return GraphicsManager::GetInstance()->getGLFWWindow(); }

private:
	GraphicsManager* mp_GraphicsManager;
	PhysicsManager* mp_PhysicsManager;

	Map<string, Object*> m_gameObjects;

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
