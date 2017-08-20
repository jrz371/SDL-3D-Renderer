#include "Object.h"

//default constructor that doesnt load a mesh
Object::Object()
{
	Position = Vector3();
	Rotation = Vector3();
	Scale = Vector3(1.0f, 1.0f, 1.0f);
}

//constructor that loads a mesh
Object::Object(string file)
{
	m.Load(file);
	Position = Vector3();
	Rotation = Vector3();
	Scale = Vector3(1.0f, 1.0f, 1.0f);
}