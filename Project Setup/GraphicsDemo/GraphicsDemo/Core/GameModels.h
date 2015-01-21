#ifndef _GAME_MODELS_H_
#define _GAME_MODELS_H_

#pragma once

#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"

#include "Vertex.h"

#include <vector>
#include <map>

namespace Models
{
	struct Model
	{
		unsigned int vao;
		std::vector<unsigned int> vbos;

		Model(){}
	};

	class GameModels
	{
	public:
		GameModels();
		~GameModels();
		void CreateTriangleModel(const std::string &gameModelName);
		void DeleteModel(const std::string &gameModelName);
		unsigned int GetModel(const std::string &gameModelName);

	private:
		std::map<std::string, Model> GameModelList;

	};

}
#endif