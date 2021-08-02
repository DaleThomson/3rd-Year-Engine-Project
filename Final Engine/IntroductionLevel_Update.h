#pragma once
#include "AbstractLevelUpdate.h"
#include "Player.h"
#include "Level_1.h"

class IntroductionLevel_Update : public AbstractLevelUpdate
{
protected:
	Player* player;

public:
	IntroductionLevel_Update(Player* player) : player(player) {}
	void update(AbstractLevel** level);
};

