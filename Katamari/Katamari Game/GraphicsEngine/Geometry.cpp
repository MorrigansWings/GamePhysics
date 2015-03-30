#include "Geometry.h"

#include "GraphicsManager.h"
#include "Mesh.h"
#include "ResourceManager.h"

ArrayList<vec3> Geometry::GetPlaneVerts( const GLenum& primitiveType, const vec3& pos, const GLfloat& width, const GLfloat& height, const unsigned int& resX, const unsigned int& resZ )
{
	ArrayList<vec3> outVerts;

	if (resX == 0 && resZ == 0)
		return outVerts;

	GLfloat stepX = width / (GLfloat)resX;
	GLfloat stepZ = height / (GLfloat)resZ;

	switch (primitiveType)
	{
	case GL_QUADS:
		{
			GLfloat currX = pos.x;
			GLfloat currY = pos.y;
			GLfloat currZ = pos.z;

			outVerts.resize(resX * resZ * 4);

			for (unsigned int x = 0; x < resX; ++x)
			{
				for (unsigned int z = 0; z < resZ; ++z)
				{
					outVerts.add(vec3(currX,         currY, currZ));
					outVerts.add(vec3(currX + stepX, currY, currZ));
					outVerts.add(vec3(currX + stepX, currY, currZ + stepZ));
					outVerts.add(vec3(currX,         currY, currZ + stepZ));
					
					currZ += stepZ;
				}

				currZ = 0.0f;
				currX += stepX;
			}

		}
		break;
	case GL_TRIANGLES:
		{
			GLfloat currX = pos.x;
			GLfloat currY = pos.y;
			GLfloat currZ = pos.z;

			outVerts.resize(resX * resZ * 6);

			for (unsigned int x = 0; x < resX; ++x)
			{
				for (unsigned int z = 0; z < resZ; ++z)
				{
					outVerts.add(vec3(currX,         0.0f, currZ));
					outVerts.add(vec3(currX + stepX, 0.0f, currZ));
					outVerts.add(vec3(currX + stepX, 0.0f, currZ + stepZ));

					outVerts.add(vec3(currX,         0.0f, currZ));
					outVerts.add(vec3(currX,         0.0f, currZ + stepZ));
					outVerts.add(vec3(currX + stepX, 0.0f, currZ + stepZ));

					currZ += stepZ;
				}

				currZ = 0.0f;
				currX += stepX;
			}

		}
		break;
		break;
	case GL_TRIANGLE_STRIP:
		{
			unsigned int newResX = resX + 1;
			unsigned int newResZ = resZ + 1;
			unsigned int numRawVerts = newResX * newResZ;

			ArrayList<vec3> rawVerts;
			rawVerts.resize(numRawVerts);

			int ind = 0;
			for (unsigned int row = 0; row < newResZ; ++row)
			{
				for (unsigned int col = 0; col < newResX; ++col)
				{
					vec3& vert = rawVerts[ind];

					vert.x = (col * stepX);
					vert.y = 0.0f;
					vert.z = (row * stepZ);

					vert += pos;

					ind++;
				}
			}

			int numVerts = (newResX * newResZ) + ((newResX - 1) * (newResZ - 2));

			outVerts.resize(numVerts);

			int rawInd;
			ind = 0;
			for (unsigned int row = 0; row < newResZ - 1; ++row)
			{
				if ((row & 1) == 0) // Even
				{
					for (unsigned int col = 0; col < newResX; ++col)
					{
						rawInd = col + row * newResX;
						outVerts[ind] = rawVerts[rawInd];
						++ind;

						rawInd = col + (row + 1) * newResX;
						outVerts[ind] = rawVerts[rawInd];
						++ind;
					}
				}
				else // Odd
				{
					for (unsigned int col = newResX - 1; col > 0; --col)
					{
						rawInd = col + (row + 1) * newResX;
						outVerts[ind] = rawVerts[rawInd];
						++ind;

						rawInd = col - 1 + row * newResX;
						outVerts[ind] = rawVerts[rawInd];
						++ind;
					}
				}
			}

			if ((newResZ & 1) && newResZ > 2)
			{
				int rawInd = (newResZ - 1) * newResX;
				outVerts[ind] = rawVerts[rawInd];
				ind++;
			}
		}
		break;
	}

	return outVerts;
}

ArrayList<vec3> Geometry::GetCubeVerts( const GLenum& primitiveType, const vec3& pos, const GLfloat& width, const GLfloat& height, const GLfloat& depth )
{
	ArrayList<vec3> outVerts;

	const vec3 verts[] = {
		vec3(-1.0f, -1.0f,  1.0f),
		vec3( 1.0f, -1.0f,  1.0f),
		vec3(-1.0f,  1.0f,  1.0f),
		vec3( 1.0f,  1.0f,  1.0f),
		vec3(-1.0f, -1.0f, -1.0f),
		vec3( 1.0f, -1.0f, -1.0f),
		vec3(-1.0f,  1.0f, -1.0f),
		vec3( 1.0f,  1.0f, -1.0f),
	};

	switch (primitiveType)
	{
	case GL_QUADS:
		{
			const int indices[] = {
				5, 1, 0, 4,
				7, 6, 2, 3,
				5, 7, 3, 1,
				1, 3, 2, 0,
				0, 2, 6, 4,
				7, 5, 4, 6,
			};

			outVerts.resize(sizeof(indices) / sizeof(int));

			for (int i = 0; i < sizeof(indices) / sizeof(int); ++i)
				outVerts.add(verts[indices[i]] + pos);
		}
		break;
	case GL_TRIANGLES:
		{
			const int indices[] = {
				0, 1, 2,
				1, 2, 3,
				2, 3, 7,
				3, 7, 1,
				7, 1, 5,
				1, 5, 4,
				5, 4, 7,
				4, 7, 6,
				7, 6, 2,
				6, 2, 4,
				2, 4, 0,
				4, 0, 1
			};

			outVerts.resize(sizeof(indices) / sizeof(int));

			for (int i = 0; i < sizeof(indices) / sizeof(int); ++i)
				outVerts.add(verts[indices[i]] + pos);
		}
		break;
	case GL_TRIANGLE_STRIP:
		{
			const int indices[] = {
				0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
			};

			outVerts.resize(sizeof(indices) / sizeof(int));

			for (int i = 0; i < sizeof(indices) / sizeof(int); ++i)
				outVerts.add(verts[indices[i]] + pos);
		}
		break;
	}

	return outVerts;
}

Mesh* Geometry::CreatePlane( const string& name, const GLenum& primitiveType, const vec3& pos, const GLfloat& width, const GLfloat& height, const unsigned int& resX, const unsigned int& resY )
{
	const ArrayList<vec3>& verts = GetPlaneVerts(primitiveType, pos, width, height, resX, resY);

	return CreateMesh(name, primitiveType, verts);
}

Mesh* Geometry::CreateCube( const string& name, const GLenum& primitiveType, const vec3& pos, const GLfloat& width, const GLfloat& height, const GLfloat& depth )
{
	const ArrayList<vec3>& verts = GetCubeVerts(primitiveType, pos, width, height, depth);

	return CreateMesh(name, primitiveType, verts);
}

Mesh* Geometry::CreateMesh( const string& name, const GLenum& primitiveType, const ArrayList<vec3>& verts )
{
	if (verts.isEmpty())
		return nullptr;

	Mesh* pMesh = GraphicsManager::GetInstance()->getResourceManager()->addMesh(name);

	pMesh->begin(primitiveType, verts.getSize());
	pMesh->copyVertexData(verts);
	pMesh->end();

	return pMesh;
}
