#pragma once

#include <string>

#include "Vector3.h"
#include "Mesh.h"

//objects for scenes
//they have a positions, rotations in euler angles, and scale
//they also have a mesh for component to be drawn
class Object
{
public:
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;

	Mesh m;

	//default constructor with no mesh
	Object();
	//constructor that has a mesh
	Object(string file);

	//index in the scenes array
	unsigned int index;

	//name of gameobject
	//planning to implement a find object by name for scene
	string name;

};
