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

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>

#include "Core/Shader_Loader.h"

using namespace Core;

GLuint program;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);

	// use created program
	glUseProgram(program);

	// draw 3 vertices as triangles
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void Init()
{
	glEnable(GL_DEPTH_TEST);

	// load shaders
	Shader_Loader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl",
										"Shaders\\Fragment_Shader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char ** argv)
{
	// Initialize application window with GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Test Window");

	// Initialize glew if supported
	glewInit();
	if (glewIsSupported("GL_VERSION_4_5"))
		std::cout << "OpenGL Version is 4.5\n";
	else
		std::cout << "OpenGL Version 4.5 is not supported.\n";

	Init();

//	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(renderScene);
	glutMainLoop();
	glDeleteProgram(program);

	return 0;
}
