#include "Level_2_Update.h"

void Level_2_Update::update(AbstractLevel** level)
{
	AbstractLevel* l = *level;
	*level = new Level_3(player); // The double pointer is set to the next level.
	delete l; // The pointer is then deleted. 
}