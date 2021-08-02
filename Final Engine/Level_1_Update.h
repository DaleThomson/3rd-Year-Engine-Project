#pragma once
#include "AbstractLevelUpdate.h"
#include "Player.h"
#include "Level_2.h"

class Level_1_Update : public AbstractLevelUpdate
{
protected:
	Player* player;
public:
	Level_1_Update(Player* player) : player(player) {}
	void update(AbstractLevel** level);
};