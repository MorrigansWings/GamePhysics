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

#ifndef ARC_CORE_MATH_FUNCTIONS_H
#define ARC_CORE_MATH_FUNCTIONS_H

namespace Arc
{

/* Determines if a value is between two other numbers
 *
 * @param value: The value to check
 * @param min: The minimum value of the range to check
 * @param max: The maximum value of the range to check
 * @returns: True if the value is between the min and max values or equal to either, False otherwise
 */
template <class Number>
inline bool Arc_Between( Number value, Number min, Number max )
{
	return ( value >= min && value <= max);
}

/* Calculates a linear interpolation
 *
 * @param start: The number to start at, returned when fraction is 0
 * @param end: The number to end at, returned when fraction is 1
 * @param fraction: The value from 0 to 1 to interpolate between the two numbers where
 *     a value of 0 will return the start number, and a value of 1 will return the end
 * @returns: A number between the start and end values, determined by the fraction amount
 */
template <class Number>
inline Number Arc_Lerp( Number start, Number end, float fraction)
{
	return (Number)( start + (end - start) * fraction );
}

template <class Number>
inline Number Arc_Clamp(Number value, Number min, Number max)
{
	return ( ( value > max ) ? max : ( ( value < min ) ? min : value ) );
}

template <class Number>
inline int Arc_Sign( Number value )
{
	return ( value > 0 ? 1 : ( value < 0 ? -1 : 0 ) );
}

float Arc_Floor(float value, int accuracy);

float Arc_Nearest(float value, int accuracy);

float Arc_Ceil(float value, int accuracy);

double Arc_Floor(double value, int accuracy);

double Arc_Nearest(double value, int accuracy);

double Arc_Ceil(double value, int accuracy);


} // namespace Arc

#endif // ARC_CORE_MATH_FUNCTIONS_H
