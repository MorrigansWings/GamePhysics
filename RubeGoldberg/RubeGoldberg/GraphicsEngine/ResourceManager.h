#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <Arc/ManagedObject.h>

#include <Arc/Map.h>

#include "OpenGL.h"
#include "Functions.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "ResourceLoader.h"

using namespace Arc;

class GraphicsManager;

class ResourceManager
	: public ManagedObject
{

	friend class GraphicsManager;

public:

	virtual inline string getClassName( void ) const { return "Resource Manager"; }

	Texture* loadTexture( const string& filename, GLenum minFilter, GLenum magFilter, GLenum wrapMode );

	bool loadModelFile( const string& filename );

	inline bool     hasTexture( const string& filename ) { return m_Textures.containsKey(filename); }
	inline Texture* getTexture( const string& filename ) { return (hasTexture(filename) ? m_Textures[filename] : nullptr); }


	inline bool  hasMesh( const string& name ) { return m_Meshes.containsKey(name); }
	//inline bool	 hasMesh( const Mesh& mesh ) { return m_Meshes.containsValue(mesh); }
	inline Mesh* addMesh( const string& name ) { return addMesh(name, New Mesh()); }
	inline Mesh* addMesh( const string& name, Mesh* pMesh ) { m_Meshes.add(getSafeMeshName(name), pMesh); return pMesh; }
	inline Mesh* getMesh( const string& name ) { return (hasMesh(name) ? m_Meshes[name] : nullptr); }
	string getMeshName(const Mesh* mesh);


	inline bool   hasModel( const string& name ) { return m_Models.containsKey(name); }
	inline Model* addModel( const string& name ) { return addModel(name, New Model()); }
	inline Model* addModel( const string& name, Model* pModel ) { m_Models.add(getSafeModelName(name), pModel); return pModel; }
	inline Model* getModel( const string& name ) { return (hasModel(name) ? m_Models[name] : nullptr); }
	string getModelName(const Model* model);

	inline bool      hasMaterial( const string& name ) { return m_Materials.containsKey(name); }
	inline Material* addMaterial( const string& name ) { return addMaterial(name, New Material()); }
	inline Material* addMaterial( const string& name, Material* pMaterial ) { m_Materials.add(getSafeMaterialName(name), pMaterial); return pMaterial; }
	inline Material* getMaterial( const string& name ) { return (hasMaterial(name) ? m_Materials[name] : nullptr); }

	inline Map<string, Texture*>::Iterator itTexturesBegin( void ) { return m_Textures.itBegin(); }
	inline Map<string, Texture*>::Iterator itTexturesEnd( void )   { return m_Textures.itEnd(); }

	inline Map<string, Material*>::Iterator itMaterialsBegin( void ) { return m_Materials.itBegin(); }
	inline Map<string, Material*>::Iterator itMaterialsEnd( void )   { return m_Materials.itEnd(); }

	inline Map<string, Mesh*>::Iterator itMeshsBegin( void ) { return m_Meshes.itBegin(); }
	inline Map<string, Mesh*>::Iterator itMeshsEnd( void )   { return m_Meshes.itEnd(); }

	inline Map<string, Model*>::Iterator itModelsBegin( void ) { return m_Models.itBegin(); }
	inline Map<string, Model*>::Iterator itModelsEnd( void )   { return m_Models.itEnd(); }

	bool tetherTexture( Texture* pTexture );
	bool releaseTexture( Texture* pTexture );

	inline bool tetherTexture( const string& name )  { if (m_Textures.containsKey(name)) { tetherTexture(m_Textures[name]);  return true; } return false; } 
	inline bool releaseTexture( const string& name ) { if (m_Textures.containsKey(name)) { releaseTexture(m_Textures[name]); return true; } return false; } 

	bool tetherMaterial( Material* pMaterial );
	bool releaseMaterial( Material* pMaterial );

	inline bool tetherMaterial( const string& name )  { if (m_Materials.containsKey(name)) { tetherMaterial(m_Materials[name]);  return true; } return false; } 
	inline bool releaseMaterial( const string& name ) { if (m_Materials.containsKey(name)) { releaseMaterial(m_Materials[name]); return true; } return false; } 

	bool tetherMesh( Mesh* pMesh );
	bool releaseMesh( Mesh* pMesh );

	inline bool tetherMesh( const string& name )  { if (m_Meshes.containsKey(name)) { tetherMesh(m_Meshes[name]);  return true; } return false; } 
	inline bool releaseMesh( const string& name ) { if (m_Meshes.containsKey(name)) { releaseMesh(m_Meshes[name]); return true; } return false; } 

	bool tetherModel( Model* pModel );
	bool releaseModel( Model* pModel );

	inline bool tetherModel( const string& name )  { if (m_Models.containsKey(name)) { tetherModel(m_Models[name]);  return true; } return false; } 
	inline bool releaseModel( const string& name ) { if (m_Models.containsKey(name)) { releaseModel(m_Models[name]); return true; } return false; } 

	// Unload forcibly removes it from memory, ignoring all tethers

	bool removeTexture( Texture* pTexture );
	inline bool removeTexture( const string& name ) { if (m_Textures.containsKey(name)) { removeTexture(m_Textures[name]); return true; } return false; } 

	bool removeMaterial( Material* pMaterial );
	inline bool removeMaterial( const string& name ) { if (m_Materials.containsKey(name)) { removeMaterial(m_Materials[name]); return true; } return false; } 

	bool removeMesh( Mesh* pMesh );
	inline bool removeMesh( const string& name ) { if (m_Meshes.containsKey(name)) { removeMesh(m_Meshes[name]); return true; } return false; } 

	bool removeModel( Model* pModel );
	inline bool removeModel( const string& name ) { if (m_Models.containsKey(name)) { removeModel(m_Models[name]); return true; } return false; } 

private:

	ResourceManager( void );
	virtual ~ResourceManager( void );

	ResourceManager( const ResourceManager& rhs );
	void operator=( const ResourceManager& rhs );

	string getSafeTextureName ( const string& name );
	string getSafeMaterialName( const string& name );
	string getSafeMeshName    ( const string& name );
	string getSafeModelName   ( const string& name );

	Map<string, ResourceLoader*>	m_Loaders;

	Map<string, string>				m_LoaderAlias;

	Map<string, Texture*>			m_Textures;

	Map<string, Material*>			m_Materials;

	Map<string, Mesh*>				m_Meshes;

	Map<string, Model*>				m_Models;

	Map<Texture*, int>				m_TextureTethers;

	Map<Material*, int>				m_MaterialTethers;
	
	Map<Mesh*, int>					m_MeshTethers;

	Map<Model*, int>				m_ModelTethers;

};

#endif // RESOURCE_MANAGER_H