#pragma once

#include <fstream>
#include <vector>

using namespace std;

#include "SDL.h"

#include "Vector3.h"
#include "Math.h"
#include "Core.h"
#include "Log.h"

//triangle hold the 3 vert indexes that is in the meshes vert array
struct Tri {
	int v1, v2, v3;
};

//mesh that can be loaded from triangle based Wavefront OBJ files that do not have materials or predefined normals
//need to modify obj files heavily to use it
class Mesh {

public:

	//constructor
	Mesh();

	//load the mesh from a file
	void Load(string fileName);
	
	//get all the triangles
	vector<Tri> GetTris();
	//get all the vertices
	vector<Vector3> GetVerts();
	//get the center
	Vector3 GetCenter();
protected:

	//not translated verts
	vector<Vector3> Vertices;
	//tris
	vector<Tri> Triangles;

	//calculated center of the mesh
	Vector3 Center;

private:

};
