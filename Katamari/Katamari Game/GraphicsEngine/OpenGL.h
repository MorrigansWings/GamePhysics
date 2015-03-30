#ifndef GRAPHICS_II_OPENGL_H
#define GRAPHICS_II_OPENGL_H


#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <GLM/glm.hpp>
#include <GLM/ext.hpp>

#pragma comment( lib, "OpenGL32.lib")
#pragma comment( lib, "GLu32.lib")
#pragma comment( lib, "glew32.lib")
#pragma comment (lib, "glfw3.lib")

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat2;
using glm::mat3;
using glm::mat4;
using glm::mat2x2;
using glm::mat2x3;
using glm::mat2x4;
using glm::mat3x2;
using glm::mat3x3;
using glm::mat3x4;
using glm::mat4x2;
using glm::mat4x3;
using glm::mat4x4;

#endif // GRAPHICS_II_OPENGL_H