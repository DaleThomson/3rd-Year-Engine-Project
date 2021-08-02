#pragma once
#include "AbstractLevel.h"
#include "Level_2_Display.h"
#include "Level_2_Update.h"
#include "Player.h"
#include "Platform.h"
#include "Basic_Enemy.h"
#include "Collectable.h"
#include "EndPoint.h"

class Level_2 : public AbstractLevel
{
protected:
	Player* player;
	Platform* platform[6];
	Collectable* collectable[6];
	Basic_Enemy* enemy[3];
	EndPoint* endPoint;

public:
	Level_2(Player* player) : player(player)
	{
		display = new Level_2_Display();
		lUpdate = new Level_2_Update(player);
		endPoint = new EndPoint();

		display->init();
		player->setPlayerPosition(glm::vec3(-3.0f, 0.1f, 0.0f));
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
		init();
	}

	void init();
	void draw(SDL_Window* window);
	void update(AbstractLevel** level);
};