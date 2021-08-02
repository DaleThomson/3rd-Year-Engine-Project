#pragma once
#include "AbstractLevel.h"
#include "Level_1_Display.h"
#include "Level_1_Update.h"
#include "Player.h"
#include "Platform.h"
#include "Basic_Enemy.h"
#include "Projectile_Enemy.h"
#include "Collectable.h"
#include "EndPoint.h"

class Level_1 : public AbstractLevel
{
protected:
	HSAMPLE *samples = NULL;
	Player* player;
	Platform* platform[6];
	Collectable* collectable[6];
	Basic_Enemy* enemy[3];
	Projectile_Enemy* proj_Enemy;
	EndPoint* endPoint;
	EndPoint* checkPoint[4];

public:
	Level_1(Player* player) : player(player)
	{
		display = new Level_1_Display();
		lUpdate = new Level_1_Update(player);
		endPoint = new EndPoint();
		proj_Enemy = new Projectile_Enemy();

		display->init();

		for (int i = 0; i < 5; i++)
		{
			platform[i] = new Platform();
		}
		for (int i = 0; i < 5; i++)
		{
			collectable[i] = new Collectable();
		}
		for (int i = 0; i < 2; i++)
		{
			enemy[i] = new Basic_Enemy();
		}
		for (int i = 0; i < 3; i++)
		{
			checkPoint[i] = new EndPoint();
		}
		init();
	}

	void init();
	void draw(SDL_Window* window);
	void update(AbstractLevel** level);
};