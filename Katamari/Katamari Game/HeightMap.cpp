#include "HeightMap.h"

#include "Game.h"
#include "ResourceManager.h"

HeightMap::HeightMap( void )
{
}

HeightMap::HeightMap( const string& heightMapFilename, const string& textureFilename, const GLfloat& resultWidth, const GLfloat& resultHeight, const GLfloat& topLevel, const GLfloat& bottomLevel, const int& samples )
{
	load(heightMapFilename, textureFilename, resultWidth, resultHeight, topLevel, bottomLevel, samples);
}

HeightMap::~HeightMap( void )
{
}

bool HeightMap::load( const string& heightMapFilename, const string& textureFilename, const GLfloat& resultWidth, const GLfloat& resultHeight, const GLfloat& topLevel, const GLfloat& bottomLevel, const int& samples )
{
	removeModels();

	m_Width = resultWidth;
	m_Height = resultHeight;

	SDL_Surface* pSurface = IMG_Load(heightMapFilename.c_str());

	if ( ! pSurface)
		return false;

	GLfloat halfResultWidth = resultWidth * 0.5f;
	GLfloat halfResultHeight = resultHeight * 0.5f;

	int width  = glm::clamp(pSurface->w, 0, samples);
	int height = glm::clamp(pSurface->h, 0, samples);
	GLfloat colStep = (width < pSurface->w ? ((GLfloat)pSurface->w / (GLfloat)samples) : 1.0f);
	GLfloat rowStep = (height < pSurface->h ? ((GLfloat)pSurface->h / (GLfloat)samples) : 1.0f);

	unsigned int numRawVerts = width * height;

	ArrayList<vec3> rawVerts;
	rawVerts.resize(numRawVerts);

	ArrayList<vec2> rawTexCoords;
	rawTexCoords.resize(numRawVerts);

	GLfloat stepX = resultWidth / width;
	GLfloat stepY = resultHeight / height;

	m_Heights.clear();
	m_Heights.resize(samples);

	int ind = 0;
	for (int row = 0; row < height; ++row)
	{
		m_Heights[row].resize(samples);

		for (int col = 0; col < width; ++col)
		{
			int realRow = (int)((GLfloat)row * rowStep);
			int realCol = (int)((GLfloat)col * colStep);

			Uint8* pPixel = (Uint8*) pSurface->pixels + (realRow * pSurface->pitch) + (realCol * pSurface->format->BytesPerPixel);

			float value = ((GLfloat)pPixel[0] / 255.0f);
			float heightVal = glm::lerp(bottomLevel, topLevel, value);

			m_Heights[row][col] = heightVal;

			rawVerts[ind].x = (col * stepX);
			rawVerts[ind].y = heightVal;
			rawVerts[ind].z = (row * stepY);

			rawTexCoords[ind].x = ((GLfloat)col / (GLfloat)width);
			rawTexCoords[ind].y = 1.0f - ((GLfloat)row / (GLfloat)height);

			ind++;
		}
	}

	int numVerts = (width * height) + ((width - 1) * (height - 2));

	ArrayList<vec3> verts;
	verts.resize(numVerts);

	ArrayList<vec2> texCoords;
	texCoords.resize(numVerts);

	ind = 0;
	for (int row = 0; row < height - 1; ++row)
	{
		if ((row & 1) == 0)
		{
			for (int col = 0; col < width; ++col)
			{
				int rawInd = col + (row * width);
				verts[ind]     = rawVerts[rawInd];
				texCoords[ind] = rawTexCoords[rawInd];
				++ind;

				rawInd = col + ((row + 1) * width);
				verts[ind]     = rawVerts[rawInd];
				texCoords[ind] = rawTexCoords[rawInd];
				++ind;
			}
		}
		else
		{
			for (int col = width - 1; col > 0; --col)
			{
				int rawInd = col + ((row + 1) * width);
				verts[ind]     = rawVerts[rawInd];
				texCoords[ind] = rawTexCoords[rawInd];
				++ind;

				rawInd = col - 1 + (row * width);
				verts[ind]     = rawVerts[rawInd];
				texCoords[ind] = rawTexCoords[rawInd];
				++ind;
			}
		}
	}

	if ((height & 1) && height > 2)
	{
		int rawInd = (height - 1) * width;
		verts[ind]     = rawVerts[rawInd];
		texCoords[ind] = rawTexCoords[rawInd];
		ind++;
	}

	SDL_FreeSurface(pSurface);

	Mesh* pMesh = Game::GetInstance()->getResourceManager()->addMesh("ground-triangle-strip");

	pMesh->begin(GL_TRIANGLE_STRIP, numVerts);

	pMesh->copyVertexData(verts);
	pMesh->copyTextureCoordData(texCoords);

	pMesh->end();

	Model* pModel = Game::GetInstance()->getResourceManager()->addModel("ground");
	pModel->addMesh(pMesh);

	Material* pMat = Game::GetInstance()->getResourceManager()->addMaterial("ground");
	pMat->setDiffuseMap(Game::GetInstance()->getResourceManager()->loadTexture(textureFilename, GL_LINEAR, GL_LINEAR, GL_REPEAT));
	pModel->setMaterial(pMat);

	addModel(pModel);

	return true;
}

float HeightMap::getHeightAt( vec2 pos )
{
	int x = (pos.x / m_Width) * m_Heights.getSize();
	int y = (pos.y / m_Height) * m_Heights.getSize();

	return m_Heights[y][x];
}
