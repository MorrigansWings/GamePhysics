#ifndef GRAPHICS_II_GRID_H
#define GRAPHICS_II_GRID_H

#include "Entity.h"

struct RenderData;

class Grid :
	public Entity
{
public:

	Grid( void );
	virtual ~Grid( void );

	virtual void preRender( const RenderData* pData );

private:

};

#endif // GRAPHICS_II_GRID_H