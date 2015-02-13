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
#include "Core/ModelGenerator.h"
#include "Core/Camera.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cmath>

#include "Core/Shader_Loader.h"
#include <GLFW/glfw3.h>
#include "Core/Matrix.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Models::ModelGenerator *generator;
GLuint program;
Camera *cam;

#undef near
#undef far
GLfloat fieldOfView = 45.0f;
GLfloat near = 2.0f;
GLfloat far = 1500.0f;
GLFWwindow * gpWindow;

using namespace std;

void glfwError(int error, const char* description);
void glfwResize(GLFWwindow* pGLFWWindow, int width, int height);
void glfwKey(GLFWwindow* pGLFWWindow, int key, int scancode, int action, int mods);
void glfwMouseMove(GLFWwindow* pGLFWWindow, double x, double y);
void glfwMouse(GLFWwindow* pGLFWWindow, int button, int action, int mods);
void glfwMouseScroll(GLFWwindow* pGLFWWindow, double x, double y);

//void drawGround(float groundLevel);
void Init();
void renderScene(void);
void closeCallback();

int main(int argc, char ** argv)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		cout << "Could not initialize GLFW." << endl;
		exit(EXIT_FAILURE);
	}

	glfwSetErrorCallback(glfwError);

	glfwWindowHint(GLFW_DEPTH_BITS, 16);

	gpWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "A cat is fine too desu desu", NULL, NULL);
	
	if (!gpWindow)
	{
		// bad things
	}

	glfwMakeContextCurrent(gpWindow);

	glfwSwapInterval(0); // vsync

	glewExperimental = GL_TRUE;
	// Initialize glew
	if (!glewInit())
	{
		cout << "Could not initialize GLEW." << endl;
		//exit(EXIT_FAILURE);
	}

	glfwSetFramebufferSizeCallback(gpWindow, glfwResize);
	glfwSetKeyCallback(gpWindow, glfwKey);
	glfwSetMouseButtonCallback(gpWindow, glfwMouse);
	glfwSetCursorPosCallback(gpWindow, glfwMouseMove);
	glfwSetScrollCallback(gpWindow, glfwMouseScroll);

	// Display current version of OpenGL
	cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;

	Init();

	while ( ! glfwWindowShouldClose(gpWindow))
	{
		renderScene();

		glfwPollEvents();
	}

	glfwHideWindow(gpWindow);

	delete generator;
	glDeleteProgram(program);

	glfwTerminate();

	//char exiting;
	//cin >> exiting;
	return 0;
}

void Init()
{
	// Projection Settings

	
	glEnable(GL_DEPTH_TEST);

	// Initialize camera
	cam = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, gpWindow);

	// create new GameModels object and make a triangle
	generator = new Models::ModelGenerator();
	if (!generator->CreateTriangleModel("triangle1"))
		cout << "Could not create triangle1... " << endl;
	if (!generator->CreateCubeModel("cube1"))
		cout << "Could not create cube..." << endl;

	// load shaders
	Core::Shader_Loader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl",
		"Shaders\\Fragment_Shader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

Matrix4 getPerspectiveFOV(float fov, float aspectWidth, float aspectHeight, float inNear, float inFar)
{

	float const rad = fov;
	float const h = cos(0.5f * rad) / sin(0.5f * rad);
	float const w = h * aspectHeight / aspectWidth; ///todo max(width , Height) / min(width , Height)?

	Matrix4 Result(0.0f);
	Result[0][0] = w;
	Result[1][1] = h;
	Result[2][2] = -(inFar + inNear) / (inFar - inNear);
	Result[2][3] = -1.0f;
	Result[3][2] = -(2.0f * inFar * inNear) / (inFar - inNear);
	return Result;
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	glBindVertexArray(generator->GetModel("triangle1"));
	//	glBindVertexArray(generator->GetModel("cube1"));

	// use created program
	glUseProgram(program);

	// draw 3 vertices as triangles
	//	glDrawArrays(GL_TRIANGLES, 0, generator->GetModelNumVertices("cube1"));

//	drawGround(-100.0f);

	Matrix4 mat = Matrix4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(program, "uModelViewProj"), 1, GL_FALSE, (GLfloat*)&mat);

	// Draw all models
	generator->Draw();

	glfwSwapBuffers(gpWindow);
}

void closeCallback()
{
	cout << "GLUT:\t Finished" << endl;
	
}

/*// Function to draw a grid of lines
void drawGround(float groundLevel)
{
	GLfloat extent = 600.0f; // How far on the Z-Axis and X-Axis the ground extends
	GLfloat stepSize = 20.0f;  // The size of the separation between points

	// Set colour to white
	glColor3ub(255, 255, 255);

	// Draw our ground grid
	glBegin(GL_LINES);
	for (GLfloat loop = -extent; loop < extent; loop += stepSize)
	{
		// Draw lines along Z-Axis
		glVertex3f(loop, groundLevel, extent);
		glVertex3f(loop, groundLevel, -extent);

		// Draw lines across X-Axis
		glVertex3f(-extent, groundLevel, loop);
		glVertex3f(extent, groundLevel, loop);
	}
	glEnd();
}*/


void glfwError(int error, const char* description)
{
	printf("%s (%d)", description, error);
}

void glfwResize(GLFWwindow* pGLFWWindow, int width, int height)
{
}

void glfwKey(GLFWwindow* pGLFWWindow, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:

		break;
	case GLFW_RELEASE:

		break;
	case GLFW_REPEAT:


		break;
	}
}

void glfwMouseMove(GLFWwindow* pGLFWWindow, double x, double y)
{
}

void glfwMouse(GLFWwindow* pGLFWWindow, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:

		break;
	case GLFW_RELEASE:


		break;
	}
}

void glfwMouseScroll(GLFWwindow* pGLFWWindow, double x, double y)
{
}

