#pragma once
#include "AbstractDisplay.h"

// A concrete class for abstract display.
class Level_1_Display : public AbstractDisplay
{
public:
	Level_1_Display() {}
	void init();
	void draw(SDL_Window* window);
};