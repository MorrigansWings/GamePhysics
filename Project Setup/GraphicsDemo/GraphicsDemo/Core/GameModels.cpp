#include "GameModels.h"

using namespace Models;
using namespace std;

GameModels::GameModels(){}

GameModels::~GameModels()
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

void GameModels::CreateTriangleModel(const std::string &gameModelName)
{
	unsigned int vao;
	unsigned int vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vector<VertexPC> vertices;
	vertices.push_back((VertexPC(glm::vec3(0.25, -0.25, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))));
	vertices.push_back((VertexPC(glm::vec3(-0.25, -0.25, 0.0), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f))));
	vertices.push_back((VertexPC(glm::vec3(0.25, 0.25, 0.0), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))));
//	vector<VertexP> vertices;
//	vertices.push_back((VertexP(glm::vec3(0.25, -0.25, 0.0))));
//	vertices.push_back((VertexP(glm::vec3(-0.25, -0.25, 0.0))));
//	vertices.push_back((VertexP(glm::vec3(0.25, 0.25, 0.0))));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPC) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); // Set up position pipe
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPC), (void*)0);
	glEnableVertexAttribArray(1); // Set up color pipe
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPC), (void*)16);

	Model myModel;
	myModel.vao = vao;
	myModel.vbos.push_back(vbo);
	GameModelList[gameModelName] = myModel;
}

void GameModels::DeleteModel(const std::string &gameModelName)
{
	Model model = GameModelList[gameModelName];
	unsigned int p = model.vao;
	glDeleteVertexArrays(1, &p);
	glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
	model.vbos.clear();
	GameModelList.erase(gameModelName);
}

unsigned int GameModels::GetModel(const std::string &gameModelName)
{
	return GameModelList[gameModelName].vao;
}