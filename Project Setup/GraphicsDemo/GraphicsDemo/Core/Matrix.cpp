#include "Matrix.h"
#include <sstream>
#include <iomanip>

const Matrix4 Matrix4::IDENTITY = Matrix4(1.0f);

Matrix4::Matrix4()
{
	memset(matrix, 0, sizeof(float) * 16);
}

Matrix4::Matrix4(int value)
{
	for (int i = 0; i < 4; ++i)
	{
		matrix[i][i] = (float)value;
	}
}

Matrix4::Matrix4(float value)
{
	for (int i = 0; i < 4; ++i)
	{
		matrix[i][i] = value;
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

// Gives a perspective projection matrix looking at center from eye
// where up is the up direction
Matrix4 Matrix4::lookAt(Vector3 eye, Vector3 center, Vector3 up)
{
	Vector3 f = (center - eye).normalize();
	Vector3 s = (Vector3::cross(f, up)).normalize();
	Vector3 u = Vector3::cross(s, f);

	Matrix4 Result = IDENTITY;
	Result.insert(0, 0, s.x);
	Result.insert(1, 0, s.y);
	Result.insert(2, 0, s.z);
	Result.insert(0, 1, u.x);
	Result.insert(1, 1, u.y);
	Result.insert(2, 1, u.z);
	Result.insert(0, 2, -f.x);
	Result.insert(1, 2, -f.y);
	Result.insert(2, 2, -f.z);
	Result.insert(3, 0, -(Vector3::dot(s, eye)));
	Result.insert(3, 1, -(Vector3::dot(u, eye)));
	Result.insert(3, 2, Vector3::dot(f, eye));
	return Result;
}

Matrix4 Matrix4::perspectiveFOV(float fov, float width, float height, float zNear, float zFar)
{
	float rad = fov;
	float h = cos(0.5f * rad) / sin(0.5f * rad);
	float w = h * height / width;

	Matrix4 result;
	result.insert(0, 0, w);
	result.insert(1, 1, h);
	result.insert(2, 2, -(zFar + zNear) / (zFar - zNear));
	result.insert(2, 3, 1.0f);
	result.insert(3, 2, -(2.0f * zFar * zNear) / (zFar / zNear));
	return result;
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
			result[row][column] = 0.0f;
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
	output << "\n{ ";
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			output << std::setprecision(5) << matrix[i][j];
			if (j != 3)
				output << "\t";
		}
		if (i != 3)
			output << std::endl << "  ";
		else
			output << "}" << std::endl;
	}
	return output.str();
}