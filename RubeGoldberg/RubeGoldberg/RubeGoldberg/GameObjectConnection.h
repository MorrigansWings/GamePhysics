/*#ifndef _GAME_OBJECT_CONNECTION_
#define _GAME_OBJECT_CONNECTION_

#include "GameObject.h"

enum ConnectionType
{
	ROD = 0,
	CABLE,
	SPRING
};

class GameObjectConnection
	:GameObject
{
public:
	GameObjectConnection(){}
	~GameObjectConnection(){}

	void init(string first, string second, ConnectionType type);

	string mp_first;
	string mp_second;
	ConnectionType m_type;
};


#endif //_GAME_OBJECT_CONNECTION_
*/