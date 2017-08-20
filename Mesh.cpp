#include "Mesh.h"

//default vals
Mesh::Mesh()
{
	Center = Vector3();
}

void Mesh::Load(string fileName)
{
	//the file we load from
	fstream file;

	//converts string to char* fstream likes
	file.open(fileName.c_str());

	while (file.good())
	{

		string input;

		file >> input;
		//if file specifies next data is vertice
		if (input == "v")
		{
			//add vert
			Vector3 newVertex;

			file >> newVertex.x;
			file >> newVertex.y;
			file >> newVertex.z;

			Vertices.push_back(newVertex);
			Center.Add(newVertex);
		}
		//if file specifies next data is a face
		else if (input == "f")
		{
			//add face
			Tri newTri;

			file >> newTri.v1;
			file >> newTri.v2;
			file >> newTri.v3;

			newTri.v1 -= 1;
			newTri.v2 -= 1;
			newTri.v3 -= 1;

			Triangles.push_back(newTri);
		}
	}

	//divide center by total tris to find the center
	Center.Divide((float)Vertices.size());

	//send a log message of what we have done
	Log::SendMessage("Loaded Mesh: " + fileName, MESSAGE);

	//close the file to wrap up
	file.close();
}

vector<Tri> Mesh::GetTris()
{
	return Triangles;
}
vector<Vector3> Mesh::GetVerts()
{
	return Vertices;
}
Vector3 Mesh::GetCenter()
{
	return Center;
}