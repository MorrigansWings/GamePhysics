/* This file is part of ArcData.
 * 
 * ArcData is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * ArcData is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with ArcData; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * 
 * Author: Stephen Lane-Walsh
 * 
 */

#ifndef ARC_DATA_PLY_PROPERTY_TYPES_H
#define ARC_DATA_PLY_PROPERTY_TYPES_H

#include <Arc/Types.h>

namespace Arc
{

typedef string PLYPropertyType;

struct PLYPropertyTypes
{
	static PLYPropertyType PROP_TYPE_INVALID;

	static PLYPropertyType PROP_TYPE_CHAR;

	static PLYPropertyType PROP_TYPE_UCHAR;

	static PLYPropertyType PROP_TYPE_SHORT;

	static PLYPropertyType PROP_TYPE_USHORT;

	static PLYPropertyType PROP_TYPE_INT;

	static PLYPropertyType PROP_TYPE_UINT;

	static PLYPropertyType PROP_TYPE_FLOAT;

	static PLYPropertyType PROP_TYPE_DOUBLE;

	static PLYPropertyType PROP_TYPE_INT8;

	static PLYPropertyType PROP_TYPE_UINT8;

	static PLYPropertyType PROP_TYPE_INT16;

	static PLYPropertyType PROP_TYPE_UINT16;

	static PLYPropertyType PROP_TYPE_INT32;

	static PLYPropertyType PROP_TYPE_UINT32;

	static PLYPropertyType PROP_TYPE_INT64;

	static PLYPropertyType PROP_TYPE_UINT64;

	static PLYPropertyType PROP_TYPE_FLOAT32;

	static PLYPropertyType PROP_TYPE_FLOAT64;
};

} // namespace Arc

#endif // ARC_DATA_PLY_PROPERTY_TYPES_H