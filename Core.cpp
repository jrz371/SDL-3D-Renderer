#include "Core.h"

//set the instance to zero so only one is created in getinstance
Core *Core::instance = 0;

void Core::Init(int w, int h, string title)
{

	Log::Init();

	//set private values
	ScreenWidth = w;
	ScreenHeight = h;
	ScreenPixels = w * h;

	//create our pixel array
	PixelArray = new Uint32[ScreenPixels];

	//init sdl
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		Log::SendMessage(SDL_GetError(), ERROR);
	}
	else
	{
		Log::SendMessage("SDL Initialized Correctly", MESSAGE);
	}

	//create window and get window surface
	theWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);

	if (theWindow == NULL)
	{
		Log::SendMessage(SDL_GetError(), ERROR);
	}
	else
	{
		Log::SendMessage("SDL Created Window Correctly", MESSAGE);
	}

	windowSurface = SDL_GetWindowSurface(theWindow);

	//create render so we can draw
	theRenderer = SDL_CreateRenderer(theWindow, NULL, SDL_RENDERER_ACCELERATED);

	if (theRenderer == NULL)
	{
		Log::SendMessage(SDL_GetError(), ERROR);
	}
	else
	{
		Log::SendMessage("SDL Created Renderer Correctly", MESSAGE);
	}

}

void Core::Quit()
{

	//delete allocated memory
	delete PixelArray;

	//destroy renderer
	SDL_DestroyRenderer(theRenderer);

	Log::SendMessage("Destroyed Renderer", MESSAGE);

	//destroy window surface
	SDL_FreeSurface(windowSurface);

	//destroy window
	SDL_DestroyWindow(theWindow);

	Log::SendMessage("Destroyed Window", MESSAGE);

	//quit
	SDL_Quit();

	Log::SendMessage("Quit SDL", MESSAGE);

	Log::Close();

}

SDL_Window *Core::GetWindow()
{
	return theWindow;
}

SDL_Renderer *Core::GetRenderer()
{
	return theRenderer;
}

//returns singleton
Core *Core::GetInstance()
{
	if (instance == 0)
	{
		instance = new Core();
	}
	
	return instance;

}

//puts a passed color pixel at an x,y point
void Core::PutPixel(int x, int y, Uint32 color)
{
	int Point = y * ScreenWidth + x;

	if (Point >= 0 && Point < ScreenPixels)
	{
		PixelArray[Point] = color;
	}
}

//returns the color at a x,y point
Uint32 Core::GetPixel(int x, int y)
{
	int Point = y * ScreenWidth + x;

	if (Point >= 0 && Point < ScreenPixels)
	{
		return PixelArray[Point];
	}

	return 0;

}

int Core::GetWidth()
{
	return ScreenWidth;
}

int Core::GetHeight()
{
	return ScreenHeight;
}

int Core::GetTotalPixels()
{
	return ScreenPixels;
}

//clears the SDL render and pixel array
void Core::ClearScreen()
{
	//clear pizel array
	for (int x = 0; x < ScreenPixels; x++)
	{
		PixelArray[x] = 0;
	}

	//clear renderer
	SDL_RenderClear(theRenderer);

}

void Core::PresentScreen()
{
	//create raster texture
	rasterTexture = SDL_CreateTexture(theRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, ScreenWidth, ScreenHeight);

	//update the texture with the pixel array edited with PutPixel
	SDL_UpdateTexture(rasterTexture, NULL, PixelArray, ScreenWidth * sizeof(Uint32));

	//draw raster texture
	SDL_RenderCopy(theRenderer, rasterTexture, NULL, NULL);

	//flip buffers
	SDL_RenderPresent(theRenderer);

	//destroy the texture to prevent memory leak
	SDL_DestroyTexture(rasterTexture);
}

Core::Core()
{
	ScreenWidth = -1;
	ScreenHeight = -1;
	ScreenPixels = -1;
}

//mybresenhams line drawing algorithm implementation
//using floating point vars for error even though integer math could work and be marginally faster
void Core::DrawLine(int x1, int y1, int x2, int y2, Uint32 color)
{

	int deltaX = x2 - x1;
	int deltaY = y2 - y1;

	//handles straight up and down lines
	if (deltaX == 0)
	{

		int yStart;

		if (y2 < y1)
		{
			yStart = y2;
		}
		else
		{
			yStart = y1;
		}

		for (int y = yStart; y < yStart + abs(deltaY); y++)
		{
			PutPixel(x1, y, color);
		}
		return;

	}

	//switches the direction we draw the line in
	int xStep = 1;
	int yStep = 1;

	if (x2 < x1)
	{
		xStep = -1;
	}

	if (y2 < y1)
	{
		yStep = -1;
	}

	//start points for the line drawing
	int xSpot = x1;
	int ySpot = y1;

	//error used to increase pixels on the non stepping axis
	float error;

	//traverse through the steps and draw the line
	if (abs(deltaX) > abs(deltaY))
	{

		float deltaError = abs((float)((float)deltaY / (float)deltaX));

		error = deltaError - 0.5f;

		for (int x = 0; x < abs(deltaX); x++)
		{

			PutPixel(xSpot, ySpot, color);
			xSpot += xStep;

			error += deltaError;

			if (error > 0.5f)
			{
				ySpot += yStep;
				error -= 1.0f;
			}

			if (xSpot < 0 || ySpot < 0 || xSpot > GetWidth() || ySpot > GetHeight())
			{
				return;
			}

		}
	}
	//same as above except Y axis is the primary stepping axis
	else
	{

		float deltaError = abs((float)((float)deltaX / (float)deltaY));

		error = deltaError - 0.5f;

		for (int x = 0; x < abs(deltaY); x++)
		{

			PutPixel(xSpot, ySpot, color);
			ySpot += yStep;

			error += deltaError;

			if (error > 0.5f)
			{
				xSpot += xStep;
				error -= 1.0f;
			}

			if (xSpot < 0 || ySpot < 0 || xSpot > GetWidth() || ySpot > GetHeight())
			{
				return;
			}

		}
	}

}

//draw line overload to use points instead pof raw x,y coordinates
void Core::DrawLine(Point p1, Point p2, Uint32 color)
{
	DrawLine(p1.x, p1.y, p2.x, p2.y, color);
}

//flood fill algorithm
void Core::Fill(int x, int y, Uint32 newColor)
{
	//get the first color
	Uint32 startColor = Core::GetInstance()->GetPixel(x, y);

	//all the pixels to be changed
	vector<Point> Points;

	//add first value
	Points.push_back(Point() = { x,y });

	//while there are pixels in the array to be filled
	while (Points.size() > 0)
	{
		//get the most recent point
		Point p = Points.back();

		//remove it
		Points.pop_back();

		//if the pixel needs to be filled
		if (p.x >= 0 && p.y >= 0 && p.x < Core::GetInstance()->GetWidth() && p.y < Core::GetInstance()->GetHeight() && Core::GetInstance()->GetPixel(p.x, p.y) == startColor)
		{
			//put the pixel
			PutPixel(p.x, p.y, newColor);

			//add the pixels around it to be filled
			Points.push_back(Point() = { p.x + 1,p.y });
			Points.push_back(Point() = { p.x,p.y + 1 });
			Points.push_back(Point() = { p.x - 1,p.y });
			Points.push_back(Point() = { p.x,p.y - 1 });

		}

	}

}