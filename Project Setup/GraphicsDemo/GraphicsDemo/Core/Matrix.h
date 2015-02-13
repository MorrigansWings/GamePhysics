#ifndef MATRIX_H
#define MATRIX_H

#pragma once

#include <iostream>
#include "..\Dependencies\glew\glew.h"
#include "Vectors.h"

class Matrix4
{
public:
	static const Matrix4 IDENTITY;
	// Rows, then columns
	float matrix[4][4];

	Matrix4();
	Matrix4(int value);
	Matrix4(float value);
	Matrix4(float list[16]);
	Matrix4(float row1[4], float row2[4], float row3[4], float row4[4]);
	Matrix4(float list[4][4]);

	void fill(int value);
	inline void insert(int row, int column, float value){ matrix[row][column] = value; }
	
	static Matrix4 lookAt(Vector3 eye, Vector3 center, Vector3 up);
	static Matrix4 perspectiveFOV(float fov, float width, float height, float zNear, float zFar);

	const Vector4 operator*(const Vector4 &rhs);
	const Matrix4 operator*(const Matrix4 &rhs);

	const std::string ToString();
};


#endif // MATRIX_H