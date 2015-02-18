//=============================================================================
//                          GraphicsManager.h
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
#ifndef _GRAPHICS_MANAGER_H_
#define _GRAPHICS_MANAGER_H_
//=============================================================================
#pragma once
//=============================================================================
#include "d3dApp.h"

#include <vector>
#include <map>
//=============================================================================
class BaseObject3D;
class BaseMaterial;
//=============================================================================
class GraphicsManager : public D3DApp
{
public:
	GraphicsManager(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP);
	~GraphicsManager();

	bool checkDeviceCaps();
	void onLostDevice();
	void onResetDevice();
	void updateScene(float dt);
	void drawScene();

	// Helper methods
	void buildViewMtx();
	void buildProjMtx();
	void buildObjectMtx();

	// Model Creation Functions
	bool createBox(std::string &modelName);
	bool createBox(std::string &modelName, float scale);
	bool createBox(std::string &modelName, float width, float height, float depth);

private:
	float mCameraRotationX;
	float mCameraRotationY;
	float mCameraRadius;

	const float mCamMoveSpeed = 1.0f;
	const float mCamRotationSpeed = 1.0f;
	float mCameraPositionX;
	float mCameraPositionY;
	float mCameraPositionZ;

	D3DXMATRIX mView;
	D3DXMATRIX mProj;

	unsigned int mCurrentObjectNum;
	unsigned int mCurrentMaterialNum;

	bool mSwapObjectFlag;
	bool mTextureToggleFlag;
	bool mWireframeToggleFlag;
	bool mNormalToggleFlag;
	bool mEnvironmentToggleFlag;

	std::map<std::string, BaseObject3D*>	m_Objects;
	std::map<std::string, BaseMaterial*>	m_Materials;

	BaseMaterial* m_Material;

	ID3DXEffect* mEffectFile;
	//ID3DXEffect* mPhongFX;

	void setupMaterials();
};
//=============================================================================
#endif // _GRAPHICS_MANAGER_H__