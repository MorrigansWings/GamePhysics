#include <Arc/ManagedObject.h>
#include <GraphicsManager.h>
#include <PhysicsManager.h>

class KatamariGame
{
public:
	KatamariGame(int argc, char* argv[]);
	~KatamariGame();

	void setup(int framerate, float groundx, float groundZ);

	void start();
	void update(float deltaTime);
	void fixedUpdate(float deltaTime);

	inline GLFWwindow* getGLFWwindow() { return GraphicsManager::GetInstance()->getGLFWWindow(); }

private:
	PhysicsManager* mp_PhysicsManager;

	string	m_groundPlane,
			m_testCube;

	double	m_LastFrameTime;

	float	m_WorldX, // size of the world ground plane
			m_WorldZ;
	
	int		m_framerate;


};