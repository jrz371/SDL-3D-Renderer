#include "Math.h"

//constants for math stuff
const float PI = 3.14159f;
const float Deg2Rad = 0.01745329f;
const float Rad2Deg = 57.2958f;

//rotate a point around a center vector 3 on a particular axis
Vector3 Math::RotatePoint(Vector3 Point, AXIS Axis, float angle, Vector3 center)
{
	//new locations
	float NewX, NewY, NewZ;
	//distance of point from center
	float Dist;
	//the angle between the center and point
	float AngleBetween;

	//bunch of trig
	switch (Axis)
	{
	case X:
		//get angle between
		AngleBetween = atan2f(Point.y - center.y, Point.z - center.z);

		//add new rotation
		AngleBetween += (angle * Deg2Rad);

		//get distance
		Dist = (float)sqrt((center.y - Point.y) * (center.y - Point.y) + (center.z - Point.z) * (center.z - Point.z));

		//update new points
		NewX = Point.x;
		NewY = (float)sin(AngleBetween) * Dist + center.y;
		NewZ = (float)cos(AngleBetween) * Dist + center.z;

		break;
		//same for all 3 just difference axis
	case Y:

		AngleBetween = atan2f(Point.x - center.x, Point.z - center.z);

		AngleBetween += (angle * Deg2Rad);

		Dist = (float)sqrt((center.x - Point.x) * (center.x - Point.x) + (center.z - Point.z) * (center.z - Point.z));

		NewX = (float)sin(AngleBetween) * Dist + center.x;
		NewY = Point.y;
		NewZ = (float)cos(AngleBetween) * Dist + center.z;

		break;
	case Z:

		AngleBetween = atan2f(Point.x - center.x, Point.y - center.y);

		AngleBetween += (angle * Deg2Rad);

		Dist = (float)sqrt((center.x - Point.x) * (center.x - Point.x) + (center.y - Point.y) * (center.y - Point.y));

		NewX = (float)sin(AngleBetween) * Dist + center.x;
		NewY = (float)cos(AngleBetween) * Dist + center.y;
		NewZ = Point.z;

		break;
	}
	//make the new floats into a vector and return them
	Vector3 newVector = Vector3(NewX, NewY, NewZ);

	return newVector;

}

//turns a 3d world point into a 2d screen point
//camera has a rotation that cant change of 0
//camera looks towards z+
Point Math::WeakProject(Vector3 v, int Width, int Height)
{
	//create 2d screen point
	Point p;
	p.x = -1;
	p.y = -1;

	//if the mesh is actually in the viewing area, z positive
	if (v.z > 0)
	{
		//weak projection
		//x,y and just divided by z
		//just scales mesh really
		//at a z distance of 2 mesh would appear at half size
		//all the other math is just flipping the screen on the y and moving origin to the middle of the screen
		float X = (v.x / v.z) * 0.5f * (float)Width;
		float Y = (v.y / v.z) * 0.5f * (float)Height;

		p.x = (int)(X + 0.5f * (float)Width);
		p.y = (int)(Y + 0.5f * (float)Height);

		p.y = Height - p.y;

	}
	//give back the 2d point
	return p;
}

//actual perspective calculations
Point Math::StrongProject(Vector3 v, int Width, int Height)
{
	//new sreen point
	Point p;

	//use floats for calculating to keep it as accurate as possible before casting as integers
	float NewX = 0.0f;
	float NewY = 0.0f;

	//actual projection calculation
	if (v.z > 0)
	{
		NewX = (1 / v.z) * v.x;
		NewY = (1 / v.z) * v.y;
	}

	//scale it to the screen size
	//screen is 2x2
	//upper left is -1,1,0
	//lower right is 1,-1,0
	NewX *= Width / 2;
	NewY *= Height / 2;

	//move it to be based on center
	NewX += (float)Width / 2;
	NewY += (float)Height / 2;

	//flip Y axis so going up the screen is + on the y axis
	NewY = (float)Height - NewY;
	
	//create and return point
	p.x = (int)NewX;
	p.y = (int)NewY;

	return p;
}
//returns constants from the top of this CPP file
float Math::Pi()
{
	return PI;
}

float Math::Degrees2Radians()
{
	return Deg2Rad;
}

float Math::Radians2Degrees()
{
	return Rad2Deg;
}
//cross product of two sides of a triangle returns the normal
Vector3 Math::CalculateNormal(Vector3 v1, Vector3 v2, Vector3 v3)
{
	Vector3 U;
	Vector3 V;

	U = v2;
	U.Subtract(v1);
	V = v3;
	V.Subtract(v1);

	Vector3 FaceNormal;

	FaceNormal.x = (U.y * V.z) - (U.z * V.y);
	FaceNormal.y = (U.z * V.x) - (U.x * V.z);
	FaceNormal.z = (U.x * V.y) - (U.y * V.x);

	return FaceNormal;
}