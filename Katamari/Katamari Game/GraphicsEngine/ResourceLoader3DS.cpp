#include "ResourceLoader3DS.h"

#include "GraphicsManager.h"
#include "ResourceManager.h"
#include "Log.h"

void Chunk3DS::load( const unsigned long& chunkStart, Buffer& buff, const string& filename )
{
	m_StartOffset = chunkStart;
	m_ID = ReadInt(buff, chunkStart);
	m_Length = ReadLong(buff, chunkStart + 2);

	// Data for Object Chunks
	static unsigned int numFaces = 0;
	static ArrayList<vec3> vertices;
	static ArrayList<vec3> normals;
	static ArrayList<vec2> texCoords;
	static ArrayList<int> vertInds;
	//static ArrayList<int> texCoordInds;
	static string useMatName;

	// Data for Material Chunks
	static Material* pMat = nullptr;
	static string matName;
	static string matFilename;

	//Log::InfoFmt(getClassName(), "Loading Chunk (ID 0x%04X, Length %d)", m_ID, m_Length);

	unsigned int dataOffset = 6; // Size of ID and Length

	switch (m_ID)
	{
	case 0x4000: // Object Chunk
		{
			string name;
			char ch = '\0';
			int ind = 0;
			do 
			{
				ch = ReadChar(buff, chunkStart + dataOffset + ind);
				name += ch;
				ind++;
			} 
			while (ch != '\0' && ind < 20);

			Log::InfoFmt(getClassName(), "Read Object Chunk, Name: %s", name.c_str());

			numFaces = 0;
			vertices.clear();
			normals.clear();
			vertInds.clear();
			//texCoordInds.clear();

			useMatName = "";

			loadChildren(dataOffset + ind, buff, filename); // Size of ID and Length

			ArrayList<vec3> verts;
			verts.resize(numFaces * 3);

			ArrayList<vec2> txcrds;
			txcrds.resize(numFaces * 3);

			bool hasTexCoords = ! texCoords.isEmpty();

			unsigned int vertInd = 0;
			unsigned int texCoordInd = 0;
			for (unsigned int faceInd = 0; faceInd < numFaces; ++faceInd)
			{
				unsigned int first  = vertInds[(faceInd * 3)];
				unsigned int second = vertInds[(faceInd * 3) + 1];
				unsigned int third  = vertInds[(faceInd * 3) + 2];

				verts[vertInd]     = vertices[first];
				verts[vertInd + 1] = vertices[second];
				verts[vertInd + 2] = vertices[third];

				vertInd += 3;
				
				if (hasTexCoords)
				{
					txcrds[texCoordInd]     = (first  < texCoords.getSize() ? texCoords[first]  : vec2());
					txcrds[texCoordInd + 1] = (second < texCoords.getSize() ? texCoords[second] : vec2());
					txcrds[texCoordInd + 2] = (third  < texCoords.getSize() ? texCoords[third]  : vec2());

					texCoordInd += 3;
				}
			}

			Model* pModel = GraphicsManager::GetInstance()->getResourceManager()->addModel(name);
			Mesh* pTris   = GraphicsManager::GetInstance()->getResourceManager()->addMesh(name + "_tris");

			Log::InfoFmt(getClassName(), "Loaded 3DS Object with %d Tris", numFaces);

			pTris->begin(GL_TRIANGLES, numFaces * 3);
			pTris->copyVertexData(verts);
			pTris->copyTextureCoordData(txcrds);
			pTris->end();

			pModel->addMesh(pTris);

			if (useMatName.size() > 0)
			{
				pModel->setMaterial(GraphicsManager::GetInstance()->getResourceManager()->getMaterial(useMatName));
			}
		}
		break;
	case 0x4110: // Vertices List
		{
			unsigned int count = ReadInt(buff, chunkStart + dataOffset);

			vertices.resize(count);
			//Log::InfoFmt(getClassName(), "Read Vertices List Chunk, Count: %d", count);

			unsigned int vertOffset = chunkStart + dataOffset + 2;
			for (unsigned int i = 0; i < count; ++i)
			{
				vec3& vert = vertices[i];
				vert.x = ReadFloat(buff, vertOffset);
				vert.y = ReadFloat(buff, vertOffset + 4);
				vert.z = ReadFloat(buff, vertOffset + 8);

				vertOffset += 12;

				//Log::InfoFmt(getClassName(), "Vertex (%5.2f, %5.2f, %5.2f)", vert.x, vert.y, vert.z);
			}
		}
		break;
	case 0x4120: // Faces Description Chunk
		{
			unsigned int count = ReadInt(buff, chunkStart + dataOffset);
			numFaces = count;
			vertInds.resize(count * 3);

			//Log::InfoFmt(getClassName(), "Read Faces Chunk, Count: %d", count);

			unsigned int tmpDiff = 0;
			unsigned int faceOffset = chunkStart + dataOffset + 2;
			for (unsigned int i = 0; i < count; ++i)
			{
				 vertInds[(i * 3)]     = ReadInt(buff, faceOffset);
				 vertInds[(i * 3) + 1] = ReadInt(buff, faceOffset + 2);
				 vertInds[(i * 3) + 2] = ReadInt(buff, faceOffset + 4);

				 faceOffset += 8;

				 //Log::InfoFmt(getClassName(), "Face (%d, %d, %d)(%d, %d, %d)", faces[0], faces[1], faces[2], faces[3], faces[4], faces[5]);
			}

			loadChildren(faceOffset - chunkStart, buff, filename);
		}
		break;
	case 0x4130: // Face Material List
		{
			Log::InfoFmt(getClassName(), "Read Face Material List, Length: %d", m_Length);

			useMatName = ReadString(buff, chunkStart + dataOffset, 20);

		}
		break;
	case 0x4140: // Texture Coordinate List
		{
			unsigned int count = ReadInt(buff, chunkStart + dataOffset);

			texCoords.resize(count);
			//Log::InfoFmt(getClassName(), "Read Tex Coord List Chunk, Count: %d", count);

			unsigned int texCoordOffset = chunkStart + dataOffset + 2;
			for (unsigned int i = 0; i < count; ++i)
			{
				vec2& vert = texCoords[i];
				vert.x = ReadFloat(buff, texCoordOffset);
				vert.y = ReadFloat(buff, texCoordOffset + 4);

				texCoordOffset += 4;

				//Log::InfoFmt(getClassName(), "Tex Coord (%5.2f, %5.2f)", vert.x, vert.y);
			}
		}
		break;
	case 0x4160: // Translation Matrix Chunk
		{
			//Log::Info(getClassName(), "Read Translation Matrix Chunk");

			unsigned int matOffset = chunkStart + dataOffset;
			float matrix[4][4];
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 3; ++j)
				{
					matrix[i][j] = buff.readFloatAt(matOffset);
					matOffset += 4;
				}

			matrix[0][3] = 0.0f;
			matrix[1][3] = 0.0f;
			matrix[2][3] = 0.0f;
			matrix[3][3] = 1.0f;

			for (int i = 0; i < 4; ++i)
			{
				//Log::InfoFmt(getClassName(), "[%5.2f][%5.2f][%5.2f][%5.2f]", matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3]);
			}
		}
		break;
	case 0xA000: // Material Name Chunk
		{
			matName = ReadString(buff, chunkStart + dataOffset, 20);

			//Log::InfoFmt(getClassName(), "Read Material Name, Name: %s", matName.c_str());

			pMat = GraphicsManager::GetInstance()->getResourceManager()->addMaterial(matName);
		}
		break;
	case 0xA010: // Ambient Color

		//Log::InfoFmt(getClassName(), "Read Ambient Color Chunk, Length %d", m_Length);

		break;
	case 0xA020: // Diffuse Color

		//Log::InfoFmt(getClassName(), "Read Diffuse Color Chunk, Length %d", m_Length);

		break;
	case 0xA030: // Specular Color

		//Log::InfoFmt(getClassName(), "Read Specular Color Chunk, Length %d", m_Length);

		break;
	case 0xA040: // Shininess Percent

		//Log::InfoFmt(getClassName(), "Read Shininess Percent Chunk, Length %d", m_Length);

		break;
	case 0xA050: // Shininess Strength Percent

		//Log::InfoFmt(getClassName(), "Read Shininess Strength Percent Chunk, Length %d", m_Length);

		break;
	case 0xA300: // Material Map Filename
		{
			matFilename = ReadString(buff, chunkStart + dataOffset, 16);

			//Log::InfoFmt(getClassName(), "Filename: %s", matFilename.c_str());
		}
		break;
	case 0xA200: // Texture Map 1
		{
			//Log::Info(getClassName(), "Read Texture Map 1 Chunk");

			loadChildren(dataOffset, buff, filename);

			if (matFilename.size() > 0)
				pMat->setDiffuseMap(GraphicsManager::GetInstance()->getResourceManager()->loadTexture(Arc_Dirname(filename) + "/" + matFilename, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT));
		}
		break;
	case 0xA33A: // Texture Map 2
		{
			//Log::Info(getClassName(), "Read Texture Map 2 Chunk");

			loadChildren(dataOffset, buff, filename);
		}
		break;
	case 0xA210: // Opacity Map
		{
			//Log::Info(getClassName(), "Read Opacity Map Chunk");

			loadChildren(dataOffset, buff, filename);
		}
		break;
	case 0xA230: // Bump Map
		{
			//Log::Info(getClassName(), "Read Bump Map Chunk");

			loadChildren(dataOffset, buff, filename);
		}
		break;
	case 0xA33C: // Shininess Map
		{
			//Log::Info(getClassName(), "Read Shininess Map Chunk");

			loadChildren(dataOffset, buff, filename);
		}
		break;
	case 0xA204: // Specular Map
		{
			//Log::Info(getClassName(), "Read Specular Map Chunk");

			loadChildren(dataOffset, buff, filename);
		}
		break;
	case 0xA33D: // Self Illum. Map
		{
			//Log::Info(getClassName(), "Read Self Illum. Map Chunk");

			loadChildren(dataOffset, buff, filename);
		}
		break;
	case 0xA220: // Reflection Map
		{
			//Log::Info(getClassName(), "Read Reflection Map Chunk");

			loadChildren(dataOffset, buff, filename);
		}
		break;
	case 0xA33E: // Mask For Texture Map 1

		//Log::Info(getClassName(), "Read Texture Map 1 Mask Chunk");

		break;
	case 0xA340: // Mask For Texture Map 2

		//Log::Info(getClassName(), "Read Texture Map 2 Mask Chunk");

		break;
	case 0xA342: // Mask For Opacity Map

		//Log::Info(getClassName(), "Read Opacity Map Mask Chunk");

		break;
	case 0xA344: // Mask For Bump Map

		//Log::Info(getClassName(), "Read Bump Map Mask Chunk");

		break;
	case 0xA346: // Mask For Shininess Map

		//Log::Info(getClassName(), "Read Shininess Map Mask Chunk");

		break;
	case 0xA348: // Mask For Specular Map

		//Log::Info(getClassName(), "Read Specular Map Mask Chunk");

		break;
	case 0xA34A: // Mask For Self Illum. Map

		//Log::Info(getClassName(), "Read Illum. Map Mask Chunk");

		break;
	case 0xA34C: // Mask For Reflection Map

		//Log::Info(getClassName(), "Read Reflection Map Mask Chunk");

		break;
	case 0x4D4D: // Root Chunk
	case 0x3D3D: // 3D Editor Chunk
	case 0x4100: // Geometry Chunk
	case 0xAFFF: // Material List Chunk
		{
			loadChildren(dataOffset, buff, filename);
		}
		break;
	}
}

void Chunk3DS::loadChildren( const unsigned long& childrenStart, Buffer& buff, const string& filename )
{
	unsigned int offset = childrenStart;

	while (offset < m_Length)
	{
		m_Children.add(Chunk3DS(m_StartOffset + offset, buff, filename));
		Chunk3DS& chunk = m_Children.getBack();
		offset += chunk.getLength();
	}
}

bool ResourceLoader3DS::loadFromFile( const string& filename )
{
	time_t start = time(0);

	Buffer buff = Buffer::LoadFromFile(filename, true);

	if (Chunk3DS::ReadInt(buff, 0) != 0x4D4D)
	{
		Log::ErrorFmt(getClassName(), "Error loading file %s, not a valid 3DS file", filename.c_str());
		return false;
	}

	Chunk3DS root(0, buff, filename);

	time_t end = time(0);

	Log::InfoFmt(getClassName(), "Loading Complete, took %ds", (end - start));

	return true;
}