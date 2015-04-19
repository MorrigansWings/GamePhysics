#ifndef MATRICES_H
#define MATRICES_H

#include <string.h>
#include <glm/glm.hpp>
#include "Vectors.h"

namespace Physics
{
	class Matrix3
	{
	public:
		float	x0, y0, z0,
				x1, y1, z1,
				x2, y2, z2;

		Matrix3()
			: x0(0.0f), y0(0.0f), z0(0.0f)
			, x1(0.0f), y1(0.0f), z1(0.0f)
			, x2(0.0f), y2(0.0f), z2(0.0f)
		{}

		Matrix3(float value)
			: x0(value), y0(value), z0(value)
			, x1(value), y1(value), z1(value)
			, x2(value), y2(value), z2(value)
		{}

		Matrix3(float xzero, float yzero, float zzero, 
				float xone, float yone, float zone,
				float xtwo, float ytwo, float ztwo)
			: x0(xzero), y0(yzero), z0(zzero)
			, x1(xone), y1(yone), z1(zone)
			, x2(xtwo), y2(ytwo), z2(ztwo)
		{}

		~Matrix3(){}

		inline glm::mat3 GLM() { return glm::mat3(	x0, y0, z0, 
													x1, y1, z1, 
													x2, y2, z2); }
		Matrix3 operator*(float value);
		Vector3 operator*(Vector3 &rhs);
		
		Matrix3 getTranspose();
		float getDeterminant();
		Matrix3 getInverse();


	};

	class Matrix4
	{
	public:
		float	x0, y0, z0, w0, 
				x1, y1, z1, w1,
				x2, y2, z2, w2,
				x3, y3, z3, w3;

		Matrix4()
			: x0(0.0f), y0(0.0f), z0(0.0f), w0(0.0f)
			, x1(0.0f), y1(0.0f), z1(0.0f), w1(0.0f)
			, x2(0.0f), y2(0.0f), z2(0.0f), w2(0.0f)
			, x3(0.0f), y3(0.0f), z3(0.0f), w3(0.0f)
		{}

		Matrix4(float value)
			: x0(value), y0(value), z0(value), w0(value)
			, x1(value), y1(value), z1(value), w1(value)
			, x2(value), y2(value), z2(value), w2(value)
			, x3(value), y3(value), z3(value), w3(value)
		{}

		Matrix4(float xzero, float yzero, float zzero, float wzero,
				float xone, float yone, float zone, float wone,
				float xtwo, float ytwo, float ztwo, float wtwo,
				float xthree, float ythree, float zthree, float wthree)
				: x0(xzero), y0(yzero), z0(zzero), w0(wzero)
				, x1(xone), y1(yone), z1(zone), w1(wone)
				, x2(xtwo), y2(ytwo), z2(ztwo), w2(wtwo)
				, x3(xthree), y3(ythree), z3(zthree), w3(wthree)
		{}

		Matrix4 getTranslationWithRotation(Matrix3 &base, Vector3 &trans);

		inline glm::mat4 GLM() { return glm::mat4(	x0, y0, z0, w0,
													x1, y1, z1, w1,
													x2, y2, z2, w2,
													x3, y3, z3, w3); }

	};
}



#endif //MATRICES_H