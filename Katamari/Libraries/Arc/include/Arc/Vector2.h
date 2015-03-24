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

#ifndef ARC_CORE_VECTOR_2_H
#define ARC_CORE_VECTOR_2_H

#include <sstream>
#include <cmath>

#include "ManagedObject.h"

#include "Types.h"
#include "RandomFunctions.h"
#include "MathFunctions.h"

using std::stringstream;

namespace Arc
{

class Vector2
	: public ManagedObject
{
public:

	static Vector2 ZERO;

	static Vector2 ONE;

	static Vector2 NEGATIVE_ONE;

	inline Vector2( void )
		: m_X(),
		  m_Y()
	{ }

	inline Vector2( const float& x, const float& y )
		: m_X(x),
		  m_Y(y)
	{ }

	inline Vector2( const float& both )
		: m_X(both),
		  m_Y(both)
	{ }

	inline Vector2( const Vector2& rhs )
		: m_X(rhs.m_X),
		  m_Y(rhs.m_Y)
	{ }

	virtual inline void operator=( const Vector2& rhs )
	{
		m_X = rhs.m_X;
		m_Y = rhs.m_Y;
	}

	virtual inline ~Vector2( void ) { }

	virtual inline string getClassName( void ) const { return "Arc Vector2"; }

	virtual inline string toString( void ) const
	{
		stringstream ss;
		ss << "[X: " << m_X << ", Y: " << m_Y << "]";
		return ss.str();
	}

	/* Generate a random Vector2 between the min and max values
	 *
	 * @param minX: The minimum X value to be generated randomly
	 * @param minY: The minimum Y value to be generated randomly
	 * @param maxX: The maximum X value to be generated randomly
	 * @param maxY: The maximum Y value to be generated randomly
	 * @returns: A random number between the min and max values
	 */
	inline static Vector2 Rand( float minX, float minY, float maxX, float maxY )
	{
		return Vector2(Arc_RandFloat(minX, maxX), Arc_RandFloat(minY, maxY));
	}

	/* Lerp between the start and end vectors by the fraction amount
	 *
	 * @param start: The starting values
	 * @param end: The ending values
	 * @param fraction: The amount to lerp between the values, should be between 0 and 1
	 * @returns: The lerped value between the start and end vectors by the fraction amount
	 */
	inline static Vector2 Lerp( const Vector2& start, const Vector2& end, float fraction )
	{
		return Vector2(Arc_Lerp(start.m_X, end.m_X, fraction), Arc_Lerp(start.m_Y, end.m_Y, fraction));
	}

	virtual inline float getX( void ) const { return m_X; }

	virtual inline float getY( void ) const { return m_Y; }

	virtual inline void setX( float x ) { m_X = x; }

	virtual inline void setY( float y ) { m_Y = y; }

	/*
	 * @returns: Half of the X value
	 */
    inline float getHalfX( void ) const { return (getX() * 0.5f); }

	/*
	 * @returns: Half of the Y value
	 */
    inline float getHalfY( void ) const { return (getY() * 0.5f); }

	/* Normalizes the vector and stores the new values in X and Y
	 */
	virtual void normalize( void );

	/* Gets a normalized copy of this vector
	 *
	 * @returns: A normalized copy of this vector
	 */
	Vector2 getNormalized( void );

	virtual inline float getLengthSquared( void )
	{
		return (m_X * m_X) + (m_Y * m_Y);
	}

	virtual inline float getLength( void )
	{
		return (float)std::sqrt(getLengthSquared());
	}

	inline float getDot( const Vector2& rhs )
	{
		return (getX() * rhs.getX()) + (getY() * rhs.getY());
	}

	virtual inline Vector2 operator-( const Vector2& rhs )
	{
		Vector2 tmp;
		tmp.m_X = m_X - rhs.m_X;
		tmp.m_Y = m_Y - rhs.m_Y;
		return tmp;
	}

	virtual inline Vector2 operator+( const Vector2& rhs )
	{
		Vector2 tmp;
		tmp.m_X = m_X + rhs.m_X;
		tmp.m_Y = m_Y + rhs.m_Y;
		return tmp;
	}

	virtual inline Vector2 operator/( const Vector2& rhs )
	{
		Vector2 tmp;
		tmp.m_X = m_X / rhs.m_X;
		tmp.m_Y = m_Y / rhs.m_Y;
		return tmp;
	}

	virtual inline Vector2 operator*( const Vector2& rhs )
	{
		Vector2 tmp;
		tmp.m_X = m_X * rhs.m_X;
		tmp.m_Y = m_Y * rhs.m_Y;
		return tmp;
	}

	virtual inline Vector2& operator+=( const Vector2& rhs )
	{
		m_X += rhs.m_X;
		m_Y += rhs.m_Y;
		return *this;
	}

	virtual inline Vector2& operator-=( const Vector2& rhs )
	{
		m_X -= rhs.m_X;
		m_Y -= rhs.m_Y;
		return *this;
	}

	virtual inline Vector2& operator*=( const Vector2& rhs )
	{
		m_X *= rhs.m_X;
		m_Y *= rhs.m_Y;
		return *this;
	}

	virtual inline Vector2& operator/=( const Vector2& rhs )
	{
		m_X /= rhs.m_X;
		m_Y /= rhs.m_Y;
		return *this;
	}

	virtual inline Vector2& operator*=( float value )
	{
		m_X *= value;
		m_Y *= value;
		return *this;
	}

	virtual inline Vector2& operator/=( float value )
	{
		m_X /= value;
		m_Y /= value;
		return *this;
	}

	virtual inline bool operator==( const Vector2& rhs ) const
	{
		return (m_X == rhs.m_X && m_Y == rhs.m_Y);
	}

	virtual inline bool operator!=( const Vector2& rhs ) const
	{
		return ! (*this == rhs);
	}

	virtual inline bool operator<( const Vector2& rhs ) const
	{
		return (m_X < rhs.m_X && m_Y < rhs.m_Y);
	}

	virtual inline bool operator>( const Vector2& rhs ) const
	{
		return (m_X > rhs.m_X && m_Y > rhs.m_Y);
	}

	virtual inline bool operator<=( const Vector2& rhs ) const
	{
		return (m_X <= rhs.m_X && m_Y <= rhs.m_Y);
	}

	virtual inline bool operator>=( const Vector2& rhs ) const
	{
		return (m_X >= rhs.m_X && m_Y >= rhs.m_Y);
	}


protected:

	float m_X;

	float m_Y;

};

} // namespace Arc

#endif // ARC_CORE_VECTOR_2_H
