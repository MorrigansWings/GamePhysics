#include "Material.h"

#include "GraphicsManager.h"
#include "ResourceManager.h"

void Material::bind( void )
{
	ShaderManager* pShaderManager = GraphicsManager::GetInstance()->getShaderManager();

	pShaderManager->setUniform3f(pShaderManager->getUniformLocation("v3Diffuse"),  m_DiffuseColor);
	pShaderManager->setUniform3f(pShaderManager->getUniformLocation("v3Ambient"),  m_AmbientColor);
	pShaderManager->setUniform3f(pShaderManager->getUniformLocation("v3Specular"), m_SpecularColor);

	if (mp_DiffuseMap)
	{
		glActiveTexture(GL_TEXTURE0);
		mp_DiffuseMap->bind();
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexDiffuse"), TRUE);
	}
	else
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexDiffuse"), FALSE);
	}

	if (mp_AmbientMap)
	{
		glActiveTexture(GL_TEXTURE1);
		mp_AmbientMap->bind();
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexAmbient"), TRUE);
	}
	else
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexAmbient"), FALSE);
	}

	if (mp_SpecularMap)
	{
		glActiveTexture(GL_TEXTURE2);
		mp_SpecularMap->bind();
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexSpecular"), TRUE);
	}
	else
	{
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexSpecular"), FALSE);
	}

	if (mp_SpecularHilightMap)
	{
		glActiveTexture(GL_TEXTURE3);
		mp_SpecularHilightMap->bind();
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexSpecularHilight"), TRUE);
	}
	else
	{
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, 0);
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexSpecularHilight"), FALSE);
	}

	if (mp_AlphaMap)
	{
		glActiveTexture(GL_TEXTURE4);
		mp_AlphaMap->bind();
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexAlpha"), TRUE);
	}
	else
	{
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, 0);
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexAlpha"), FALSE);
	}

	if (mp_BumpMap)
	{
		glActiveTexture(GL_TEXTURE5);
		mp_BumpMap->bind();
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexBump"), TRUE);
	}
	else
	{
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, 0);
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexBump"), FALSE);
	}

	if (mp_DisplacementMap)
	{
		glActiveTexture(GL_TEXTURE6);
		mp_DisplacementMap->bind();
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexDisplacement"), TRUE);
	}
	else
	{
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, 0);
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexDisplacement"), FALSE);
	}

	if (mp_DecalMap)
	{
		glActiveTexture(GL_TEXTURE7);
		mp_DecalMap->bind();
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexDecal"), TRUE);
	}
	else
	{
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, 0);
		pShaderManager->setUniform1i(pShaderManager->getUniformLocation("bHasTexDecal"), FALSE);
	}

}
