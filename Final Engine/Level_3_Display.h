#pragma once
#include "AbstractDisplay.h"

// A concrete class for abstract display.
class Level_3_Display : public AbstractDisplay
{
private:
	SDL_Window* window;

public:
	Level_3_Display() {}
	void init();
	void draw(SDL_Window* window);
};