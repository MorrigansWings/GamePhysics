#include "Model.h"

#include "GraphicsManager.h"
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
	GraphicsManager::GetInstance()->getResourceManager()->releaseMaterial(mp_Material);
	mp_Material = nullptr;

	for (auto it = m_Meshes.itBegin(); it != m_Meshes.itEnd(); ++it)
	{
		Mesh* pMesh = (*it);
		GraphicsManager::GetInstance()->getResourceManager()->releaseMesh(pMesh);
	}
	m_Meshes.clear();
}

void Model::setMaterial(Material* pMat)
{
	GraphicsManager::GetInstance()->getResourceManager()->releaseMaterial(mp_Material);
	mp_Material = pMat;
	GraphicsManager::GetInstance()->getResourceManager()->tetherMaterial(pMat);
}

void Model::addMesh( Mesh* pMesh )
{
	m_Meshes.add(pMesh);
	GraphicsManager::GetInstance()->getResourceManager()->tetherMesh(pMesh);
}