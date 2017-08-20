#include "Vector3.h"

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float nX, float nY, float nZ)
{
	x = nX;
	y = nY;
	z = nZ;
}

void Vector3::Scale(float num)
{
	x *= num;
	y *= num;
	z *= num;
}

void Vector3::Add(float num)
{
	x += num;
	y += num;
	z += num;
}

void Vector3::Add(Vector3 v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vector3::Divide(float num)
{
	x /= num;
	y /= num;
	z /= num;
}

void Vector3::Subtract(Vector3 v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

void Vector3::Multiply(Vector3 v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
}
//3d distance formula
float Vector3::Distance(Vector3 v1, Vector3 v2)
{
	return (float)sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z));
}