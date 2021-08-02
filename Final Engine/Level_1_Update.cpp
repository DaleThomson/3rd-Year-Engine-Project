#include "Level_1_Update.h"

void Level_1_Update::update(AbstractLevel** level)
{
	AbstractLevel* l = *level;
	*level = new Level_2(player); // The double pointer is set to the next level.
	delete l;
}