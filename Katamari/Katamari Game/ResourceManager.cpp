#include "ResourceManager.h"

#include "Game.h"
#include "Log.h"
#include "ResourceLoaderOBJ.h"
#include "ResourceLoader3DS.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

ResourceManager::ResourceManager( void )
{
	m_Loaders.add("obj", New ResourceLoaderOBJ());
	m_Loaders.add("3ds", New ResourceLoader3DS());
	//s_Loaders.add("dae", New ResourceLoaderDAE());
}

ResourceManager::~ResourceManager( void )
{
	for (auto it = m_Loaders.itBegin(); it != m_Loaders.itEnd(); ++it)
	{
		ResourceLoader* pLoader = it->second;
		delete pLoader;
		it->second = nullptr;
	}
	m_Loaders.clear();

	while ( ! m_Meshes.isEmpty())
		removeMesh(m_Meshes.itBegin()->second);
	
	while ( ! m_Materials.isEmpty())
		removeMaterial(m_Materials.itBegin()->second);

	while ( ! m_Models.isEmpty())
		removeModel(m_Models.itBegin()->second);

	while ( ! m_Textures.isEmpty())
		removeTexture(m_Textures.itBegin()->second);
}

Texture* ResourceManager::loadTexture( const string& filename, GLenum minFilter, GLenum magFilter, GLenum wrapMode )
{
	if (m_Textures.containsKey(filename))
		return m_Textures[filename];

	string ext = Arc_FileExtension(filename);

	// Load the texture from a file
	SDL_Surface *surface = IMG_Load(filename.c_str());

	if ( ! surface)
	{
		Log::ErrorFmt("Resource Manager", "Error Loading Texture %s", SDL_GetError());
		return nullptr;
	}

	GLuint texID = 0;

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	GLenum mode;

	if (Arc_FileExtension(filename) == "tga")
	{
		mode = GL_BGR;

		if (surface->format->BytesPerPixel == 4)
			mode = GL_BGRA;
	}
	else
	{
		mode = GL_RGB;

		if (surface->format->BytesPerPixel == 4)
			mode = GL_RGBA;
	}
	
	//glGenerateMipmap(GL_TEXTURE_2D);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	Texture* pTex = New Texture(texID, surface->w, surface->h);

	m_Textures.add(getSafeTextureName(filename), pTex);

	SDL_FreeSurface(surface);

	tetherTexture(pTex);
	return pTex;
}

bool ResourceManager::loadModelFile( const string& filename )
{
	if (filename == "")
		return false;

	string ext = Arc_FileExtension(filename);

	while (m_LoaderAlias.containsKey(ext))
		ext = m_LoaderAlias[ext];

	if ( ! m_Loaders.containsKey(ext))
		return false;

	ResourceLoader* pLoader = m_Loaders[ext];

	return pLoader->loadFromFile(filename);
}

bool ResourceManager::tetherTexture( Texture* pTexture )
{
	if (m_TextureTethers.containsKey(pTexture))
	{
		m_TextureTethers[pTexture]++;
		return true;
	}

	if (m_Textures.containsValue(pTexture))
	{
		m_TextureTethers.add(pTexture, 1);
		return true;
	}

	return false;
}

bool ResourceManager::releaseTexture( Texture* pTexture )
{
	if (m_TextureTethers.containsKey(pTexture))
	{
		int count = --m_TextureTethers[pTexture];

		if (count <= 0)
		{
			removeTexture(pTexture);
		}
	}

	if (m_Textures.containsValue(pTexture))
	{
		removeTexture(pTexture);
	}

	return false;
}

bool ResourceManager::tetherMaterial( Material* pMaterial )
{
	if (m_MaterialTethers.containsKey(pMaterial))
	{
		m_MaterialTethers[pMaterial]++;
		return true;
	}

	if (m_Materials.containsValue(pMaterial))
	{
		m_MaterialTethers.add(pMaterial, 1);
		return true;
	}

	return false;
}

bool ResourceManager::releaseMaterial( Material* pMaterial )
{
	if (m_MaterialTethers.containsKey(pMaterial))
	{
		int count = --m_MaterialTethers[pMaterial];

		if (count <= 0)
		{
			removeMaterial(pMaterial);
		}
	}

	if (m_Materials.containsValue(pMaterial))
	{
		removeMaterial(pMaterial);
	}

	return false;
}

