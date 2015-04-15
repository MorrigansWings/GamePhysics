/* This file is part of ArcCore.
 *
 * ArcCore is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ArcCore is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcCore; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Author: Stephen Lane-Walsh
 *
 */

#ifndef ARC_CORE_VECTOR_4_H
#define ARC_CORE_VECTOR_4_H

#include <sstream>

#include "Vector3.h"

#include "Types.h"
#include "RandomFunctions.h"
#include "MathFunctions.h"

using std::stringstream;

namespace Arc
{

class Vector4
	: public Vector3
{
public:

	static Vector4 ZERO;

	static Vector4 ONE;

	static Vector4 NEGATIVE_ONE;

	inline Vector4( void )
		: Vector3(),
		  m_W()
	{ }

	inline Vector4( const float& x, const float& y, const float& z, const float& w )
		: Vector3(x, y, z),
		  m_W(w)
	{ }

	inline Vector4( const float& all )
		: Vector3(all),
		  m_W(all)
	{ }

	inline Vector4( const Vector4& rhs )
		: Vector3(rhs.getX(), rhs.getY(), rhs.getZ()),
		  m_W(rhs.m_W)
	{ }

	virtual inline ~Vector4( void ) { }

	virtual inline string getClassName( void ) const { return "Arc Vector4"; }

	virtual inline string toString( void ) const
	{
		stringstream ss;
		ss << "[X: " << m_X << ", Y: " << m_Y << ", Z: " << m_Z << ", W: " << m_W << "]";
		return ss.str();
	}

	/* Generate a random Vector3 between the min and max values
	 *
	 * @param minX: The minimum X value to be generated randomly
	 * @param minY: The minimum Y value to be generated randomly
	 * @param minZ: The minimum Z value to be generated randomly
	 * @param maxX: The maximum X value to be generated randomly
	 * @param maxY: The maximum Y value to be generated randomly
	 * @param maxZ: The maximum Z value to be generated randomly
	 * @returns: A random number between the min and max values
	 */
	inline static Vector4 Rand( float minX, float minY, float minZ, float minW, float maxX, float maxY, float maxZ, float maxW )
	{
		return Vector4(Arc_RandFloat(minX, maxX), Arc_RandFloat(minY, maxY), Arc_RandFloat(minZ, maxZ), Arc_RandFloat(minW, maxW));
	}

	/* Lerp between the start and end vectors by the fraction amount
	 *
	 * @param start: The starting values
	 * @param end: The ending values
	 * @param fraction: The amount to lerp between the values, should be between 0 and 1
	 * @returns: The lerped value between the start and end vectors by the fraction amount
	 */
	inline static Vector4 Lerp( const Vector4& start, const Vector4& end, float fraction )
	{
		return Vector4(Arc_Lerp(start.getX(), end.getX(), fraction), Arc_Lerp(start.getY(), end.getY(), fraction), Arc_Lerp(start.getZ(), end.getZ(), fraction), Arc_Lerp(start.getW(), end.getW(), fraction));
	}

	virtual inline float getW( void ) const { return m_W; }

	virtual inline void setW( float z ) { m_W = z; }

	/*
	 * @returns: Half of the Z value
	 */
    inline float getHalfW( void ) const { return (getW() * 0.5f); }

	/* Normalizes the vector and stores the new values in X, Y, and Z
	 */
	virtual void normalize( void );

	/* Gets a normalized copy of this vector
	 *
	 * @returns: A normalized copy of this vector
	 */
	Vector4 getNormalized( void );

	virtual inline float getLengthSquared( void )
	{
		return (m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z) + (m_W * m_W);
	}

	inline float getDot( const Vector4& rhs )
	{
		return (getX() * rhs.getX()) + (getY() * rhs.getY()) + (getZ() * rhs.getZ()) + (getW() * rhs.getW());
	}

	virtual inline Vector4 operator-( const Vector4& rhs )
	{
		Vector4 tmp;
		tmp.m_X = m_X - rhs.m_X;
		tmp.m_Y = m_Y - rhs.m_Y;
		tmp.m_Z = m_Z - rhs.m_Z;
		tmp.m_W = m_W - rhs.m_W;
		return tmp;
	}

	virtual inline Vector4 operator+( const Vector4& rhs )
	{
		Vector4 tmp;
		tmp.m_X = m_X + rhs.m_X;
		tmp.m_Y = m_Y + rhs.m_Y;
		tmp.m_Z = m_Z + rhs.m_Z;
		tmp.m_W = m_W + rhs.m_W;
		return tmp;
	}

	virtual inline Vector4 operator/( const Vector4& rhs )
	{
		Vector4 tmp;
		tmp.m_X = m_X / rhs.m_X;
		tmp.m_Y = m_Y / rhs.m_Y;
		tmp.m_Z = m_Z / rhs.m_Z;
		tmp.m_W = m_W / rhs.m_W;
		return tmp;
	}

	virtual inline Vector4 operator*( const Vector4& rhs )
	{
		Vector4 tmp;
		tmp.m_X = m_X * rhs.m_X;
		tmp.m_Y = m_Y * rhs.m_Y;
		tmp.m_Z = m_Z * rhs.m_Z;
		tmp.m_W = m_W * rhs.m_W;
		return tmp;
	}

	virtual inline void operator=( const Vector4& rhs )
	{
		Vector3::operator=(rhs);
		m_W = rhs.m_W;
	}

	virtual inline Vector4& operator+=( const Vector4& rhs )
	{
		Vector3::operator+=(rhs);
		m_W += rhs.m_W;
		return *this;
	}

	virtual inline Vector4& operator-=( const Vector4& rhs )
	{
		Vector3::operator-=(rhs);
		m_W -= rhs.m_W;
		return *this;
	}

	virtual inline Vector4& operator*=( const Vector4& rhs )
	{
		Vector3::operator*=(rhs);
		m_W *= rhs.m_W;
		return *this;
	}

	virtual inline Vector4& operator/=( const Vector4& rhs )
	{
		Vector3::operator/=(rhs);
		m_W /= rhs.m_W;
		return *this;
	}

	virtual inline Vector4& operator*=( float value )
	{
		Vector3::operator*=(value);
		m_W *= value;
		return *this;
	}

	virtual inline Vector4& operator/=( float value )
	{
		Vector3::operator/=(value);
		m_W /= value;
		return *this;
	}

	virtual inline bool operator==( const Vector4& rhs ) const
	{
		return (Vector3::operator==(rhs) && m_W == rhs.m_W);
	}

	virtual inline bool operator!=( const Vector4& rhs ) const
	{
		return ! (*this == rhs);
	}

	virtual inline bool operator<( const Vector4& rhs ) const
	{
		return (Vector3::operator<(rhs) && m_W < rhs.m_W);
	}

	virtual inline bool operator>( const Vector4& rhs ) const
	{
		return (Vector3::operator>(rhs) && m_W > rhs.m_W);
	}

	virtual inline bool operator<=( const Vector4& rhs ) const
	{
		return (Vector3::operator<=(rhs) && m_W <= rhs.m_W);
	}

	virtual inline bool operator>=( const Vector4& rhs ) const
	{
		return (Vector3::operator>=(rhs) && m_W >= rhs.m_W);
	}


protected:

	float m_W;

};

} // namespace Arc

#endif // ARC_CORE_VECTOR_4_H
