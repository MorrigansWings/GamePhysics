//=============================================================================
//                          GraphicsManager.cpp
//
// Adopted from CubeDemo.cpp by Frank Luna (C) 2005 All Rights Reserved.
//
// Edited and changed by Adi Bar-Lev, 2013
// EGP-300-101 - Computer Graphics II, Spring 2013.
//
// This project creates a skeleton workspace and base classes for the student to be 
// able to start working with sample classes and develop evolve it according to the 
// given exercises
//
// Controls: Use mouse to orbit and zoom; use the 'W' and 'S' keys to 
//           alter the height of the camera.
//=============================================================================
#include "../Input/DirectInput.h"
#include <crtdbg.h>
#include "GfxStats.h"
#include <list>

#include "GraphicsManager.h"
#include "Vertex.h"

#include "3DClasses/BaseObject3D.h"
#include "3DClasses/ConeObject3D.h"
#include "3DClasses/CylinderObject3D.h"
#include "3DClasses/SphereObject3D.h"
#include "3DClasses/BoxObject3D.h"
#include "3DClasses/TorusObject3D.h"
#include "3DClasses/TeapotObject3D.h"

#include "Materials/PhongMaterial.h"
#include "Materials/NormalMaterial.h"
#include "Materials/NormalEnvironmentMaterial.h"
//=============================================================================

GraphicsManager::GraphicsManager(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP)
: D3DApp(hInstance, winCaption, devType, requestedVP)
{
	if(!checkDeviceCaps())
	{
		MessageBox(0, "checkDeviceCaps() Failed", 0, 0);
		PostQuitMessage(0);
	}

	mCameraRadius    = 10.0f;
	mCameraRotationX = -D3DX_PI * 0.5;//1.2;
	mCameraRotationY = 0.0f;

	mSwapObjectFlag = false;
	mTextureToggleFlag = false;
	mWireframeToggleFlag = false;
	mNormalToggleFlag = false;
	mEnvironmentToggleFlag = false;

	// set up vertex declarations
	InitAllVertexDeclarations();

	setupMaterials();

	onResetDevice();
}

GraphicsManager::~GraphicsManager()
{
    GfxStats::DeleteInstance();

	std::map<std::string, BaseObject3D*>::iterator objIter = m_Objects.begin();
	for (objIter = m_Objects.begin(); objIter != m_Objects.end(); objIter++)
	{
//		OutputDebugStringW(L"Erasing object from m_Objects using objIter\n");
		delete objIter->second;
	}

	m_Objects.clear();

	std::map<std::string, BaseMaterial*>::iterator matIter;
	for (matIter = m_Materials.begin(); matIter != m_Materials.end(); matIter++)
	{
		m_Materials.erase(matIter);
//		delete matIter->second;
	}

	m_Materials.clear();

	delete m_Material;

	DestroyAllVertexDeclarations();
}

bool GraphicsManager::checkDeviceCaps()
{
	return true;
}

void GraphicsManager::onLostDevice()
{
	GfxStats::GetInstance()->onLostDevice();
	m_Material->getEffect()->OnLostDevice();
}

void GraphicsManager::onResetDevice()
{
	GfxStats::GetInstance()->onResetDevice();
	m_Material->getEffect()->OnResetDevice();
	// The aspect ratio depends on the backbuffer dimensions, which can 
	// possibly change after a reset.  So rebuild the projection matrix.
	buildProjMtx();
	buildObjectMtx();
}

