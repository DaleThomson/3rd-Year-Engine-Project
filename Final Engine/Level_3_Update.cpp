#include "Level_3_Update.h"
void Level_3_Update::update(AbstractLevel** level)
{
	AbstractLevel* l = *level;
	*level = new Level_4(player); // The double pointer is set to the next level.
	delete l; // The pointer is then deleted. 
}