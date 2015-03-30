#ifndef GRAPHICS_II_RESOURCE_LOADER_OBJ_H
#define GRAPHICS_II_RESOURCE_LOADER_OBJ_H

#include "ResourceLoader.h"

class ResourceLoaderOBJ :
	public ResourceLoader
{
public:

	inline ResourceLoaderOBJ( void ) { }
	virtual inline ~ResourceLoaderOBJ( void ) { }

	virtual inline string getClassName( void ) const { return "Resource Loader OBJ"; }

	virtual bool loadFromFile( const string& filename );

protected:

	bool loadMTLFile( const string& filename );

};

#endif // GRAPHICS_II_RESOURCE_LOADER_OBJ_H