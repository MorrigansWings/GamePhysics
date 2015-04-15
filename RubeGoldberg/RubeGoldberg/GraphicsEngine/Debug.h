#ifndef GRAPHICS_II_DEBUG_H
#define GRAPHICS_II_DEBUG_H

#include <Arc/ManagedObject.h>

#include <Arc/Map.h>

using namespace Arc;

class Debug :
	public ManagedObject
{
public:

	inline static bool HasBool( const string& name ) { return m_BoolConfig.containsKey(name); }

	inline static void SetBool( const string& name, const bool& value ) { (HasBool(name) ? m_BoolConfig[name] = value : m_BoolConfig.add(name, value)); }

	inline static void ToggleBool( const string& name ) { if (HasBool(name)) { m_BoolConfig[name] = ! m_BoolConfig[name]; } }

	inline static bool GetBool( const string& name ) { return (HasBool(name) ? m_BoolConfig[name] : false); }

private:

	static Map<string, bool> m_BoolConfig;

};

#endif // GRAPHICS_II_DEBUG_H