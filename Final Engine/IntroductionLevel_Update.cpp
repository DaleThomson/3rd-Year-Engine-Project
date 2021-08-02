#include "IntroductionLevel_Update.h"

void IntroductionLevel_Update::update(AbstractLevel** level)
{
	AbstractLevel* l = *level;
	*level = new Level_1(player); // The double pointer is set to the next level.
	delete l;
}
