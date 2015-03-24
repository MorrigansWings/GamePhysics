#ifndef GRAPHICS_II_MODEL_H
#define GRAPHICS_II_MODEL_H

#include <Arc/ManagedObject.h>

#include <Arc/ArrayList.h>
#include <Arc/OBJDocument.h>
#include <Arc/PLYDocument.h>

#include "OpenGL.h"

#include "Mesh.h"
#include "Material.h"

using namespace Arc;

class ResourceManager;

class Model :
	public ManagedObject
{

	friend class ResourceManager;

public:

	inline Model( void )
		: m_Meshes(),
		  mp_Material(nullptr)
	{ }

	virtual ~Model( void );

	virtual inline string getClassName( void ) const { return "Model"; }

	void render( void );

	void addMesh( Mesh* pMesh );

	inline Material* getMaterial( void ) { return mp_Material; }
	void setMaterial( Material* pMat );

private:

	Model( const Model& rhs );

	void operator=( const Model& rhs );

	ArrayList<Mesh*> m_Meshes;

	Material* mp_Material;

}; // class Model

#endif // GRAPHICS_II_MODEL_H