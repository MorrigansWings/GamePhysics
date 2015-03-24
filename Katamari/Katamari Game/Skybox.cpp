#include "Skybox.h"

#include "Game.h"
#include "ResourceManager.h"
#include "RenderData.h"

void Skybox::preRender( const RenderData* pData )
{
	ShaderManager* pShaderManager = Game::GetInstance()->getShaderManager();

	pShaderManager->useProgram("skybox");

	glm::mat4x4 mModel = mat4(1.0f);
	glm::mat4x4 mViewProj, mModelViewProj;

	mModel = glm::translate(mModel, vec3(m_Pos.x, m_Pos.y, m_Pos.z));
	mModel = glm::scale(mModel, vec3(m_Scale.x, m_Scale.y, m_Scale.z));

	mModel = glm::rotate(mModel, m_Rot.x, vec3(1.0f, 0.0f, 0.0f));
	mModel = glm::rotate(mModel, m_Rot.y, vec3(0.0f, 1.0f, 0.0f));
	mModel = glm::rotate(mModel, m_Rot.z, vec3(0.0f, 0.0f, 1.0f));

	static GLint m4ModelViewProjLoc  = pShaderManager->getUniformLocation("uModelViewProj");

	mModelViewProj = pData->ViewProj * mModel;

	pShaderManager->setUniformMatrix4fv(m4ModelViewProjLoc, 1, &mModelViewProj);

	static GLint uTexLoc = pShaderManager->getUniformLocation("uTex");

	pShaderManager->setUniform1i(uTexLoc, 0);

	glActiveTexture(GL_TEXTURE0);
	mp_Tex->bind();
}

void Skybox::postRender( const RenderData* pData )
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

bool Skybox::load( const string& filename )
{
	removeModels(); 

	mp_Tex = Game::GetInstance()->getResourceManager()->loadTexture(filename, GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);

	if ( ! mp_Tex )
	{
		Game::GetInstance()->getResourceManager()->releaseTexture(mp_Tex);
		return false;
	}

	const GLfloat SKYBOX_SCALE = 1000.0f;

	vec3 skyboxVerts[24] = {
		vec3(-1.0f,  1.0f, -1.0f), vec3( 1.0f,  1.0f, -1.0f), vec3( 1.0f, -1.0f, -1.0f), vec3(-1.0f, -1.0f, -1.0f), // Front
		vec3(-1.0f,  1.0f,  1.0f), vec3(-1.0f,  1.0f, -1.0f), vec3(-1.0f, -1.0f, -1.0f), vec3(-1.0f, -1.0f,  1.0f), // Left
		vec3( 1.0f,  1.0f,  1.0f), vec3(-1.0f,  1.0f,  1.0f), vec3(-1.0f, -1.0f,  1.0f), vec3( 1.0f, -1.0f,  1.0f), // Back
		vec3( 1.0f,  1.0f, -1.0f), vec3( 1.0f,  1.0f,  1.0f), vec3( 1.0f, -1.0f,  1.0f), vec3( 1.0f, -1.0f, -1.0f), // Right
		vec3(-1.0f,  1.0f,  1.0f), vec3( 1.0f,  1.0f,  1.0f), vec3( 1.0f,  1.0f, -1.0f), vec3(-1.0f,  1.0f, -1.0f), // Top
		vec3(-1.0f, -1.0f,  1.0f), vec3( 1.0f, -1.0f,  1.0f), vec3( 1.0f, -1.0f, -1.0f), vec3(-1.0f, -1.0f, -1.0f)  // Bottom
	};

	const GLfloat ONE_FOURTH   = 0.25f;
	const GLfloat TWO_FOURTH   = 0.5f;
	const GLfloat THREE_FOURTH = 0.75f;
	const GLfloat ONE_THIRD    = 1.0f / 3.0f + 0.0015f;
	const GLfloat TWO_THIRD    = 2.0f / 3.0f - 0.0015f;

	vec2 skyboxTxcrds[24] = {
		vec2( ONE_FOURTH,   TWO_THIRD ), vec2( TWO_FOURTH,   TWO_THIRD ), vec2( TWO_FOURTH,   ONE_THIRD ), vec2( ONE_FOURTH,   ONE_THIRD ), // Front
		vec2( 0.0f,         TWO_THIRD ), vec2( ONE_FOURTH,   TWO_THIRD ), vec2( ONE_FOURTH,   ONE_THIRD ), vec2( 0.0f,         ONE_THIRD ), // Left
		vec2( THREE_FOURTH, TWO_THIRD ), vec2( 1.0f,         TWO_THIRD ), vec2( 1.0f,         ONE_THIRD ), vec2( THREE_FOURTH, ONE_THIRD ), // Back
		vec2( TWO_FOURTH,   TWO_THIRD ), vec2( THREE_FOURTH, TWO_THIRD ), vec2( THREE_FOURTH, ONE_THIRD ), vec2( TWO_FOURTH,   ONE_THIRD ), // Right
		vec2( ONE_FOURTH,   1.0f      ), vec2( TWO_FOURTH,   1.0f      ), vec2( TWO_FOURTH,   TWO_THIRD ), vec2( ONE_FOURTH,   TWO_THIRD ), // Up
		vec2( ONE_FOURTH,   0.0f      ), vec2( TWO_FOURTH,   0.0f      ), vec2( TWO_FOURTH,   ONE_THIRD ), vec2( ONE_FOURTH,   ONE_THIRD )  // Down
	};

	for (int i = 0; i < 24; ++i)
		skyboxVerts[i] *= SKYBOX_SCALE;

	Mesh* pMesh = Game::GetInstance()->getResourceManager()->addMesh("skybox-quads");
	pMesh->begin(GL_QUADS, 24);
	pMesh->copyVertexData(skyboxVerts);
	pMesh->copyTextureCoordData(skyboxTxcrds);
	pMesh->end();

	Model* pModel = Game::GetInstance()->getResourceManager()->addModel("skybox");
	pModel->addMesh(pMesh);

	addModel(pModel);

	return true;
}