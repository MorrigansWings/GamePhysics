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

#ifndef ARC_CORE_VECTOR_3_H
#define ARC_CORE_VECTOR_3_H

#include <sstream>

#include "Vector2.h"

#include "Types.h"
#include "RandomFunctions.h"
#include "MathFunctions.h"

using std::stringstream;

namespace Arc
{

class Vector3
	: public Vector2
{
public:

	static Vector3 ZERO;

	static Vector3 ONE;

	static Vector3 NEGATIVE_ONE;

	inline Vector3( void )
		: Vector2(),
		  m_Z()
	{ }

	inline Vector3( const float& x, const float& y, const float& z )
		: Vector2(x, y),
		  m_Z(z)
	{ }

	inline Vector3( const float& all )
		: Vector2(all),
		  m_Z(all)
	{ }

	inline Vector3( const Vector3& rhs )
		: Vector2(rhs.getX(), rhs.getY()),
		  m_Z(rhs.m_Z)
	{ }

	virtual inline ~Vector3( void ) { }

	virtual inline string getClassName( void ) const { return "Arc Vector3"; }

	virtual inline string toString( void ) const
	{
		stringstream ss;
		ss << "[X: " << m_X << ", Y: " << m_Y << ", Z: " << m_Z << "]";
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
	inline static Vector3 Rand( float minX, float minY, float minZ, float maxX, float maxY, float maxZ )
	{
		return Vector3(Arc_RandFloat(minX, maxX), Arc_RandFloat(minY, maxY), Arc_RandFloat(minZ, maxZ));
	}

	/* Lerp between the start and end vectors by the fraction amount
	 *
	 * @param start: The starting values
	 * @param end: The ending values
	 * @param fraction: The amount to lerp between the values, should be between 0 and 1
	 * @returns: The lerped value between the start and end vectors by the fraction amount
	 */
	inline static Vector3 Lerp( const Vector3& start, const Vector3& end, float fraction )
	{
		return Vector3(Arc_Lerp(start.getX(), end.getX(), fraction), Arc_Lerp(start.getY(), end.getY(), fraction), Arc_Lerp(start.getZ(), end.getZ(), fraction));
	}

	virtual inline float getZ( void ) const { return m_Z; }

	virtual inline void setZ( float z ) { m_Z = z; }

	/*
	 * @returns: Half of the Z value
	 */
    inline float getHalfZ( void ) const { return (getZ() * 0.5f); }

	/* Normalizes the vector and stores the new values in X, Y, and Z
	 */
	virtual void normalize( void );

	/* Gets a normalized copy of this vector
	 *
	 * @returns: A normalized copy of this vector
	 */
	Vector3 getNormalized( void );

	virtual inline float getLengthSquared( void )
	{
		return (m_X * m_X) + (m_Y * m_Y) + (m_Z * m_Z);
	}

	inline float getDot( const Vector3& rhs )
	{
		return (getX() * rhs.getX()) + (getY() * rhs.getY()) + (getZ() * rhs.getZ());
	}

	inline Vector3 getCross( Vector3& other )
	{
		Vector3 result;

		result.setX( (getY() * other.getZ()) - (getZ() * other.getY()) );
		result.setY( (getZ() * other.getX()) - (getX() * other.getZ()) );
		result.setZ( (getX() * other.getY()) - (getY() * other.getX()) );

		return result;
	}

	virtual inline Vector3 operator-( const Vector3& rhs )
	{
		Vector3 tmp;
		tmp.m_X = m_X - rhs.m_X;
		tmp.m_Y = m_Y - rhs.m_Y;
		tmp.m_Z = m_Z - rhs.m_Z;
		return tmp;
	}

	virtual inline Vector3 operator+( const Vector3& rhs )
	{
		Vector3 tmp;
		tmp.m_X = m_X + rhs.m_X;
		tmp.m_Y = m_Y + rhs.m_Y;
		tmp.m_Z = m_Z + rhs.m_Z;
		return tmp;
	}

	virtual inline Vector3 operator/( const Vector3& rhs )
	{
		Vector3 tmp;
		tmp.m_X = m_X / rhs.m_X;
		tmp.m_Y = m_Y / rhs.m_Y;
		tmp.m_Z = m_Z / rhs.m_Z;
		return tmp;
	}

	virtual inline Vector3 operator*( const Vector3& rhs )
	{
		Vector3 tmp;
		tmp.m_X = m_X * rhs.m_X;
		tmp.m_Y = m_Y * rhs.m_Y;
		tmp.m_Z = m_Z * rhs.m_Z;
		return tmp;
	}

	virtual inline void operator=( const Vector3& rhs )
	{
		Vector2::operator=(rhs);
		m_Z = rhs.m_Z;
	}

	virtual inline Vector3& operator+=( const Vector3& rhs )
	{
		Vector2::operator+=(rhs);
		m_Z += rhs.m_Z;
		return *this;
	}

	virtual inline Vector3& operator-=( const Vector3& rhs )
	{
		Vector2::operator-=(rhs);
		m_Z -= rhs.m_Z;
		return *this;
	}

	virtual inline Vector3& operator*=( const Vector3& rhs )
	{
		Vector2::operator*=(rhs);
		m_Z *= rhs.m_Z;
		return *this;
	}

	virtual inline Vector3& operator/=( const Vector3& rhs )
	{
		Vector2::operator/=(rhs);
		m_Z /= rhs.m_Z;
		return *this;
	}

	virtual inline Vector3& operator*=( float value )
	{
		Vector2::operator*=(value);
		m_Z *= value;
		return *this;
	}

	virtual inline Vector3& operator/=( float value )
	{
		Vector2::operator/=(value);
		m_Z /= value;
		return *this;
	}

	virtual inline bool operator==( const Vector3& rhs ) const
	{
		return (Vector2::operator==(rhs) && m_Z == rhs.m_Z);
	}

	virtual inline bool operator!=( const Vector3& rhs ) const
	{
		return ! (*this == rhs);
	}

	virtual inline bool operator<( const Vector3& rhs ) const
	{
		return (Vector2::operator<(rhs) && m_Z < rhs.m_Z);
	}

	virtual inline bool operator>( const Vector3& rhs ) const
	{
		return (Vector2::operator>(rhs) && m_Z > rhs.m_Z);
	}

	virtual inline bool operator<=( const Vector3& rhs ) const
	{
		return (Vector2::operator<=(rhs) && m_Z <= rhs.m_Z);
	}

	virtual inline bool operator>=( const Vector3& rhs ) const
	{
		return (Vector2::operator>=(rhs) && m_Z >= rhs.m_Z);
	}


protected:

	float m_Z;

};

} // namespace Arc

#endif // ARC_CORE_VECTOR_3_H
