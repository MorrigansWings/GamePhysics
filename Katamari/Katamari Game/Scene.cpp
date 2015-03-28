#include "Scene.h"

#include "GraphicsManager.h"
#include "Debug.h"
#include "RenderData.h"
#include "Entity.h"
#include "Skybox.h"
#include "Config.h"
#include "HeightMap.h"
#include <algorithm>

struct EntityDepthCmp
	: public std::binary_function<Entity*, Entity*, bool>
{
public:

	Camera* pCamera;

	inline bool operator()( const Entity* rhs, const Entity* lhs )
	{
		float rDepth = rhs->getDistanceFromCamera(pCamera);
		float lDepth = lhs->getDistanceFromCamera(pCamera);

		return (rDepth > lDepth);
	}

};

Scene::Scene(void)
  : m_Entities			(),
	m_Cameras			(),
	mp_RenderData		(nullptr),
	mp_CurrentCamera	(nullptr),
	mp_Skybox			(nullptr),
	m_ChangingView		(false),
	m_MoveSpeed			(2.0f),
	m_LookSpeed			(0.2f),
	m_ElapsedTime		(0.0f)
{
	mp_RenderData = New RenderData();
}

Scene::~Scene( void )
{
	delete mp_RenderData;
	delete mp_Skybox;

	for (auto it = m_Entities.itBegin(); it != m_Entities.itEnd(); ++it)
	{
		Entity* pEntity = it->second;
		delete pEntity;
	}
	m_Entities.clear();

	for (auto it = m_Cameras.itBegin(); it != m_Cameras.itEnd(); ++it)
	{
		Camera* pCamera = it->second;
		delete pCamera;
	}
	m_Cameras.clear();
}

void Scene::hookResize( int width, int height )
{
	for (auto it = m_Cameras.itBegin(); it != m_Cameras.itEnd(); ++it)
	{
		Camera* pCamera = it->second;

		pCamera->setAspect((GLfloat)width, (GLfloat)height);
	}
}

void Scene::hookKeyDown( int key )
{
	switch (key)
	{
	case GLFW_KEY_Z:

		if (Debug::GetBool("fly-through-mode"))
			mp_CurrentCamera->decreaseSpeed(1.0f);

		break;
	case GLFW_KEY_W:

		if ( ! Debug::GetBool("fly-through-mode") && mp_CurrentCamera)
			mp_CurrentCamera->moveForward(m_MoveSpeed * 0.1f);

		break;
	case GLFW_KEY_S:

		if ( ! Debug::GetBool("fly-through-mode") && mp_CurrentCamera)
			mp_CurrentCamera->moveBackward(m_MoveSpeed * 0.1f);

		break;
	case GLFW_KEY_A:

		if ( ! Debug::GetBool("fly-through-mode") && mp_CurrentCamera)
			mp_CurrentCamera->moveLeft(m_MoveSpeed * 0.1f);
		else
			mp_CurrentCamera->increaseSpeed(1.0f);

		break;
	case GLFW_KEY_D:

		if ( ! Debug::GetBool("fly-through-mode") && mp_CurrentCamera)
			mp_CurrentCamera->moveRight(m_MoveSpeed * 0.1f);

		break;
	case GLFW_KEY_F5:

		cycleCameras();

		break;
	case GLFW_KEY_F6:

		const vec3& pos = mp_CurrentCamera->getPos();
		const vec3& dir = mp_CurrentCamera->getDir();

		Log::InfoFmt(getClassName(), "Camera Data:\n  Pos: %2.2f %2.2f %2.2f\n  Dir: %2.2f %2.2f %2.2f",
										pos.x, pos.y, pos.z,
										dir.x, dir.y, dir.z);

		break;
	}
}

void Scene::hookKeyUp( int key )
{

}

void Scene::hookKeyHeld( int key )
{
	switch (key)
	{
	case GLFW_KEY_W:

		if ( ! Debug::GetBool("fly-through-mode") && mp_CurrentCamera)
			mp_CurrentCamera->moveForward();

		break;
	case GLFW_KEY_S:

		if ( ! Debug::GetBool("fly-through-mode") && mp_CurrentCamera)
			mp_CurrentCamera->moveBackward();

		break;
	case GLFW_KEY_A:

		if ( ! Debug::GetBool("fly-through-mode") && mp_CurrentCamera)
			mp_CurrentCamera->moveLeft();
		else
			mp_CurrentCamera->increaseSpeed(1.0f);

		break;
	case GLFW_KEY_Z:

		if (Debug::GetBool("fly-through-mode") && mp_CurrentCamera)
			mp_CurrentCamera->decreaseSpeed(1.0f);

		break;
	case GLFW_KEY_D:

		if ( ! Debug::GetBool("fly-through-mode") && mp_CurrentCamera)
			mp_CurrentCamera->moveRight();

		break;
	}
}

