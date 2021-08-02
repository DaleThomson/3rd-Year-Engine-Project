#pragma once
#include "AbstractDisplay.h"

// A concrete class for abstract display.
class IntroductionLevel_Display : public AbstractDisplay
{
private:
	SDL_Window* window;

public:
	IntroductionLevel_Display() {}
	void init();
	void draw(SDL_Window* window);
};