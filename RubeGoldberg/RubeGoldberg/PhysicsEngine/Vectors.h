#ifndef _VECTORS_H_
#define _VECTORS_H_

#include <string>
#include <glm/glm.hpp>

namespace Physics
{

	class Vector2
	{
	public:
		const static Vector2 ZERO;

		float x, y;

		Vector2()
			: x(0.0f)
			, y(0.0f)
		{}

		Vector2(float inX, float inY)
			:x(inX)
			, y(inY)
		{}

		Vector2(int inX, int inY)
			:x((float)inX)
			, y((float)inY)
		{}

		Vector2(float values[2])
			: x(values[0])
			, y(values[1])
		{}

		const Vector2 operator+(const Vector2 &rhs);
		const Vector2 operator+(const int modifier);
		const Vector2 operator+(const float modifier);
		const Vector2 operator=(const Vector2 &rhs);

		const std::string ToString();

		inline glm::vec2 GLM() { return glm::vec2(this->x, this->y); }
	};


	class Vector4;

	class Vector3
	{
	public:
		const static Vector3 ZERO;

		float x, y, z;

		Vector3()
			: x(0.0f)
			, y(0.0f)
			, z(0.0f)
		{}

		Vector3(int value)
			: x((float)value)
			, y((float)value)
			, z((float)value)
		{}

		Vector3(float value)
			: x(value)
			, y(value)
			, z(value)
		{}

		// Float constructor for Vector3
		Vector3(float inX, float inY, float inZ)
			: x(inX)
			, y(inY)
			, z(inZ)
		{}

		// Int constructor for Vector3
		Vector3(int inX, int inY, int inZ)
			: x((float)inX)
			, y((float)inY)
			, z((float)inZ)
		{}

		Vector3(float values[3])
			: x(values[0])
			, y(values[1])
			, z(values[2])
		{}

		Vector3(Vector2 base, float inZ)
			: x(base.x)
			, y(base.y)
			, z(inZ)
		{}

		Vector3(const Vector3 &orig)
			: x(orig.x)
			, y(orig.y)
			, z(orig.z)
		{}

		void invert();
		Vector3 getInverted();
		float magnitude();
		float squareMagnitude();
		Vector3 normalize();
		Vector3 getNormalized();
		Vector3 addScaledVector(const Vector3 &velocity, float t);

		float dot(const Vector3 &second);
		Vector3 cross(const Vector3 &second);

		const Vector4 ConvertToHomogeneous();

		const Vector3 operator+(const int modifier);
		const Vector3 operator+(const float modifier);
		const Vector3 operator+(const Vector3 &rhs);

		const Vector3 operator+=(const float modifier);
		const Vector3 operator+=(const Vector3 &rhs);

		Vector3 operator-(const float modifier);
		Vector3 operator-(const Vector3 &rhs);
		Vector3 operator-(const Vector3 &rhs) const;

		Vector3 operator-=(const float modifier);
		Vector3 operator-=(const Vector3 &rhs);

		const Vector3 operator=(const Vector3 &rhs);

		Vector3 operator*(const float rhs);
		Vector3 operator*=(const float rhs);

		Vector3 operator/(const float rhs);
		Vector3 operator/=(const float rhs);

		const std::string ToString();

		static Vector3 cross(const Vector3 &first, const Vector3 &second);
		static float dot(const Vector3 &first, const Vector3 &second);
		static float getDistance(const Vector3 &first, const Vector3 &second);

		inline glm::vec3 GLM() { return glm::vec3(this->x, this->y, this->z); }
	};

	class Vector4
	{
	public:
		const static Vector4 ZERO;

		float x, y, z, w;

		Vector4()
			: x(0.0f)
			, y(0.0f)
			, z(0.0f)
			, w(0.0f)
		{}

		Vector4(float value)
			: x(value)
			, y(value)
			, z(value)
			, w(value)
		{}

		Vector4(float inR, float inG, float inB, float inA)
			: x(inR)
			, y(inG)
			, z(inB)
			, w(inA)
		{}

		Vector4(int inR, int inG, int inB, int inA)
			: x((float)inR)
			, y((float)inG)
			, z((float)inB)
			, w((float)inA)
		{}

		Vector4(float values[4])
			: x(values[0])
			, y(values[1])
			, z(values[2])
			, w(values[3])
		{}

		Vector4(const Vector3 &base, float inW)
			: x(base.x)
			, y(base.y)
			, z(base.z)
			, w(inW)
		{}

		Vector4(const Vector4 &orig)
			: x(orig.x)
			, y(orig.y)
			, z(orig.z)
			, w(orig.w)
		{}

		const Vector4 operator+(const Vector4 &rhs);
		const Vector4 operator=(const Vector4 &rhs);

		inline glm::vec4 GLM() { return glm::vec4(this->x, this->y, this->z, this->w); }
	};
}

#endif // _VECTORS_H_