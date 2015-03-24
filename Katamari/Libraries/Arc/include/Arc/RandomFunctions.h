/* This file is part of Arc.
 *
 * Arc is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Arc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Arc; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * Author: Stephen Lane-Walsh
 *
 */

#ifndef ARC_CORE_RANDOM_FUNCTIONS_H
#define ARC_CORE_RANDOM_FUNCTIONS_H

#include <cstdlib>
#include <ctime>

namespace Arc
{

void Arc_InitRandom( void );

int Arc_RandInt( int min, int max );

float Arc_RandFloat( float min, float max );

double Arc_RandDouble( double min, double max );

} // namespace Arc

#endif // ARC_CORE_RANDOM_FUNCTIONS_H
