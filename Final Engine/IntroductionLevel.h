#pragma once
#include "AbstractLevel.h"
#include "IntroductionLevel_Display.h"
#include "IntroductionLevel_Update.h"
#include "Player.h"
#include "Platform.h"
#include "Basic_Enemy.h"
#include "Projectile_Enemy.h"
#include "Collectable.h"
#include "EndPoint.h"

class IntroductionLevel : public AbstractLevel
{
private:
	HSAMPLE *samples = NULL;
	Player* player;
	Platform* platform[7];
	const int MAX_PLATFORMS = 7;
	const int MAX_CHECKPOINTS = 3;
	const int MAX_COLLECTABLES = 3;
	Collectable* collectable[3];
	Basic_Enemy* enemy;
	Projectile_Enemy* projectile_Enemy;
	EndPoint* endPoint;
	EndPoint* checkPoint[4];

public:
	IntroductionLevel(Player* player) : player(player)
	{
		display = new IntroductionLevel_Display();
		lUpdate = new IntroductionLevel_Update(player);
		endPoint = new EndPoint();
		projectile_Enemy = new Projectile_Enemy();
		enemy = new Basic_Enemy();

		for (int i = 0; i < MAX_PLATFORMS; i++)
		{
			platform[i] = new Platform();
		}

		for (int i = 0; i < MAX_COLLECTABLES; i++)
		{
			collectable[i] = new Collectable();
		}

		for (int i = 0; i < MAX_CHECKPOINTS; i++)
		{
			checkPoint[i] = new EndPoint();
		}

		display->init();
		init();
	}

	void init();
	void draw(SDL_Window* window);
	void update(AbstractLevel** level);
};

