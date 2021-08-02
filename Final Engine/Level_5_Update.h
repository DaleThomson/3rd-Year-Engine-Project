#pragma once
#include "AbstractLevelUpdate.h"
#include "Player.h"
class Level_5_Update : public AbstractLevelUpdate
{
protected:
	Player* player;
public:
	Level_5_Update(Player* player) : player(player) {}
	void update(AbstractLevel** level);
};