#pragma once

#include <string>
#include <vector>

using namespace std;

#include "SDL.h"

#include "Math.h"

#include "Log.h"

class Core
{
public:
	//initilizes SDL, creates window, renderer, and pixel array
	void Init(int w, int h, string title);

	//closes SDL and frees memory
	void Quit();

	SDL_Window *GetWindow();

	SDL_Renderer *GetRenderer();

	//singleton getter
	static Core *GetInstance();

	//puts a single pixel at a passed X,Y
	void PutPixel(int x, int y, Uint32 color);

	//gets the pixel color of a passed X,Y screen coordinate
	Uint32 GetPixel(int x, int y);

	//gets screen information
	int GetWidth();

	int GetHeight();

	int GetTotalPixels();

	//clears screen buffers
	void ClearScreen();

	//swaps screen buffers
	void PresentScreen();

	//draws a line of a specified color in between passed X,Y points
	void DrawLine(int x1, int y1, int x2, int y2, Uint32 color);

	//draws a line of a specified color in between 2 points
	void DrawLine(Point p1, Point p2, Uint32 color);

	//flood fill specified color
	void Fill(int x, int y, Uint32 newColor);

private:
	//singleton
	static Core *instance;

	//SDL data structures
	SDL_Window *theWindow;
	SDL_Renderer *theRenderer;
	SDL_Surface *windowSurface;

	//streamed texture that has pixel array below imposed on it
	SDL_Texture *rasterTexture;

	//all the pixels on the screen for rendering
	//modified by set pixel
	Uint32 *PixelArray;

	//screen information
	int ScreenWidth;
	int ScreenHeight;

	int ScreenPixels;

protected:

	//default constructor for singleton
	Core();

};
