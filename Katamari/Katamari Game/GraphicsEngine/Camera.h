#ifndef GRAPHICS_II_CAMERA_H
#define GRAPHICS_II_CAMERA_H

#include <Arc/ManagedObject.h>

#include "OpenGL.h"

#define _USE_MATH_DEFINES
#include <cmath>

using namespace glm;
using namespace Arc;

class Camera :
	public ManagedObject
{
public:

	inline Camera( const GLfloat& width, const GLfloat& height, const vec3& pos, const vec3& dir, const vec3& up, const GLfloat& fov, const GLfloat& vNear, const GLfloat& vFar, const GLfloat& speed )
		: m_ProjUpdated		(true),
		  m_InitialPos		(pos),
		  m_InitialUp		(up),
		  m_InitialDir      (dir),
		  m_InitialFOV		(fov),
		  m_InitialNear		(vNear),
		  m_InitialFar		(vFar),
		  m_InitialSpeed	(speed),
		  m_Orient			(1, 0, 0, 0)
	{
		reset(width, height);
		getViewMatrix();
	}

	virtual inline ~Camera( void ) { }

	virtual inline string getClassName( void ) const { return "Camera"; }

	void reset( GLfloat width, GLfloat height );
	inline void reset( void ) { reset(m_AspectWidth, m_AspectHeight); }

	inline vec3 getPos( void ) const      { return m_Pos; }
	inline void setPos( const vec3& pos ) { setPos(pos.x, pos.y, pos.z); }
	inline void setPos( const GLfloat& x, const GLfloat& y, const GLfloat& z )
	{ 
		m_Pos.x = x;
		m_Pos.y = y; 
		m_Pos.z = z;
	}

	inline vec3 getDir( void ) const	  { return m_Dir; }
	inline void setDir( const vec3& dir ) { setDir(dir.x, dir.y, dir.z); }
	void setDir( const GLfloat& x, const GLfloat& y, const GLfloat& z );

	inline vec3 getUp( void ) const     { return m_Up; }
	inline void setUp( const vec3& up ) { setUp(up.x, up.y, up.z); }
	inline void setUp( const GLfloat& x, const GLfloat& y, const GLfloat& z ) 
	{ 
		m_Up.x = x; 
		m_Up.y = y;
		m_Up.z = z;
	}

	inline vec3 getLeft( void )  { return cross(m_Up, getDir()); }
	inline vec3 getRight( void ) { return cross(getDir(), m_Up); }

	inline GLfloat getFOV( void ) const { return m_FOV; }
	inline void setFOV( const GLfloat& fov )
	{ 
		m_FOV = fov;
		m_ProjUpdated = true;
	}

	inline void setAspect( const GLfloat& width, const GLfloat& height ) 
	{ 
		m_AspectWidth = width;
		m_AspectHeight = height;
		m_ProjUpdated = true; 
	}

	void changePitch( const GLfloat& amount );
	void changeYaw( const GLfloat& amount );
	void rotate( const GLfloat& amount, const vec3& axis );

	inline GLfloat getSpeed( void ) const { return m_Speed; }
	inline void setSpeed( const GLfloat& speed ) { m_Speed = speed; }
	inline void increaseSpeed( const GLfloat& amount ) { m_Speed += amount; }
	inline void decreaseSpeed( const GLfloat& amount ) { m_Speed -= amount; }

	void setPerspective( const GLfloat& fov, const GLfloat& width, const GLfloat& height, const GLfloat& vNear, const GLfloat& vFar );

	mat4x4 getViewMatrix( void );
	mat4x4 getProjectionMatrix( void );

	void moveForward ( const GLfloat& amount );
	void moveBackward( const GLfloat& amount );
	void moveLeft    ( const GLfloat& amount );
	void moveRight   ( const GLfloat& amount );

	inline void moveForward ( void ) { moveForward(m_Speed); }
	inline void moveBackward( void ) { moveBackward(m_Speed); }
	inline void moveLeft    ( void ) { moveLeft(m_Speed); }
	inline void moveRight   ( void ) { moveRight(m_Speed); }

private:

	bool			m_ProjUpdated;

	GLfloat			m_FOV,
					m_AspectWidth, 
					m_AspectHeight,
					m_Near,
					m_Far,
					m_Pitch,
					m_Yaw,
					m_Speed,
					m_InitialFOV,
					m_InitialNear,
					m_InitialFar,
					m_InitialSpeed;

	mat4x4			m_View, 
					m_Proj;

	vec3			m_Pos,
					m_Dir,
					m_Up,
					m_LookAt,
					m_PosDelta,
					m_InitialPos,
					m_InitialDir,
					m_InitialUp;

	quat			m_Orient;

};

#endif // GRAPHICS_II_CAMERA_H