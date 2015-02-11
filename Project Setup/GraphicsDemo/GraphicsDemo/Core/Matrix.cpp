#include "Matrix.h"
#include <sstream>

Matrix4::Matrix4(int value)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			matrix[i][j] = (float)value;
	}
}

Matrix4::Matrix4(float value)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			matrix[i][j] = value;
	}
}

Matrix4::Matrix4(float list[16])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			matrix[i][j] = list[(i * 4) + j];
	}
}

Matrix4::Matrix4(float row1[4], float row2[4], float row3[4], float row4[4])
{
	for (int i = 0; i < 4; ++i)
	{
		matrix[0][i] = row1[i];
	}
	for (int i = 0; i < 4; ++i)
	{
		matrix[1][i] = row2[i];
	}
	for (int i = 0; i < 4; ++i)
	{
		matrix[2][i] = row3[i];
	}
	for (int i = 0; i < 4; ++i)
	{
		matrix[3][i] = row4[i];
	}
}

Matrix4::Matrix4(float list[4][4])
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			matrix[i][j] = list[i][j];
	}
}

void Matrix4::fill(int value)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			matrix[i][j] = (float)value;
	}
}

const Vector4 Matrix4::operator*(const Vector4 &rhs)
{
	float result[4];
	for (int i = 0; i < 4; ++i)
	{
		result[i] =	  (matrix[i][0] * rhs.x)
					+ (matrix[i][1] * rhs.y)
					+ (matrix[i][2] * rhs.z)
					+ (matrix[i][3] * rhs.w);
	}
	return Vector4(result);
}

const Matrix4 Matrix4::operator*(const Matrix4 &rhs)
{
	float result[4][4];
	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
		{
			for (int i = 0; i < 4; ++i)
			{
				result[row][column] += matrix[row][i] * rhs.matrix[i][column];
			}
		}
	}
	return Matrix4(result);
}

const std::string Matrix4::ToString()
{
	std::stringstream output;
	output << "{ ";
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			output << matrix[i][j];
			if (j != 3)
				output << "\t";
		}
		if (i != 3)
			output << std::endl;
		else
			output << "}" << std::endl;
	}
	return output.str();
}