//=============================================================================
// d3dUtil.h by Frank Luna (C) 2005 All Rights Reserved.
//
// Contains various utility code for DirectX applications, such as, clean up
// and debugging code.
//
// Modified by Adi Bar-Lev, 2013
//=============================================================================

#ifndef D3DUTIL_H
#define D3DUTIL_H

// Enable extra D3D debugging in debug builds if using the debug DirectX runtime.  
// This makes D3D objects work well in the debugger watch window, but slows down 
// performance slightly.
#if defined(DEBUG) | defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <string>
#include <sstream>


//===============================================================
// Globals for convenient access.
class D3DApp;
extern D3DApp* gd3dApp;
extern IDirect3DDevice9* gd3dDevice;

//==============================================================================
// Singleton
//------------------------------------------------------------------------------
// Put the following declaration as first declaration within your class' h file
// Notice - no parameters should be passed in the constructor.
// Since this is a singleton, the constructor should be private /protected
#define DECLARE_SINGLETON(clsName)	\
    protected: \
        static clsName*     ms_instance; \
        clsName();  \
    \
    public: \
        static void DeleteInstance()  { \
            delete ms_instance; \
            ms_instance = NULL; \
        } \
        static clsName* GetInstance() { \
            if (!ms_instance) \
                ms_instance = new clsName; \
            return ms_instance; \
        } \
    protected:

// Put the following initilization at the top of your class source file
#define DEFINE_SINGLETON(clsName)  \
    clsName*    clsName::ms_instance = NULL;

//==============================================================================
// Clean up

#define ReleaseCOM(x) { if(x){ x->Release();x = 0; } }

//===============================================================
// Debug

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                      \
	{                                                  \
		HRESULT hr = x;                                \
		if(FAILED(hr))                                 \
		{                                              \
			DXTrace(__FILE__, __LINE__, hr, #x, TRUE); \
		}                                              \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) x;
	#endif
#endif 

#endif // D3DUTIL_H