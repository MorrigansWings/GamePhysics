#ifndef GRAPHICS_II_RESOURCE_LOADER_H
#define GRAPHICS_II_RESOURCE_LOADER_H

#include <Arc/ManagedObject.h>

using namespace Arc;

class ResourceLoader :
	public ManagedObject
{
public:

	virtual bool loadFromFile( const string& filename ) = 0;

};

#endif // GRAPHICS_II_RESOURCE_LOADER_H