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

#ifndef ARC_CORE_BUFFER_H
#define ARC_CORE_BUFFER_H

#include <iostream>
#include <fstream>
#include <cstring>

#include "ManagedObject.h"

#include "ArrayList.h"

namespace Arc
{

class Buffer :
	public ManagedObject
{
public:

	inline Buffer( void )
		: m_Buffer(),
		  m_EndOfUsed(),
		  m_ReadIndex()
	{
		clear();
	}

	inline Buffer( const Buffer& other )
		: m_Buffer(other.m_Buffer),
		  m_EndOfUsed(other.m_EndOfUsed),
		  m_ReadIndex(other.m_ReadIndex)
	{ }

	Buffer( const char* buffer, unsigned int size );
	Buffer( const string& text );
	Buffer( std::istream& stream );

	virtual inline ~Buffer( void ) { clear(); }

	virtual inline string getClassName( void ) const { return "Arc Buffer"; }

	inline static Buffer LoadFromFile( const string& filename, const bool& binary = false )
	{
		std::ifstream file(filename, std::ios::in | (binary ? std::ios::binary : 0));
		Buffer buff(file);
		file.close();
		return buff;
	}

	inline void setDataFromBuffer( const Buffer& other ) { m_Buffer = other.m_Buffer; }
	bool setDataFromStream( std::istream& stream );
	void setDataFromBuffer( const char* buffer, unsigned int size );
	void setDataFromString( const string& text );
	void setDataFromStringWithLength( const string& text );

	void appendBuffer( const Buffer& other );
	bool appendDataFromStream( std::istream& stream );
	void appendBuffer( const char* buffer, unsigned int size );

	inline void appendString( const string& text )
	{
		appendBuffer(text.c_str(), text.size());
	}

	inline void appendStringWithLength( const string& text )
	{
		appendShort(text.size());
		appendBuffer(text.c_str(), text.size());
	}

	inline void appendBool( const bool& value )
	{
		appendBuffer((char*)&value, sizeof(bool));
	}

	inline void appendShort( const short& value )
	{
		appendBuffer((char*)&value, sizeof(short));
	}

	inline void appendInt( const int& value )
	{
		appendBuffer((char*)&value, sizeof(int));
	}

	inline void appendLong( const long& value )
	{
		appendBuffer((char*)&value, sizeof(long));
	}

	inline void appendChar( const char& value )
	{
		appendBuffer((char*)&value, sizeof(char));
	}

	inline void appendFloat( const float& value )
	{
		appendBuffer((char*)&value, sizeof(float));
	}

	inline void appendDouble( const double& value )
	{
		appendBuffer((char*)&value, sizeof(double));
	}

	string readNextString( unsigned int size );
	string readNextStringWithLength( void );
	string readNextLine( void );
	bool readNextBool( void );
	short readNextShort( void );
	int readNextInt( void );
	long readNextLong( void );
	char readNextChar( void );
	float readNextFloat( void );
	double readNextDouble( void );

	inline bool endOfBuffer( void ) { return (m_ReadIndex >= m_EndOfUsed); }

	string readStringAt( unsigned long offset, unsigned int size );
	string readStringWithLengthAt( unsigned long offset );
	string readLineAt( unsigned long offset );
	bool readBoolAt( unsigned long offset );
	short readShortAt( unsigned long offset );
	int readIntAt( unsigned long offset );
	long readLongAt( unsigned long offset );
	char readCharAt( unsigned long offset );
	float readFloatAt( unsigned long offset );
	double readDoubleAt( unsigned long offset );

	bool writeToStream( std::ostream& stream ) const;

	inline void setEndOfUsed( unsigned long index ) { m_EndOfUsed = Arc_Clamp(index, (unsigned long)0, (unsigned long)m_Buffer.getSize() - 1); }
	inline void setReadIndex( unsigned long index ) { m_ReadIndex = Arc_Clamp(index, (unsigned long)0, (unsigned long)m_Buffer.getSize() - 1); }

	inline unsigned long getReadIndex( void ) const { return m_ReadIndex; }

	inline void resetReadIndex( void ) { setReadIndex(0); }

	void clear( void );

	string getText( void ) const;
	Buffer& operator=( const string& text );

	void resize( long size );
	inline long getFullSize( void ) const { return m_Buffer.getSize() - 1; }
	inline long getUsedSize( void ) const { return m_EndOfUsed; }

	inline char* getRawBuffer( void ) { return (char*)&(m_Buffer[0]); }
	inline char* getRawBuffer( void ) const { return (char*)&(m_Buffer[0]); }

	friend inline std::ostream& operator<<( std::ostream& stream, const Buffer& buffer)
	{
		buffer.writeToStream(stream);
		return stream;
	}

	friend inline std::istream& operator>>( std::istream& stream, Buffer& buffer)
	{
		buffer.appendDataFromStream(stream);
		return stream;
	}

protected:

	// Memory Buffer to store data in
	ArrayList<char> m_Buffer;

	// End of used memory buffer
	unsigned long m_EndOfUsed;

	// Index for reading from the buffer
	unsigned long m_ReadIndex;

}; // class Buffer

} // namespace Arc

#endif // ARC_CORE_BUFFER_H
