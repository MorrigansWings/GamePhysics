/*
Project: GraphicsDemo
Author: JoyLee Flahive
File: main.cpp
Description:
This project should serve as a base for further
projects in Game Physics.
*/

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL Test Window");

	glutMainLoop();

	return 0;
}