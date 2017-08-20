#pragma once

//math for sqrt in distance function
#include <math.h>

class Vector3 {
public:
	float x, y, z;

	//constructors
	Vector3();
	Vector3(float nX, float nY, float nZ);

	//multiply all parts of the vector by a scalar value
	void Scale(float num);

	//add a scalar value to all parts of the vector
	void Add(float num);

	//add another vector to this vector
	void Add(Vector3 v);

	//divides the vector by a scalar value
	void Divide(float num);

	//subtract a vector from this vector
	void Subtract(Vector3 v);

	//multiply two vectors together
	void Multiply(Vector3 v);

	//returns the distance between two vectors acting as points
	static float Distance(Vector3 v1, Vector3 v2);

};
