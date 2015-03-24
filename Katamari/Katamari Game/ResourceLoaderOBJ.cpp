#include "ResourceLoaderOBJ.h"

#include "Game.h"
#include "ResourceManager.h"

bool ResourceLoaderOBJ::loadFromFile( const string& filename )
{
	time_t start = time(0);

	Log::InfoFmt(getClassName(), "Loading model file %s", filename.c_str());

	Buffer buffer = Buffer::LoadFromFile(filename);

	string line;

	ArrayList<vec3> verts;
	ArrayList<vec3> norms;
	ArrayList<vec2> texCoords;

	ArrayList<vec3> triVerts;
	ArrayList<vec3> quadVerts;

	ArrayList<vec3> triNorms;
	ArrayList<vec3> quadNorms;

	ArrayList<vec4> triColors;
	ArrayList<vec4> quadColors;

	ArrayList<vec2> triTexCoords;
	ArrayList<vec2> quadTexCoords;

	int triVertTotal = 0;
	int quadVertTotal = 0;

	Model* pCurrModel = nullptr;
	string modelName;

	bool endOfBuffer = buffer.endOfBuffer();
	while ( ! endOfBuffer)
	{
		line = buffer.readNextLine();

		if (line.length() == 0 || line[0] == '#')
			continue;

		size_t spacePos = line.find(' ');
		if (spacePos == string::npos)
			continue;

		string cmd;
		cmd.assign(line, 0, spacePos);

		string data;
		data.assign(line, spacePos + 1, line.size() - spacePos);

		stringstream ss(data);

		if (cmd == "v")
		{
			static vec3 vert;

			ss >> vert.x >> vert.y >> vert.z;

			verts.add(vert);
		}
		else if (cmd == "vt")
		{
			static vec2 coord;

			ss >> coord.x >> coord.y;

			texCoords.add(coord);
		}
		else if (cmd == "vn")
		{
			static vec3 norm;

			ss >> norm.x >> norm.y >> norm.z;

			norms.add(norm);
		}
		else if (cmd == "f")
		{
			int vertInds[4] = { -1, -1, -1, -1 };
			int normInds[4] = { -1, -1, -1, -1 };
			int texInds[4]  = { -1, -1, -1, -1 };

			string piece;
			int count = 0;
			for (int i = 0; getline(ss, piece, ' '); ++i)
			{
				if (piece.size() == 0)
				{
					--i;
					continue;
				}

				count++;

				bool vertAndNorm = Arc_StringContains(piece, "//");

				for (unsigned int j = 0; j < piece.size(); ++j)
				{
					if (piece[j] == '/')
						piece[j] = ' ';
				}

				stringstream ssPiece(piece);
				if (vertAndNorm)
				{
					ssPiece >> vertInds[i];
					ssPiece >> normInds[i];
				}
				else
				{
					ssPiece >> vertInds[i];
					ssPiece >> texInds[i];
					ssPiece >> normInds[i];
				}
			}

			if (count == 3)
			{
				triVertTotal += 3;

				if (vertInds[0] != -1 && vertInds[1] != -1 && vertInds[2] != -1)
				{
					triVerts.add(verts[vertInds[0] - 1]);
					triVerts.add(verts[vertInds[1] - 1]);
					triVerts.add(verts[vertInds[2] - 1]);
				}

				if (normInds[0] != -1 && normInds[1] != -1 && normInds[2] != -1)
				{
					triNorms.add(norms[normInds[0] - 1]);
					triNorms.add(norms[normInds[1] - 1]);
					triNorms.add(norms[normInds[2] - 1]);
				}

				if (texInds[0] != -1 && texInds[1] != -1 && texInds[2] != -1)
				{
					triTexCoords.add(texCoords[texInds[0] - 1]);
					triTexCoords.add(texCoords[texInds[1] - 1]);
					triTexCoords.add(texCoords[texInds[2] - 1]);
				}
			}
			else if (count == 4)
			{
				quadVertTotal += 4;

				if (vertInds[0] != -1 && vertInds[1] != -1 && vertInds[2] != -1 && vertInds[3] != -1)
				{
					quadVerts.add(verts[vertInds[0] - 1]);
					quadVerts.add(verts[vertInds[1] - 1]);
					quadVerts.add(verts[vertInds[2] - 1]);
					quadVerts.add(verts[vertInds[3] - 1]);
				}

				if (normInds[0] != -1 && normInds[1] != -1 && normInds[2] != -1 && normInds[3] != -1)
				{
					quadNorms.add(norms[normInds[0] - 1]);
					quadNorms.add(norms[normInds[1] - 1]);
					quadNorms.add(norms[normInds[2] - 1]);
					quadNorms.add(norms[normInds[3] - 1]);
				}

				if (texInds[0] != -1 && texInds[1] != -1 && texInds[2] != -1 && texInds[3] != -1)
				{
					quadTexCoords.add(texCoords[texInds[0] - 1]);
					quadTexCoords.add(texCoords[texInds[1] - 1]);
					quadTexCoords.add(texCoords[texInds[2] - 1]);
					quadTexCoords.add(texCoords[texInds[3] - 1]);
				}
			}
		}
		else if (cmd == "o" || cmd == "g")
		{
			if (pCurrModel != nullptr)
			{
				Mesh* pTriMesh  = Game::GetInstance()->getResourceManager()->addMesh(modelName + "_tris");
				Mesh* pQuadMesh = Game::GetInstance()->getResourceManager()->addMesh(modelName + "_quads");

				if (triColors.isEmpty())
					triColors.resize(triVertTotal,   vec4(-1.0f, -1.0f, -1.0f, -1.0f));

				if (quadColors.isEmpty())
					quadColors.resize(quadVertTotal, vec4(-1.0f, -1.0f, -1.0f, -1.0f));

				pTriMesh->begin(GL_TRIANGLES, triVertTotal);

				if ( ! triVerts.isEmpty())
					pTriMesh->copyVertexData(triVerts);

				if ( ! triNorms.isEmpty())
					pTriMesh->copyNormalData(triNorms);

				if ( ! triColors.isEmpty())
					pTriMesh->copyColorData(triColors);

				if ( ! triTexCoords.isEmpty())
					pTriMesh->copyTextureCoordData(triTexCoords);

				pTriMesh->end();

				pQuadMesh->begin(GL_QUADS, quadVertTotal);

				if ( ! quadVerts.isEmpty())
					pQuadMesh->copyVertexData(quadVerts);

				if ( ! quadNorms.isEmpty())
					pQuadMesh->copyNormalData(quadNorms);

				if ( ! quadColors.isEmpty())
					pQuadMesh->copyColorData(quadColors);

				if ( ! quadTexCoords.isEmpty())
					pQuadMesh->copyTextureCoordData(quadTexCoords);

				pQuadMesh->end();

				pCurrModel->addMesh(pTriMesh);
				pCurrModel->addMesh(pQuadMesh);

				Log::InfoFmt(getClassName(), "Loaded OBJ Object with %d Tris, %d Quads, and %d Total Faces", triVertTotal, quadVertTotal, (triVertTotal + quadVertTotal));

				triVertTotal = 0;
				quadVertTotal = 0;

				triVerts.clear();
				quadVerts.clear();

				triNorms.clear();
				quadNorms.clear();

				triColors.clear();
				quadColors.clear();

				triTexCoords.clear();
				quadTexCoords.clear();
			}

			if (data.size() != 0)
			{
				while (Game::GetInstance()->getResourceManager()->hasModel(data))
					data += '0';

				modelName = data;
				pCurrModel = Game::GetInstance()->getResourceManager()->addModel(modelName);
			}
		}
		else if (cmd == "mtllib")
		{
			loadMTLFile(Arc_Dirname(filename) + "/" + data);
		}
		else if (cmd == "usemtl")
		{
			pCurrModel->setMaterial(Game::GetInstance()->getResourceManager()->getMaterial(data));
		}

		endOfBuffer = buffer.endOfBuffer();

		if (endOfBuffer)
		{
			if ( ! triVerts.isEmpty() || ! quadVerts.isEmpty())
			{
				buffer.appendString("o \n");
				endOfBuffer = false;

				// If the file had no objects, shove everything in a "Default" object
				if (pCurrModel == nullptr)
				{
					pCurrModel = Game::GetInstance()->getResourceManager()->addModel("Default");
				}
			}
		}
	}

	time_t end = time(0);

	Log::InfoFmt(getClassName(), "Loading Complete, took %ds", (end - start));

	return true;
}

