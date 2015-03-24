#include "Model.h"

#include "Game.h"
#include "ResourceManager.h"
#include "Functions.h"

void Model::render( void )
{
	if (mp_Material)
	{
		mp_Material->bind();
	}

	for (auto it = m_Meshes.itBegin(); it != m_Meshes.itEnd(); ++it)
	{
		Mesh* pMesh = (*it);
		pMesh->render();
	}
}

Model::~Model( void )
{
	Game::GetInstance()->getResourceManager()->releaseMaterial(mp_Material);
	mp_Material = nullptr;

	for (auto it = m_Meshes.itBegin(); it != m_Meshes.itEnd(); ++it)
	{
		Mesh* pMesh = (*it);
		Game::GetInstance()->getResourceManager()->releaseMesh(pMesh);
	}
	m_Meshes.clear();
}

void Model::setMaterial(Material* pMat)
{
	Game::GetInstance()->getResourceManager()->releaseMaterial(mp_Material);
	mp_Material = pMat;
	Game::GetInstance()->getResourceManager()->tetherMaterial(pMat);
}

void Model::addMesh( Mesh* pMesh )
{
	m_Meshes.add(pMesh);
	Game::GetInstance()->getResourceManager()->tetherMesh(pMesh);
}