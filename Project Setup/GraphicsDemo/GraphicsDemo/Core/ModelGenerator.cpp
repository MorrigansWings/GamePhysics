#include "ModelGenerator.h"

using namespace Models;
using namespace std;

#include "Vectors.h"
#include <iostream>

const GLuint Models::ModelGenerator::ATTR_VERTEX = 0;
const GLuint Models::ModelGenerator::ATTR_COLOR = 1;


ModelGenerator::ModelGenerator(){}

ModelGenerator::~ModelGenerator()
{
	map<string, Model>::iterator it;
	for (it = GameModelList.begin(); it != GameModelList.end(); ++it)
	{
		// delete VAO and VBOs if any
		unsigned int* p = &it->second.vao;
		glDeleteVertexArrays(1, p);
		glDeleteBuffers(it->second.vbos.size(), &it->second.vbos[0]);
		it->second.vbos.clear();
	}
	GameModelList.clear();
}

bool ModelGenerator::CreateTriangleModel(const std::string &gameModelName)
{
	// Check if model name already exists in map
	if (GameModelList.find(gameModelName) != GameModelList.end())
	{
		// Model already exists - cannot create model
		return false;
	}
	else
	{
		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		vector<VertexPC> vertices;
		vertices.push_back((VertexPC(Vector3(0.25f, -0.25f, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f))));
		vertices.push_back((VertexPC(Vector3(-0.25f, -0.25f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f))));
		vertices.push_back((VertexPC(Vector3(0.25f, 0.25f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f))));

		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPC) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(ATTR_VERTEX); // Set up position pipe
		glVertexAttribPointer(ATTR_VERTEX, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPC), (void*)0);
		glEnableVertexAttribArray(ATTR_COLOR); // Set up color pipe
		glVertexAttribPointer(ATTR_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPC), (void*)12);

//		cout << "Size of VertexPC: " << sizeof(VertexPC) << endl;
//		cout << "\tVertexPC.position: " << sizeof(Vector3) << endl;
//		cout << "\tVertexPC.color: " << sizeof(Vector4) << endl;

		Model myModel;
		myModel.vao = vao;
		myModel.vbos.push_back(vbo);
		myModel.vertexCount = vertices.size();
		GameModelList[gameModelName] = myModel;

		return true;
	}
}

bool ModelGenerator::CreateCubeModel(const std::string &gameModelName, float width)
{
	// Check if model name already exists in map
	if (GameModelList.find(gameModelName) != GameModelList.end())
	{
		// Model already exists - cannot create model
		return false;
	}
	else
	{
		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Set up coords
		Vector3 front[4] = { Vector3(-width, width, -width),
							 Vector3(-width, -width, -width),
							 Vector3(width, -width, -width),
							 Vector3(width, width, -width) };
		Vector3 back[4] = { Vector3(width, width, width),
							Vector3(width, -width, width),
							Vector3(-width, -width, width),
							Vector3(-width, width, width) };

		vector<VertexPC> vertices;
		//Front 2 triangles
		vertices.push_back(VertexPC(front[0], Vector4(0.0f, 1.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(front[1], Vector4(0.0f, 1.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(front[2], Vector4(0.0f, 1.0f, 0.0f, 1.0f)));

		vertices.push_back(VertexPC(front[0], Vector4(1.0f, 1.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(front[2], Vector4(1.0f, 1.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(front[3], Vector4(1.0f, 1.0f, 0.0f, 1.0f)));
		
		//back 2 triangles
		vertices.push_back(VertexPC(back[0], Vector4(0.0f, 1.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(back[1], Vector4(0.0f, 1.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(back[2], Vector4(0.0f, 1.0f, 0.0f, 1.0f)));

		vertices.push_back(VertexPC(back[0], Vector4(0.0f, 1.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(back[2], Vector4(0.0f, 1.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(back[3], Vector4(0.0f, 1.0f, 0.0f, 1.0f)));

		//Top
		vertices.push_back(VertexPC(back[3], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(front[0], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(front[3], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

		vertices.push_back(VertexPC(back[3], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(front[3], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(back[0], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

		// Bottom
		vertices.push_back(VertexPC(front[1], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(back[2], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(back[1], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

		vertices.push_back(VertexPC(front[1] , Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(back[1], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(front[2], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

		// Left
		vertices.push_back(VertexPC(back[3], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(back[2], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(front[1], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

		vertices.push_back(VertexPC(back[3], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(front[1], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(front[0], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

		// Right
		vertices.push_back(VertexPC(front[3], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(front[2], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(back[1], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

		vertices.push_back(VertexPC(front[3], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(back[1], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
		vertices.push_back(VertexPC(back[0], Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

		unsigned int vbo;
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPC) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0); // Set up position pipe
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPC), (void*)0);
		glEnableVertexAttribArray(1); // Set up color pipe
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPC), (void*)12);

		Model myModel;
		myModel.vao = vao;
		myModel.vbos.push_back(vbo);
		myModel.vertexCount = vertices.size();
		GameModelList[gameModelName] = myModel;

		return true;
	}
}

void ModelGenerator::DeleteModel(const std::string &gameModelName)
{
	Model model = GameModelList[gameModelName];
	unsigned int p = model.vao;
	glDeleteVertexArrays(1, &p);
	glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
	model.vbos.clear();
	GameModelList.erase(gameModelName);
}

unsigned int ModelGenerator::GetModel(const std::string &gameModelName)
{
	return GameModelList[gameModelName].vao;
}

unsigned int ModelGenerator::GetModelNumVertices(const std::string &gameModelName)
{
	return GameModelList[gameModelName].vertexCount;
}

void ModelGenerator::Draw()
{
	map<string, Model>::iterator it;
	for (it = GameModelList.begin(); it != GameModelList.end(); ++it)
	{
		glBindVertexArray(it->second.vao);
		//cout << "Drawing " << it->first.c_str()  << " with " << it->second.vertexCount << " vertices" << endl;
		glDrawArrays(GL_TRIANGLES, 0, it->second.vertexCount);
	}
}

void ModelGenerator::Draw(const std::string &gameModelName)
{
	map<string, Model>::iterator it;
	if ((it = GameModelList.find(gameModelName)) != GameModelList.end())
	{
		glBindVertexArray(it->second.vao);
		//cout << "Drawing " << it->first.c_str() << " with " << it->second.vertexCount << " vertices" << endl;
		glDrawArrays(GL_TRIANGLES, 0, it->second.vertexCount);
	}
}