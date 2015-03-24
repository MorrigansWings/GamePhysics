#ifndef GRAPHICS_II_RESOURCE_LOADER_3DS_H
#define GRAPHICS_II_RESOURCE_LOADER_3DS_H

#include "ResourceLoader.h"

#include <Arc/Types.h>
#include <Arc/Buffer.h>

class Chunk3DS
	: ManagedObject
{
public:

	inline Chunk3DS( const unsigned long& start, Buffer& buff, const string& filename )
	{
		load(start, buff, filename);
	}

	virtual inline string getClassName( void ) const { return "Chunk 3DS"; }

	static inline unsigned char ReadChar( Buffer& buff, const unsigned long& offset )
	{
		return (unsigned)buff.readCharAt(offset);
	}

	static inline unsigned int ReadInt ( Buffer& buff, const unsigned long& offset )
	{
		unsigned int temp = ReadChar(buff, offset);
		return (temp | (ReadChar(buff, offset + 1) << 8));
	}

	static inline unsigned long ReadLong( Buffer& buff, const unsigned long& offset )
	{
		unsigned long temp1 = ReadInt(buff, offset);
		unsigned long temp2 = ReadInt(buff, offset + 2);
		return (temp1 | (temp2 << 16));
	}

	static inline float ReadFloat( Buffer& buff, const unsigned long& offset )
	{
		return buff.readFloatAt(offset);
	}

	static inline string ReadString( Buffer& buff, unsigned int startOffset, const int& maxLen )
	{
		string tmp;
		char ch = '\0';
		int ind = 0;
		do 
		{
			ch = ReadChar(buff, startOffset + ind);
			tmp += ch;
			ind++;
		} 
		while (ch != '\0' && (ind == -1 || ind < maxLen));

		return tmp;
	}

	inline unsigned int getID( void ) const { return m_ID; }
	inline void setID( unsigned int val ) { m_ID = val; }

	inline unsigned long getLength( void ) const { return m_Length; }
	inline void setLength( unsigned long val ) { m_Length = val; }

	inline unsigned long getStartOffset( void ) const { return m_StartOffset; }
	inline void setStartOffset( unsigned long val ) { m_StartOffset = val; }

private:

	void load( const unsigned long& start, Buffer& buff, const string& filename );
	void loadChildren( const unsigned long& start, Buffer& buff, const string& filename );

	unsigned int loadMaterialChunk( const unsigned long& start, Buffer& buff );

	unsigned int m_ID;

	unsigned long m_Length;

	unsigned long m_StartOffset;

	ArrayList<Chunk3DS> m_Children;

};

class ResourceLoader3DS :
	public ResourceLoader
{
public:

	inline ResourceLoader3DS( void ) { }
	virtual inline ~ResourceLoader3DS( void ) { }

	virtual inline string getClassName( void ) const { return "Resource Loader 3DS"; }

	virtual bool loadFromFile( const string& filename );

protected:

};

#endif // GRAPHICS_II_RESOURCE_LOADER_3DS_H