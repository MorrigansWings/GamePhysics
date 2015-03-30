#include <Arc/ManagedObject.h>
#include <GraphicsManager.h>
#include <PhysicsManager.h>

class KatamariGame
{
public:
	KatamariGame(){};
	~KatamariGame(){};
	inline void setGroundPlane(string name) { groundPlane = name; }

private:
	int	mWorldX, // size of the world ground plane
		mWorldY;

	string groundPlane;

};