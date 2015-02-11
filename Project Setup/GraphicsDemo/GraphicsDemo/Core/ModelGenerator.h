#ifndef _MODEL_GENERATOR_H_
#define _MODEL_GENERATOR_H_

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
		unsigned int vertexCount;

		Model(){}
	};

	class ModelGenerator
	{
	public:
		ModelGenerator();
		~ModelGenerator();
		bool CreateTriangleModel(const std::string &gameModelName);
		bool CreateCubeModel(const std::string &gameModelName);
		void DeleteModel(const std::string &gameModelName);
		unsigned int GetModel(const std::string &gameModelName);
		unsigned int GetModelNumVertices(const std::string &gameModelName);

		void Draw();

	private:
		std::map<std::string, Model> GameModelList;

	};

}
#endif //_MODEL_GENERATOR_H_