#pragma once
#include "AbstractLevelUpdate.h"
#include "Player.h"
#include "Level_4.h"
class Level_3_Update : public AbstractLevelUpdate
{
protected:
	Player* player;
public:
	Level_3_Update(Player* player) : player(player) {}
	void update(AbstractLevel** level);
};