/*
Project: GraphicsDemo
Author: JoyLee Flahive
File: main.cpp
Description:
This project should serve as a base for further
projects in Game Physics.
*/

//#include "Dependencies\glew\glew.h"
//#include "Dependencies\freeglut\freeglut.h"
#pragma once

#include "Core/Shader_Loader.h"
#include "Core/GameModels.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>

#include "Core/Shader_Loader.h"

Models::GameModels *gameModels;
GLuint program;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	glBindVertexArray(gameModels->GetModel("triangle1"));
	
	// use created program
	glUseProgram(program);

	// draw 3 vertices as triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void closeCallback()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init()
{
	glEnable(GL_DEPTH_TEST);

	// create new GameModels object and make a triangle
	gameModels = new Models::GameModels();
	gameModels->CreateTriangleModel("triangle1");

	// load shaders
	Core::Shader_Loader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl",
										"Shaders\\Fragment_Shader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char ** argv)
{
	// Initialize application window with GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Test Window");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Initialize glew
	glewInit();

	// Display current version of OpenGL
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION);

	Init();

	// Register callbacks
	glutDisplayFunc(renderScene);
	glutCloseFunc(closeCallback);

	glutMainLoop();

	delete gameModels;
	glDeleteProgram(program);

	return 0;
}
