#ifndef _QUAT_H_
#define _QUAT_H_

#pragma once

class Quat
{
public:
	float x, y, z, w;

	Quat()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{}

	Quat(int val)
		: x((float)val)
		, y((float)val)
		, z((float)val)
		, w((float)val)
	{}

	Quat(float val)
		: x(val)
		, y(val)
		, z(val)
		, w(val)
	{}

	Quat(int inX, int inY, int inZ, int inW)
		: x((float)inX)
		, y((float)inY)
		, z((float)inZ)
		, w((float)inW)
	{}

	Quat(float inX, float inY, float inZ, float inW)
		: x(inX)
		, y(inY)
		, z(inZ)
		, w(inW)
	{}

	Quat(const Quat &q)
		: x(q.x)
		, y(q.y)
		, z(q.z)
		, w(q.w)
	{}

};

#endif // _QUAT_H_