#include "Level_4_Update.h"

void Level_4_Update::update(AbstractLevel** level)
{
	AbstractLevel* l = *level;
	*level = new Level_5(player); // The double pointer is set to the next level.
	delete l; // The pointer is then deleted. 
}