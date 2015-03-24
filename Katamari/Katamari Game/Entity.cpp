#include "Entity.h"

#include "Game.h"
#include "ResourceManager.h"
#include "RenderData.h"
#include "Camera.h"

void Entity::render( const RenderData* pData )
{
	preRender(pData);
	doRender(pData);
	postRender(pData);
}

void Entity::update( const double& deltaTime )
{

}

void Entity::preRender( const RenderData* pData )
{
	ShaderManager* pShaderManager = Game::GetInstance()->getShaderManager();

	pShaderManager->useProgram("entity");

	glm::mat4x4 mModel = mat4(1.0f);
	glm::mat4x4 mViewProj, mModelView, mModelViewProj;

	mModel = glm::translate(mModel, vec3(m_Pos.x, m_Pos.y, m_Pos.z));
	mModel = glm::scale(mModel, vec3(m_Scale.x, m_Scale.y, m_Scale.z));

	mModel = glm::rotate(mModel, m_Rot.x, vec3(1.0f, 0.0f, 0.0f));
	mModel = glm::rotate(mModel, m_Rot.y, vec3(0.0f, 1.0f, 0.0f));
	mModel = glm::rotate(mModel, m_Rot.z, vec3(0.0f, 0.0f, 1.0f));

	mModelView = pData->View * mModel;
	mModelViewProj = pData->ViewProj * mModel;

	static GLint m4ModelViewLoc      = pShaderManager->getUniformLocation("uModelView");
	static GLint m4ModelViewProjLoc  = pShaderManager->getUniformLocation("uModelViewProj");
	static GLint v3GlobalAmbientLoc  = pShaderManager->getUniformLocation("uGlobalAmbient");
	static GLint v3LightColorLoc     = pShaderManager->getUniformLocation("uLightColor");
	static GLint v3LightDirectionLoc = pShaderManager->getUniformLocation("uLightDirection");
	static GLint v3HalfVectorLoc     = pShaderManager->getUniformLocation("uHalfVector");
	static GLint bGlobalLightLoc     = pShaderManager->getUniformLocation("uHasGlobalLight");

	pShaderManager->setUniformMatrix4fv(m4ModelViewProjLoc, 1, &mModelViewProj);
	pShaderManager->setUniformMatrix4fv(m4ModelViewLoc,     1, &mModelView);

	pShaderManager->setUniform3f(v3GlobalAmbientLoc,  pData->AmbientLightAmount);
	pShaderManager->setUniform3f(v3LightColorLoc,     pData->GlobalLightColor);
	pShaderManager->setUniform3f(v3LightDirectionLoc, pData->GlobalLightDirection);

	pShaderManager->setUniform1i(bGlobalLightLoc, isLightingAffected());
}

void Entity::doRender( const RenderData* pData )
{
	auto end = m_Models.itEnd();
	for (auto it = m_Models.itBegin(); it != end; ++it)
	{
		Model* pModel = (*it);
		pModel->render();
	}
}

void Entity::postRender( const RenderData* pData )
{

}

void Entity::removeModels( void )
{
	for (auto it = m_Models.itBegin(); it != m_Models.itEnd(); ++it)
	{
		Model* pModel = (*it);

		Game::GetInstance()->getResourceManager()->releaseModel(pModel);
	}
	m_Models.clear();
}

float Entity::getDistanceFromCamera( Camera* pCamera ) const
{
	vec3 tmp = m_Pos - pCamera->getPos();
	return dot(tmp, tmp);
}
