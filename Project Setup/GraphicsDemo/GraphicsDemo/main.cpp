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

#include "Core/Shader_Loader.h"
#include <GLFW/glfw3.h>

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

using namespace std;

void drawground(float groundLevel);

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

//	glBindVertexArray(generator->GetModel("triangle1"));
//	glBindVertexArray(generator->GetModel("cube1"));

	// use created program
	glUseProgram(program);

	// draw 3 vertices as triangles
//	glDrawArrays(GL_TRIANGLES, 0, generator->GetModelNumVertices("cube1"));

	//Reset the matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Move camera to location
	glRotatef(cam->getRotation().x, 1.0f, 0.0f, 0.0f);
	glRotatef(cam->getRotation().y, 0.0f, 1.0f, 0.0f);

	Vector3 pos = cam->getPosition();
	glTranslatef(-pos.x, -pos.y, -pos.z);

	drawground(-100.0f);


	// Draw all models
	generator->Draw();

	glutSwapBuffers();
}

void closeCallback()
{
	cout << "GLUT:\t Finished" << endl;
	glutLeaveMainLoop();
}

void Init()
{
	// GLFW Settings
	glfwSwapInterval(0); // disable vsync

	// Projection Settings
	glViewport(0, 0, (GLsizei)WINDOW_WIDTH, (GLsizei)WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspectRatio = (WINDOW_WIDTH > WINDOW_HEIGHT) ? float(WINDOW_WIDTH) / float(WINDOW_HEIGHT) : float(WINDOW_HEIGHT) / float(WINDOW_WIDTH);
	GLfloat fH = tan(float(fieldOfView / 360.0f * 3.14159f)) * near;
	GLfloat fW = fH * aspectRatio;
	glFrustum(-fW, fW, -fH, fH, near, far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);

	// create new GameModels object and make a triangle
	generator = new Models::ModelGenerator();
	if (! generator->CreateTriangleModel("triangle1"))
		cout << "Could not create triangle1... " << endl;
	if (! generator->CreateCubeModel("cube1"))
		cout << "Could not create cube..." << endl;

	// load shaders
	Core::Shader_Loader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl",
										"Shaders\\Fragment_Shader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void handleKeyPress(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case 'w':
			cam->holdingForward = true;
			break;
		case 's':
			cam->holdingBackward = true;
			break;
		case 'a':
			cam->holdingLeftStrafe = true;
			break;
		case 'd':
			cam->holdingRightStrafe = true;
			break;
		}
	}
	else
	{
		switch (key)
		{
		case 'w':
			cam->holdingForward = false;
			break;
		case 's':
			cam->holdingBackward = false;
			break;
		case 'a':
			cam->holdingLeftStrafe = false;
			break;
		case 'd':
			cam->holdingRightStrafe = false;
			break;
		}
	}
}

void handleMouseMove(int mouseX, int mouseY)
{
	cam->handleMouseMove(mouseX, mouseY);
}

int main(int argc, char ** argv)
{
	// Initialize application window with GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(20, 20);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
//	glutInitContextVersion(4, 3);
//	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(argv[0]);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	// Initialize glew
	if (!glewInit())
	{
		cout << "Could not initialize GLEW." << endl;
		exit(EXIT_FAILURE);
	}

	// Initialize GLFW
	if (!glfwInit())
	{
		cout << "Could not initialize GLFW." << endl;
		exit(EXIT_FAILURE);
	}

	// Display current version of OpenGL
	cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;

	Init();

	// Register callbacks
	glutDisplayFunc(renderScene);
	glutCloseFunc(closeCallback);

	glutMainLoop();

	delete generator;
	glDeleteProgram(program);

	glfwTerminate();

	return 0;
}

// Function to draw a grid of lines
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
}