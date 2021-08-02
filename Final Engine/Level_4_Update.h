#pragma once
#include "AbstractLevelUpdate.h"
#include "Player.h"
#include "Level_5.h"
class Level_4_Update : public AbstractLevelUpdate
{
protected:
	Player* player;
public:
	Level_4_Update(Player* player) : player(player) {}
	void update(AbstractLevel** level);
};