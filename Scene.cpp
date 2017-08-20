#include "Scene.h"

//max number of objects per scene
const int MAX_OBJECTS = 10;

Scene::Scene()
{
	//resize array to max number of objects
	//so that way object references aren't broken by vector resizing
	CurrentObjects = 0;
	Objects.resize(MAX_OBJECTS);

}

void Scene::RenderScene()
{
	//total scene vertices and triangles
	vector<Vector3> TotalVerts;
	vector<Tri> TotalTris;

	//normals for all triangles in the scene
	vector<Vector3> Normals;

	//traverse through all the objects
	for (unsigned int x = 0; x < Objects.size(); x++)
	{
		//to be added to triangles so they stay with their meshes vertices
		int StartVerts = TotalVerts.size();
		//get the objects mesh info
		vector<Vector3> ObjectVerts = Objects[x].m.GetVerts();
		vector<Tri> ObjectTris = Objects[x].m.GetTris();

		//traverse through the vertices
		for (unsigned int v = 0; v < ObjectVerts.size(); v++)
		{
			//calculate their rotations if any
			if (Objects[x].Rotation.x != 0.0f)
			{
				ObjectVerts[v] = Math::RotatePoint(ObjectVerts[v], X, Objects[x].Rotation.x, Objects[x].m.GetCenter());
			}
			if (Objects[x].Rotation.y != 0.0f)
			{
				ObjectVerts[v] = Math::RotatePoint(ObjectVerts[v], Y, Objects[x].Rotation.y, Objects[x].m.GetCenter());
			}
			if (Objects[x].Rotation.z != 0.0f)
			{
				ObjectVerts[v] = Math::RotatePoint(ObjectVerts[v], Z, Objects[x].Rotation.z, Objects[x].m.GetCenter());
			}

			//translate them
			ObjectVerts[v].Add(Objects[x].Position);

			//scale them
			ObjectVerts[v].Multiply(Objects[x].Scale);

			//add transformed vertices to the total vertices array
			TotalVerts.push_back(ObjectVerts[v]);
		}

		//add all triangles to total triangle array
		for (unsigned int t = 0; t < ObjectTris.size(); t++)
		{
			TotalTris.push_back(ObjectTris[t]);
			//add starting vertices so they stay with their objects vertices
			TotalTris.back().v1 += StartVerts;
			TotalTris.back().v2 += StartVerts;
			TotalTris.back().v3 += StartVerts;
		}

	}

	//Z Sorting
	//very, very slow
	//puts framerate to less than 1 per second
	//could be improved with an implementation of the quick sort algorithm
	//commented out in order to maintain performance for testing

	/*
	int flag = -1;
	while (flag == -1)
	{
		flag = 0;
		for (unsigned int x = 0; x < TotalTris.size() - 1; x++)
		{
			if (TotalVerts[TotalTris[x].v1].z > TotalVerts[TotalTris[x + 1].v1].z)
			{

				Tri temp = TotalTris[x];
				TotalTris[x] = TotalTris[x + 1];
				TotalTris[x + 1] = temp;
				flag = -1;
			}
		}
	}
	*/


	//calculate face normal for every triangle
	for (unsigned int x = 0; x < TotalTris.size(); x++)
	{
		Vector3 normal;

		normal = Math::CalculateNormal(TotalVerts[TotalTris[x].v1], TotalVerts[TotalTris[x].v2], TotalVerts[TotalTris[x].v3]);
		//if it's not a back face add it to the array
		if (normal.z < 0)
		{
			Normals.push_back(normal);
		}
		//otherwise remove the triangle this normal is associated with
		else
		{
			TotalTris.erase(TotalTris.begin() + x);
		}
	}


	//clear screen
	Core::GetInstance()->ClearScreen();

	//create three points for each triangle
	Point p1, p2, p3;

	//for each triangle that's left after backface removal
	for (unsigned int x = 0; x < TotalTris.size(); x++)
	{

		//project them onto the screen
		p1 = Math::StrongProject(TotalVerts[TotalTris[x].v1], Core::GetInstance()->GetWidth(), Core::GetInstance()->GetHeight());
		p2 = Math::StrongProject(TotalVerts[TotalTris[x].v2], Core::GetInstance()->GetWidth(), Core::GetInstance()->GetHeight());
		p3 = Math::StrongProject(TotalVerts[TotalTris[x].v3], Core::GetInstance()->GetWidth(), Core::GetInstance()->GetHeight());


		//draw lines between them to create a wireframe
		Core::GetInstance()->DrawLine(p1, p2, 123456789);
		Core::GetInstance()->DrawLine(p2, p3, 123456789);
		Core::GetInstance()->DrawLine(p3, p1, 123456789);

	}

	//swap buffers
	Core::GetInstance()->PresentScreen();

}
//adds an object to the scene and returns its refernce
Object *Scene::AddObject(string meshFile, string name)
{
	//add one to current objects counter
	CurrentObjects += 1;
	//if we are less than max objects
	if (CurrentObjects < MAX_OBJECTS)
	{

		//create a new object that loads the mesh
		Object newObject = Object(meshFile);

		//assign name and index
		newObject.name = name;
		newObject.index = CurrentObjects - 1;
		
		//add to array
		Objects[CurrentObjects - 1] = newObject;

		//return reference
		return &Objects[CurrentObjects - 1];

	}

	//otherwise subtract from counter and return a null
	CurrentObjects -= 1;
	return nullptr;
}
//returns the reference to a game object by index
Object *Scene::GetObjectByIndex(int o)
{
	//if within the bounds
	if (o >= 0 && o < CurrentObjects)
	{
		//return refernce
		return &this->Objects[o];
	}
	//otherwise null
	return nullptr;
}