bool ResourceManager::tetherMesh( Mesh* pMesh )
{
	if (m_MeshTethers.containsKey(pMesh))
	{
		m_MeshTethers[pMesh]++;
		return true;
	}

	if (m_Meshes.containsValue(pMesh))
	{
		m_MeshTethers.add(pMesh, 1);
		return true;
	}

	return false;
}

bool ResourceManager::releaseMesh( Mesh* pMesh )
{
	if (m_MeshTethers.containsKey(pMesh))
	{
		int count = --m_MeshTethers[pMesh];

		if (count <= 0)
		{
			removeMesh(pMesh);
		}
	}

	if (m_Meshes.containsValue(pMesh))
	{
		removeMesh(pMesh);
	}

	return false;
}

bool ResourceManager::tetherModel( Model* pModel )
{
	if (m_ModelTethers.containsKey(pModel))
	{
		m_ModelTethers[pModel]++;
		return true;
	}

	if (m_Models.containsValue(pModel))
	{
		m_ModelTethers.add(pModel, 1);
		return true;
	}

	return false;
}

bool ResourceManager::releaseModel( Model* pModel )
{
	if (m_ModelTethers.containsKey(pModel))
	{
		int count = --m_ModelTethers[pModel];

		if (count <= 0)
		{
			removeModel(pModel);
		}
	}

	if (m_Models.containsValue(pModel))
	{
		removeModel(pModel);
	}

	return false;
}

bool ResourceManager::removeTexture( Texture* pTexture )
{
	if ( ! m_Textures.containsValue(pTexture))
		return false;

	GLuint texID = pTexture->getGLTexture();
	glDeleteTextures(1, &texID);

	delete pTexture;

	m_TextureTethers.removeKey(pTexture);
	m_Textures.removeFirstValue(pTexture);

	return true;
}

bool ResourceManager::removeMaterial( Material* pMaterial )
{
	if ( ! m_Materials.containsValue(pMaterial))
		return false;

	delete pMaterial;

	m_MaterialTethers.removeKey(pMaterial);
	m_Materials.removeFirstValue(pMaterial);

	return true;
}

bool ResourceManager::removeMesh( Mesh* pMesh )
{
	if ( ! m_Meshes.containsValue(pMesh))
		return false;

	delete pMesh;

	m_MeshTethers.removeKey(pMesh);
	m_Meshes.removeFirstValue(pMesh);

	return true;
}

bool ResourceManager::removeModel( Model* pModel )
{
	if ( ! m_Models.containsValue(pModel))
		return false;

	delete pModel;

	m_ModelTethers.removeKey(pModel);
	m_Models.removeFirstValue(pModel);

	return true;
}

string ResourceManager::getSafeTextureName( const string& name )
{
	if ( ! m_Textures.containsKey(name))
		return name;

	stringstream ss;
	int index = 0;

	do 
	{
		ss.clear(); ss.str(name);
		ss << index;
		++index;
	}
	while (m_Textures.containsKey(ss.str()));

	return ss.str();
}

string ResourceManager::getSafeMaterialName( const string& name )
{
	if ( ! m_Materials.containsKey(name))
		return name;

	stringstream ss;
	int index = 0;

	do 
	{
		ss.clear(); ss.str(name);
		ss << index;
		++index;
	}
	while (m_Materials.containsKey(ss.str()));

	return ss.str();
}

string ResourceManager::getSafeMeshName( const string& name )
{
	if ( ! m_Meshes.containsKey(name))
		return name;

	stringstream ss;
	int index = 0;

	do 
	{
		ss.clear(); ss.str(name);
		ss << index;
		++index;
	}
	while (m_Meshes.containsKey(ss.str()));

	return ss.str();
}

string ResourceManager::getSafeModelName( const string& name )
{
	if ( ! m_Models.containsKey(name))
		return name;

	stringstream ss;
	int index = 0;

	do 
	{
		ss.clear(); ss.str(name);
		ss << index;
		++index;
	}
	while (m_Models.containsKey(ss.str()));

	return ss.str();
}
