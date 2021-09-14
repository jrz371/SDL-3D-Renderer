# SDL-3D-Renderer
Utilizes SDL2 to create a wire frame 3D renderer

In order to compile include and link SDL 2

entry point of program is in main.cpp

Monkey.txt is a Wavefront OBJ of the monkey head created in Blender loaded into the program, Debug.txt is opened and modified by the Log class

To render your own blender files, make sure that you do the following steps

1. Add `Triangulate` modifier to all the objects in your blender
2. Export the model in OBJ format
3. Parse the faces using the `parser.py` file as follows

`parser.py <your model obj file> <new name for your parsed obj file>`

4. To render it, run `./main <parsed obj file name>`