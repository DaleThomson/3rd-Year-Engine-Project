#pragma once
#include "SDL.h"
class AbstractLevel;

class AbstractLevelUpdate
{
public:
	virtual void update(AbstractLevel** level) = 0;
};
