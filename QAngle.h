#pragma once

class QAngle
{
public:
	float x, y, z;
	QAngle() : x(0), y(0), z(0) {}
	QAngle(float x, float y, float z) : x(x), y(y), z(z) {}
	QAngle(float x, float y) : x(x), y(y), z(0) {}
};