void GraphicsManager::updateScene(float dt)
{
	// Reset the statistics for the scene - each object will add to it.
	GfxStats::GetInstance()->setVertexCount(0);
	GfxStats::GetInstance()->setTriCount(0);
	GfxStats::GetInstance()->update(dt);

	// Get snapshot of input devices.
	gDInput->poll();

	// Camera Keyboard Controls
	if (gDInput->keyDown(DIK_W)) // forward
	{

	}
	else
	{
	}
	if (gDInput->keyDown(DIK_S)) // back
	{

	}
	else
	{
	}
	if (gDInput->keyDown(DIK_A)) // rotate left
	{

	}
	else
	{
	}
	if (gDInput->keyDown(DIK_D)) // rotate right
	{

	}
	else
	{
	}

	// Divide by 100 to make mouse less sensitive.
	mCameraRotationX -= gDInput->mouseDY() / 100.0f;
	mCameraRotationY -= gDInput->mouseDX() / 100.0f;
	mCameraRadius	 -= gDInput->mouseDZ() / 100.0f;

	// If we rotate over 360 degrees, just roll back to 0
	if( fabsf(mCameraRotationX) >= 2.0f * D3DX_PI ) 
		mCameraRotationX = 0.0f;
	if( fabsf(mCameraRotationY) >= 2.0f * D3DX_PI ) 
		mCameraRotationY = 0.0f;

	// Don't let radius get too small.
	if( mCameraRadius < 5.0f )
		mCameraRadius = 5.0f;

	// The camera position/orientation relative to world space can 
	// change every frame based on input, so we need to rebuild the
	// view matrix every frame with the latest changes.
	buildViewMtx();
	buildObjectMtx();
}

void GraphicsManager::drawScene()
{
	// Clear the backbuffer and depth buffer.
	HR(gd3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0));

	HR(gd3dDevice->BeginScene());

	// Iterate through and render all objects
	std::map<std::string, BaseObject3D*>::iterator objIter;
	for (objIter = m_Objects.begin(); objIter != m_Objects.end(); objIter++)
		objIter->second->Render(gd3dDevice, mView, mProj);

    // display the render statistics
    GfxStats::GetInstance()->display();

	HR(gd3dDevice->EndScene());

	// Present the backbuffer
	HR(gd3dDevice->Present(0, 0, 0, 0));
}

void GraphicsManager::buildViewMtx()
{
	D3DXMatrixIdentity(&mView);
	D3DXMatrixTranslation(&mView, 0, 0, mCameraRadius);
}

void GraphicsManager::buildObjectMtx()
{
	D3DXMATRIX rotationMatrix; 
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, mCameraRotationY, mCameraRotationX, 0);

	std::map<std::string, BaseObject3D*>::iterator objIter;
	for (objIter = m_Objects.begin(); objIter != m_Objects.end(); ++objIter)
		objIter->second->Rotate(rotationMatrix);
}

void GraphicsManager::buildProjMtx()
{
	float w = (float)md3dPP.BackBufferWidth;
	float h = (float)md3dPP.BackBufferHeight;
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI * 0.25f, w/h, 1.0f, 5000.0f);
}
/************************************ OBJECT FUNCTIONS **************************************/
bool GraphicsManager::createBox(std::string &modelName)
{
	return createBox(modelName, 1.0f, 1.0f, 1.0f);
}

bool GraphicsManager::createBox(std::string &modelName, float scale)
{
	return createBox(modelName, scale, scale, scale);
}

bool GraphicsManager::createBox(std::string &modelName, float width, float height, float depth)
{
	// If name doesn't exist in the map already, create new
	if (m_Objects.find(modelName) == m_Objects.end())
	{
		BoxObject3D* box = new BoxObject3D(width, height, depth);
		m_Objects[modelName] = box;
		m_Objects[modelName]->Create(gd3dDevice);
		m_Objects[modelName]->SetMaterial(m_Material);
		return true;
	}
	// Otherwise, return false - cannot create new object
	else return false;
}

/************************************ PRIVATE FUNCTIONS **************************************/

void GraphicsManager::setupMaterials()
{
	//-------------- setup Effects ---------------------
	ID3DXBuffer* errors = 0;
	D3DXCreateEffectFromFile(gd3dDevice, "Shaders/phong-normal-env.fx", 0, 0, D3DXSHADER_DEBUG, 0, &mEffectFile, &errors);
	if( errors )
	{
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);
	}

	// Initialize materials and assign effects

	m_Material = new NormalEnvironmentMaterial();
	//m_Material = new NormalMaterial();
	m_Material->ConnectToEffect(mEffectFile);
	m_Material->InitEffect( gd3dDevice );

	mCurrentMaterialNum = 0;
}
