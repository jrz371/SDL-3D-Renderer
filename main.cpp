#include "SDL.h"

using namespace std;

//includes core and scene
#include "Core.h"
#include "Scene.h"

//sdl event structure
SDL_Event theEvent;

//entry point to program
int main(int argc, char *args[])
{
	//initialize the core that creates a window
	Core::GetInstance()->Init(800, 600, "Raster");

	//program loop bool
	bool good = true;

	//create the scene
	Scene s = Scene();

	//add an object to it
	Object *TestObject = s.AddObject("Monkey.txt", "Monkey");
	Object *TestObject2 = s.AddObject("Monkey.txt", "Monkey2");

	//if the object is not a null reference, move it into the view
	if (TestObject != nullptr && TestObject2 != nullptr)
	{
		TestObject->Position.z = 5.0f;
		TestObject2->Position.z = 7.0f;
		TestObject2->Position.x = -5.0f;
	}
	//otherwise dont start the loop
	else
	{
		good = false;
	}
	
	//main loop
	while (good)
	{
		//update events
		SDL_PollEvent(&theEvent);

		//if we quit make the game loop end
		if (theEvent.type == SDL_QUIT)
		{
			good = false;
		}

		//slowly rotate the objects
		TestObject->Rotation.y += 0.5f;
		TestObject2->Rotation.y -= 0.5f;

		//render the scene
		s.RenderScene();

	} 

	//quit on exit
	Core::GetInstance()->Quit();

	return 0;
}