void Scene::hookMouseDown( int button )
{
	switch (button)
	{
	case 0: // Left

		m_ChangingView = true;

		break;
	case 1: // Right

		break;
	}
}

void Scene::hookMouseUp( int button )
{
	switch (button)
	{
	case 0: // Left

		m_ChangingView = false;

		break;
	case 1: // Right

		break;
	}
}

void Scene::hookMouseMoved( float x, float y )
{
	static float lastX = 0.0f, lastY = 0.0f;

	if (m_ChangingView && mp_CurrentCamera)
	{
		float dX = (lastX - x) * m_LookSpeed;
		float dY = (lastY - y) * m_LookSpeed;

		dX = glm::radians(dX);
		dY = glm::radians(dY);

		mp_CurrentCamera->changeYaw  (dX);
		mp_CurrentCamera->changePitch(dY);
	}

	lastX = x;
	lastY = y;
}

void Scene::hookMouseScrolled( float scrollX, float scrollY )
{

}

void Scene::loadSkybox( const string& filename )
{
	if ( ! mp_Skybox)
	{
		mp_Skybox = New Skybox(filename);
		return;
	}

	if ( ! mp_Skybox->load(filename))
	{
		delete mp_Skybox;
		mp_Skybox = nullptr;
	}
}

void Scene::addEntity( const string& name, Entity* pEntity )
{
	m_Entities.add(name, pEntity);
}

void Scene::addWater( const string& name, Water* pWater )
{
	m_Water.add(pWater);
}

void Scene::update( float deltaTime )
{
	m_ElapsedTime += deltaTime;

	if (mp_CurrentCamera && mp_Skybox)
	{
		vec3& camPos = mp_CurrentCamera->getPos();
		mp_Skybox->setPos(vec3(camPos.x, mp_Skybox->getPos().y, camPos.z));

		if (Debug::GetBool("fly-through-mode"))
		{
			mp_CurrentCamera->moveForward(mp_CurrentCamera->getSpeed() * 0.01f);
		}
	}

	EntityDepthCmp cmp;
	cmp.pCamera = mp_CurrentCamera;

	std::sort(m_Clouds.itBegin(), m_Clouds.itEnd(), cmp);
	std::sort(m_Foliage.itBegin(), m_Foliage.itEnd(), cmp);
}

void Scene::render( void )
{
	if ( ! mp_CurrentCamera)
		return;

	mat4x4 mView = mp_CurrentCamera->getViewMatrix();
	mat4x4 mProj = mp_CurrentCamera->getProjectionMatrix();
	mat4x4 mViewProj = mProj * mView;

	const GLfloat START_TIME_OFFSET = 28.0f;
	GLfloat secsInADay = Config::GetFloat("SecondsInADay");
	vec3 dayAmbient = Config::GetVec3("GlobalAmbient");

	vec3 globalLightDir = vec3(1.0f, 0.8f, -1.0f);
	globalLightDir = mat3x3(mView) * globalLightDir;
	mp_RenderData->pScene                = this;
	mp_RenderData->View					= mView;
	mp_RenderData->Proj					= mProj;
	mp_RenderData->ViewProj				= mViewProj;
	mp_RenderData->TimeOfDay			= ( sin(( START_TIME_OFFSET + m_ElapsedTime ) / secsInADay) + 1.0f ) * 0.5f;
	mp_RenderData->AmbientLightAmount   = dayAmbient;
	mp_RenderData->GlobalLightColor		= vec3(1.0f, 1.0f, 1.0f);
	mp_RenderData->GlobalLightDirection	= globalLightDir;
	mp_RenderData->ElapsedTime          = m_ElapsedTime;

	if (mp_Skybox)
		mp_Skybox->render(mp_RenderData);

	for (auto it = m_Entities.itBegin(); it != m_Entities.itEnd(); ++it)
	{
		Entity* pEntity = it->second;

		pEntity->render(mp_RenderData);
	}
}

void Scene::cycleCameras( void )
{
	if (m_Cameras.getSize() <= 1)
		return;

	const string& key = m_Cameras.getIndexOf(mp_CurrentCamera);
	auto it = m_Cameras.find(key);

	++it;

	if (it == m_Cameras.itEnd())
	{
		it = m_Cameras.itBegin();
	}

	mp_CurrentCamera = it->second;
}

void Scene::addCloud( Entity* pCloud )
{
	m_Clouds.add(pCloud);
}

void Scene::addShrub( Entity* pShrub )
{
	m_Foliage.add(pShrub);
}

HeightMap* Scene::getHeightMap()
{
	return mp_HeightMap;
}

void Scene::addHeightMap( const string& name, HeightMap* pEntity )
{
	mp_HeightMap = pEntity;
	m_Entities.add(name, (Entity*)pEntity);
}
