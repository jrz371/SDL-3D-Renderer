#pragma once

#include <iostream>
#include <string>

using namespace std;

#include "Math.h"
#include "Core.h"
#include "Object.h"
#include "Log.h"

class Scene
{
public:

	//default constructor that creates objects vector
	Scene();

	//all the rendering steps for the scene
	void RenderScene();

	//adds an object to the scene and returns the reference
	Object *AddObject(string meshFile, string name);

	//returns refernce of an object by passed index
	Object *GetObjectByIndex(int index);

private:
protected:

	//current objects in the scene
	int CurrentObjects;
	//vector that contains objects
	vector<Object> Objects;
};