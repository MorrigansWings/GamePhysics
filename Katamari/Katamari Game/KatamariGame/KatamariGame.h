#include <Arc/ManagedObject.h>

class KatamariGame
{
public:
	KatamariGame(){};
	~KatamariGame(){};
	void initialize(int x, int y);

private:
	int	mWorldX, // size of the world ground plane
		mWorldY;

	string groundPlane;

};