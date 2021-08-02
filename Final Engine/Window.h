#pragma once
#include "AbstractWindow.h"
class Window : public AbstractWindow
{
public:
	Window(int width, int height, const char* name)
	{
		height2 = height;
		width2 = width;
		windowName = name;
	}

	virtual ~Window() {}

	SDL_Window* setupRC(SDL_GLContext &context);
	SDL_Window* getWindow();

};