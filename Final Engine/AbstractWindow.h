#pragma once
#include "SDL.h"
#include <iostream>

using namespace std;

class AbstractWindow
{
public:
	SDL_Window* window;
	int height2;
	int width2;
	const char* windowName;
	virtual SDL_Window* setupRC(SDL_GLContext &context) = 0;
	virtual SDL_Window* getWindow() = 0;
};