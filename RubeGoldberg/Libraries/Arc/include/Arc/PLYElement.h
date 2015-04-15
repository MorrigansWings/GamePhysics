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

#ifndef ARC_DATA_PLY_ELEMENT_H
#define ARC_DATA_PLY_ELEMENT_H

#include <Arc/ArcCore.h>
#include <Arc/ManagedObject.h>

#include "PLYElementType.h"

namespace Arc
{

class PLYDocument;

class PLYElement
	: public ManagedObject
{

	friend class PLYDocument;

public:

	static PLYElement INVALID;

	inline PLYElement( const PLYElement& rhs )
		: mp_Document(rhs.mp_Document),
		  m_Type(rhs.m_Type),
		  m_CharData(rhs.m_CharData),
		  m_UCharData(rhs.m_UCharData),
		  m_ShortData(rhs.m_ShortData),
		  m_UShortData(rhs.m_UShortData),
		  m_IntData(rhs.m_IntData),
		  m_UIntData(rhs.m_UIntData),
		  m_LongData(rhs.m_LongData),
		  m_ULongData(rhs.m_ULongData),
		  m_FloatData(rhs.m_FloatData),
		  m_DoubleData(rhs.m_DoubleData),
		  m_CharDataList(rhs.m_CharDataList),
		  m_UCharDataList(rhs.m_UCharDataList),
		  m_ShortDataList(rhs.m_ShortDataList),
		  m_UShortDataList(rhs.m_UShortDataList),
		  m_IntDataList(rhs.m_IntDataList),
		  m_UIntDataList(rhs.m_UIntDataList),
		  m_LongDataList(rhs.m_LongDataList),
		  m_ULongDataList(rhs.m_ULongDataList),
		  m_FloatDataList(rhs.m_FloatDataList),
		  m_DoubleDataList(rhs.m_DoubleDataList)
	{ }

	virtual inline string getClassName( void ) const { return "Arc PLY Element"; }

	inline void setTypeName( const string& type ) { m_Type = type; }

	inline string getTypeName( void ) const { return m_Type; }

	inline char getCharData( const string& name )
	{
		return (m_CharData.containsKey(name) ? m_CharData[name] : 0);
	}

	inline unsigned char getUCharData( const string& name )
	{
		return (m_UCharData.containsKey(name) ? m_UCharData[name] : (unsigned)0);
	}

	inline short getShortData( const string& name )
	{
		return (m_ShortData.containsKey(name) ? m_ShortData[name] : 0);
	}

	inline unsigned short getUShortData( const string& name )
	{
		return (m_UShortData.containsKey(name) ? m_UShortData[name] : (unsigned)0);
	}

	inline int getIntData( const string& name )
	{
		return (m_IntData.containsKey(name) ? m_IntData[name] : 0);
	}

	inline unsigned int getUIntData( const string& name )
	{
		return (m_UIntData.containsKey(name) ? m_UIntData[name] : (unsigned)0);
	}

	inline long getLongData( const string& name )
	{
		return (m_LongData.containsKey(name) ? m_LongData[name] : 0);
	}

	inline unsigned long getULongData( const string& name )
	{
		return (m_ULongData.containsKey(name) ? m_ULongData[name] : (unsigned)0);
	}

	inline float getFloatData( const string& name )
	{
		return (m_FloatData.containsKey(name) ? m_FloatData[name] : 0.0f);
	}

	inline double getDoubleData( const string& name )
	{
		return (m_DoubleData.containsKey(name) ? m_CharData[name] : 0.0);
	}

	inline Arc_int8_t getInt8Data( const string& name ) { return getCharData(name); }

	inline Arc_uint8_t getUInt8Data( const string& name ) { return getUCharData(name); }

	inline Arc_int16_t getInt16Data( const string& name ) { return getShortData(name); }

	inline Arc_uint16_t getUInt16Data( const string& name ) { return getUShortData(name); }

	inline Arc_int32_t getInt32Data( const string& name ) { return getIntData(name); }

	inline Arc_uint32_t getUInt32Data( const string& name ) { return getUIntData(name); }

	inline Arc_int64_t getInt64Data( const string& name ) { return getLongData(name); }

	inline Arc_uint64_t getUInt64Data( const string& name ) { return getULongData(name); }

	inline float getFloat32Data( const string& name ) { return getFloatData(name); }

	inline double getFloat64Data( const string& name ) { return getDoubleData(name); }

	inline void setCharData( const string& name, const char& data )
	{
		(m_CharData.containsKey(name) ? m_CharData[name] = data : m_CharData.add(name, data));
	}

	inline void setUCharData( const string& name, const unsigned char& data )
	{
		(m_UCharData.containsKey(name) ? m_UCharData[name] = data : m_UCharData.add(name, data));
	}

	inline void setShortData( const string& name, const short& data )
	{
		(m_ShortData.containsKey(name) ? m_ShortData[name] = data : m_ShortData.add(name, data));
	}

	inline void setUShortData( const string& name, const unsigned short& data )
	{
		(m_UShortData.containsKey(name) ? m_UShortData[name] = data : m_UShortData.add(name, data));
	}

	inline void setIntData( const string& name, const int& data )
	{
		(m_IntData.containsKey(name) ? m_IntData[name] = data : m_IntData.add(name, data));
	}

	inline void setUIntData( const string& name, const unsigned int& data )
	{
		(m_UIntData.containsKey(name) ? m_UIntData[name] = data : m_UIntData.add(name, data));
	}

	inline void setLongData( const string& name, const long& data )
	{
		(m_LongData.containsKey(name) ? m_LongData[name] = data : m_LongData.add(name, data));
	}

	inline void setULongData( const string& name, const unsigned long& data )
	{
		(m_ULongData.containsKey(name) ? m_ULongData[name] = data : m_ULongData.add(name, data));
	}

	inline void setFloatData( const string& name, const float& data )
	{
		(m_FloatData.containsKey(name) ? m_FloatData[name] = data : m_FloatData.add(name, data));
	}

	inline void setDoubleData( const string& name, const double& data )
	{
		(m_DoubleData.containsKey(name) ? m_DoubleData[name] = data : m_DoubleData.add(name, data));
	}

	inline void setInt8Data( const string& name, const Arc_int8_t& data ) { setCharData(name, (char)data); }

	inline void setUInt8Data( const string& name, const Arc_uint8_t& data ) { setUCharData(name, (unsigned char)data); }

	inline void setInt16Data( const string& name, const Arc_int16_t& data ) { setShortData(name, (short)data); }

	inline void setUInt16Data( const string& name, const Arc_uint16_t& data ) { setUShortData(name, (unsigned short)data); }

	inline void setInt32Data( const string& name, const Arc_int32_t& data ) { setIntData(name, (int)data); }

	inline void setUInt32Data( const string& name, const Arc_uint32_t& data ) { setUIntData(name, (unsigned int)data); }

	inline void setInt64Data( const string& name, const Arc_int64_t& data ) { setLongData(name, (long)data); }

	inline void setUInt64Data( const string& name, const Arc_uint64_t& data ) { setULongData(name, (unsigned long)data); }

	inline void setFloat32Data( const string& name, const float& data ) { setFloatData(name, data); }

	inline void setFloat64Data( const string& name, const double& data ) { setDoubleData(name, data); }

	inline void addCharDataToList( const char& data )
	{
		m_CharDataList.add(data);
	}

	inline void addUCharDataToList( const unsigned char& data )
	{
		m_UCharDataList.add(data);
	}

	inline void addShortDataToList( const short& data )
	{
		m_ShortDataList.add(data);
	}

	inline void addUShortDataToList( const unsigned short& data )
	{
		m_UShortDataList.add(data);
	}

	inline void addIntDataToList( const int& data )
	{
		m_IntDataList.add(data);
	}

	inline void addUIntDataToList( const unsigned int& data )
	{
		m_UIntDataList.add(data);
	}

	inline void addLongDataToList( const long& data )
	{
		m_LongDataList.add(data);
	}

	inline void addULongDataToList( const unsigned long& data )
	{
		m_ULongDataList.add(data);
	}

	inline void addFloatDataToList( const float& data )
	{
		m_FloatDataList.add(data);
	}

	inline void addDoubleDataToList( const double& data )
	{
		m_DoubleDataList.add(data);
	}

	inline void addInt8DataToList( const char& data ) { addCharDataToList(data); }

	inline void addUInt8DataToList( const unsigned char& data ) { addUCharDataToList(data); }

	inline void addInt16DataToList( const short& data ) { addShortDataToList(data); }

	inline void addUInt16DataToList( const unsigned short& data ) { addUShortDataToList(data); }

	inline void addInt32DataToList( const int& data ) { addIntDataToList(data); }

	inline void addUInt32DataToList( const unsigned int& data ) { addUIntDataToList(data); }

	inline void addInt64DataToList( const long& data ) { addLongDataToList(data); }

	inline void addUInt64DataToList( const unsigned long& data ) { addULongDataToList(data); }

	inline void addFloat32DataToList( const float& data ) { addFloatDataToList(data); }

	inline void addFloat64DataToList( const double& data ) { addDoubleDataToList(data); }

	inline char getCharDataFromList( const int& index ) const
	{
		return (m_CharDataList.hasIndex(index) ? m_CharDataList[index] : 0);
	}

	inline unsigned char getUCharDataFromList( const int& index ) const
	{
		return (m_UCharDataList.hasIndex(index) ? m_UCharDataList[index] : (unsigned)0);
	}

	inline short getShortDataFromList( const int& index ) const
	{
		return (m_ShortDataList.hasIndex(index) ? m_ShortDataList[index] : 0);
	}

	inline unsigned short getUShortDataFromList( const int& index ) const
	{
		return (m_UShortDataList.hasIndex(index) ? m_UShortDataList[index] : (unsigned)0);
	}

	inline int getIntDataFromList( const int& index ) const
	{
		return (m_IntDataList.hasIndex(index) ? m_IntDataList[index] : 0);
	}

	inline unsigned int getUIntDataFromList( const int& index ) const
	{
		return (m_UIntDataList.hasIndex(index) ? m_UIntDataList[index] : (unsigned)0);
	}

	inline long getLongDataFromList( const int& index ) const
	{
		return (m_LongDataList.hasIndex(index) ? m_LongDataList[index] : 0);
	}

	inline unsigned long getULongDataFromList( const int& index ) const
	{
		return (m_ULongDataList.hasIndex(index) ? m_ULongDataList[index] : (unsigned)0);
	}

	inline float getFloatDataFromList( const int& index ) const
	{
		return (m_FloatDataList.hasIndex(index) ? m_FloatDataList[index] : 0.0f);
	}

	inline double getDoubleDataFromList( const int& index ) const
	{
		return (m_DoubleDataList.hasIndex(index) ? m_DoubleDataList[index] : 0.0);
	}

	inline Arc_int8_t getInt8DataFromList( const int& index ) const { return getCharDataFromList(index); }

	inline Arc_uint8_t getUInt8DataFromList( const int& index ) const { return getUCharDataFromList(index); }

	inline Arc_int16_t getInt16DataFromList( const int& index ) const { return getShortDataFromList(index); }

	inline Arc_uint16_t getUInt16DataFromList( const int& index ) const { return getUShortDataFromList(index); }

	inline Arc_int32_t getInt32DataFromList( const int& index ) const { return getIntDataFromList(index); }

	inline Arc_uint32_t getUInt32DataFromList( const int& index ) const { return getUIntDataFromList(index); }

	inline Arc_int64_t getInt64DataFromList( const int& index ) const { return getLongDataFromList(index); }

	inline Arc_uint64_t getUInt64DataFromList( const int& index ) const { return getULongDataFromList(index); }

	inline float getFloat32DataFromList( const int& index ) const { return getFloatDataFromList(index); }

	inline double getFloat64DataFromList( const int& index ) const { return getDoubleDataFromList(index); }

	inline unsigned int getCharDataListSize( void ) const { return m_CharDataList.getSize(); }

	inline unsigned int getUCharDataListSize( void ) const { return m_UCharDataList.getSize(); }

	inline unsigned int getShortDataListSize( void ) const { return m_ShortDataList.getSize(); }

	inline unsigned int getUShortDataListSize( void ) const { return m_UShortDataList.getSize(); }

	inline unsigned int getIntDataListSize( void ) const { return m_IntDataList.getSize(); }

	inline unsigned int getUIntDataListSize( void ) const { return m_UIntDataList.getSize(); }

	inline unsigned int getLongDataListSize( void ) const { return m_LongDataList.getSize(); }

	inline unsigned int getULongDataListSize( void ) const { return m_ULongDataList.getSize(); }

	inline unsigned int getFloatDataListSize( void ) const { return m_FloatDataList.getSize(); }

	inline unsigned int getDoubleDataListSize( void ) const { return m_DoubleDataList.getSize(); }

	inline unsigned int getInt8DataListSize( void ) const { return getCharDataListSize(); }

	inline unsigned int getUInt8DataListSize( void ) const { return getUCharDataListSize(); }

	inline unsigned int getInt16DataListSize( void ) const { return getShortDataListSize(); }

	inline unsigned int getUInt16DataListSize( void ) const { return getUShortDataListSize(); }

	inline unsigned int getInt32DataListSize( void ) const { return getIntDataListSize(); }

	inline unsigned int getUInt32DataListSize( void ) const { return getUIntDataListSize(); }

	inline unsigned int getInt64DataListSize( void ) const { return getLongDataListSize(); }

	inline unsigned int getUInt64DataListSize( void ) const { return getULongDataListSize(); }

	inline unsigned int getFloat32DataListSize( void ) const { return getFloatDataListSize(); }

	inline unsigned int getFloat64DataListSize( void ) const { return getDoubleDataListSize(); }

private:

	inline PLYElement( void )
		: mp_Document(nullptr),
		  m_Type(),
		  m_CharData(),
		  m_UCharData(),
		  m_ShortData(),
		  m_UShortData(),
		  m_IntData(),
		  m_UIntData(),
		  m_LongData(),
		  m_ULongData(),
		  m_FloatData(),
		  m_DoubleData(),
		  m_CharDataList(),
		  m_UCharDataList(),
		  m_ShortDataList(),
		  m_UShortDataList(),
		  m_IntDataList(),
		  m_UIntDataList(),
		  m_LongDataList(),
		  m_ULongDataList(),
		  m_FloatDataList(),
		  m_DoubleDataList()
	{ }

	inline PLYElement( PLYDocument* pDocument )
		: mp_Document(pDocument),
		  m_Type(),
		  m_CharData(),
		  m_UCharData(),
		  m_ShortData(),
		  m_UShortData(),
		  m_IntData(),
		  m_UIntData(),
		  m_LongData(),
		  m_ULongData(),
		  m_FloatData(),
		  m_DoubleData(),
		  m_CharDataList(),
		  m_UCharDataList(),
		  m_ShortDataList(),
		  m_UShortDataList(),
		  m_IntDataList(),
		  m_UIntDataList(),
		  m_LongDataList(),
		  m_ULongDataList(),
		  m_FloatDataList(),
		  m_DoubleDataList()
	{ }

	void setDocument( PLYDocument* pDocument );

	PLYDocument* getDocument( void );

	PLYDocument* mp_Document;

	string m_Type;

	Map<string, char> m_CharData;

	Map<string, unsigned char> m_UCharData;

	Map<string, short> m_ShortData;

	Map<string, unsigned short> m_UShortData;

	Map<string, int> m_IntData;

	Map<string, unsigned int> m_UIntData;

	Map<string, long> m_LongData;

	Map<string, unsigned long> m_ULongData;

	Map<string, float> m_FloatData;

	Map<string, double> m_DoubleData;

	ArrayList<char> m_CharDataList;

	ArrayList<unsigned char> m_UCharDataList;

	ArrayList<short> m_ShortDataList;

	ArrayList<unsigned short> m_UShortDataList;

	ArrayList<int> m_IntDataList;

	ArrayList<unsigned int> m_UIntDataList;

	ArrayList<long> m_LongDataList;

	ArrayList<unsigned long> m_ULongDataList;

	ArrayList<float> m_FloatDataList;

	ArrayList<double> m_DoubleDataList;

};

} // namespace Arc

#endif // ARC_DATA_PLY_ELEMENT_H