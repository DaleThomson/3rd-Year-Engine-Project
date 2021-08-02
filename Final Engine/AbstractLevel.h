#pragma once
#include "AbstractDisplay.h"
#include "AbstractLevelUpdate.h"
#include "Collision.h"
class AbstractLevel
{
protected:
	AbstractDisplay* display;
	AbstractLevelUpdate* lUpdate;
public:
	virtual ~AbstractLevel()
	{
		delete display;
		delete lUpdate;
	}

	virtual void init() = 0;
	virtual void draw(SDL_Window* window) = 0;
	virtual void update(AbstractLevel** level) = 0;
};