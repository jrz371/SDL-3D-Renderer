#pragma once

#include <math.h>

using namespace std;

#include "Vector3.h"

//2d screen point
struct Point {
	int x, y;
};

enum AXIS {
	X = 0,
	Y = 1,
	Z = 2
};

class Math
{
public:
	//rotate a point on a single axis based on a pased center and axis
	static Vector3 RotatePoint(Vector3 Point, AXIS Axis, float angle, Vector3 center);

	//weak projection
	static Point WeakProject(Vector3 v, int Width, int Height);

	//true perspective projection
	static Point StrongProject(Vector3 v, int Width, int Height);

	//returns handy math constants
	static float Pi();

	static float Degrees2Radians();

	static float Radians2Degrees();

	//cross product of two sides of a triangle returns the normal
	static Vector3 CalculateNormal(Vector3 v1, Vector3 v2, Vector3 v3);

};
