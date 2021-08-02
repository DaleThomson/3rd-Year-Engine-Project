#pragma once
#include "AbstractLevelUpdate.h"
#include "Player.h"
#include "Level_3.h"
class Level_2_Update : public AbstractLevelUpdate
{
protected:
	Player* player;
public:
	Level_2_Update(Player* player) : player(player) {}
	void update(AbstractLevel** level);
};