bool ResourceLoaderOBJ::loadMTLFile( const string& filename )
{
	Log::InfoFmt(getClassName(), "Loading material file %s", filename.c_str());

	Buffer buff = Buffer::LoadFromFile(filename);

	string line;
	Material* pCurrMtl = nullptr;

	while ( ! buff.endOfBuffer())
	{
		line = buff.readNextLine();

		if (line.length() == 0 || line[0] == '#')
			continue;

		size_t spacePos = line.find(' ');
		if (spacePos == string::npos)
			continue;

		string cmd;
		cmd.assign(line, 0, spacePos);

		string data;
		data.assign(line, spacePos + 1, line.size() - spacePos);

		stringstream ss(data);

		if (cmd == "newmtl")
		{
			pCurrMtl = Game::GetInstance()->getResourceManager()->addMaterial(data);
		}
		else 
		{
			if (pCurrMtl == nullptr)
			{
				pCurrMtl = Game::GetInstance()->getResourceManager()->addMaterial("Default");
			}

			if (cmd == "Ka")
			{
				float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

				stringstream ssPiece(data);

				ssPiece >> color[0];
				ssPiece >> color[1];
				ssPiece >> color[2];
				ssPiece >> color[3];

				pCurrMtl->setAmbientColor(vec4(color[0], color[1], color[2], color[3]));
			}
			else if(cmd == "Kd")
			{
				float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

				stringstream ssPiece(data);

				ssPiece >> color[0];
				ssPiece >> color[1];
				ssPiece >> color[2];
				ssPiece >> color[3];

				pCurrMtl->setDiffuseColor(vec4(color[0], color[1], color[2], color[3]));
			}
			else if(cmd == "Ks")
			{
				float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

				stringstream ssPiece(data);

				ssPiece >> color[0];
				ssPiece >> color[1];
				ssPiece >> color[2];
				ssPiece >> color[3];

				pCurrMtl->setSpecularColor(vec4(color[0], color[1], color[2], color[3]));
			}
			else if (cmd == "Ns")
			{

			}
			else if (cmd == "d" || cmd == "Tr")
			{

			}
			else if (cmd == "illum")
			{

			}
			else if (cmd == "map_Ka")
			{
				pCurrMtl->setAmbientMap(Game::GetInstance()->getResourceManager()->loadTexture(Arc_Dirname(filename) + "/" + data, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT));
			}
			else if (cmd == "map_Kd")
			{
				pCurrMtl->setDiffuseMap(Game::GetInstance()->getResourceManager()->loadTexture(Arc_Dirname(filename) + "/" + data, GL_LINEAR, GL_LINEAR, GL_REPEAT));
			}
			else if (cmd == "map_Ks")
			{
				pCurrMtl->setSpecularMap(Game::GetInstance()->getResourceManager()->loadTexture(Arc_Dirname(filename) + "/" + data, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT));
			}
			else if (cmd == "map_Ns")
			{
				pCurrMtl->setSpecularHilightMap(Game::GetInstance()->getResourceManager()->loadTexture(Arc_Dirname(filename) + "/" + data, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT));
			}
			else if (cmd == "map_d")
			{
				pCurrMtl->setAlphaMap(Game::GetInstance()->getResourceManager()->loadTexture(Arc_Dirname(filename) + "/" + data, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT));
			}
			else if (cmd == "map_bump" || cmd == "bump")
			{
				pCurrMtl->setBumpMap(Game::GetInstance()->getResourceManager()->loadTexture(Arc_Dirname(filename) + "/" + data, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT));
			}
			else if (cmd == "disp")
			{
				pCurrMtl->setDisplacementMap(Game::GetInstance()->getResourceManager()->loadTexture(Arc_Dirname(filename) + "/" + data, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT));
			}
			else if (cmd == "decal")
			{
				pCurrMtl->setDecalMap(Game::GetInstance()->getResourceManager()->loadTexture(Arc_Dirname(filename) + "/" + data, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT));
			}
		}
	}

	return true;
}
