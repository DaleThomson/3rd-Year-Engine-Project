#include "Level_1.h"

void Level_1::init()
{
	samples = new HSAMPLE[5];	//array of sound  files
	samples[0] = Sound::loadSample("../Resources/SoundFiles/rainforest.wav", BASS_SAMPLE_LOOP);	//adding sound files to the array to be played later in code

	Sound::playSample(samples[0]);

	for (int i = 0; i < 5; i++)
	{
		collectable[i]->init();
	}
	for (int i = 0; i < 5; i++)
	{
		platform[i]->init();
	}
	for (int i = 0; i < 2; i++)
	{
		enemy[i]->init();
	}

	endPoint->init();
	endPoint->setPosition(glm::vec3(-6.0f, 1.0f, 70.0f));

	for (int i = 0; i < 3; i++)
	{
		checkPoint[i]->init();
	}

	proj_Enemy->init();

	platform[0]->setPosition(glm::vec3(-6.0f, 2.0f, 0.0f));
	platform[1]->setPosition(glm::vec3(-6.0f, 4.0f, 10.0f));
	platform[2]->setPosition(glm::vec3(-6.0f, 2.0f, 15.0f));
	platform[3]->setPosition(glm::vec3(-6.0f, 3.0f, 20.0f));
	platform[4]->setPosition(glm::vec3(-6.0f, 5.0f, 25.0f));

	collectable[0]->setPosition(glm::vec3(-6.0f, 0.5f, 30.0f));
	collectable[1]->setPosition(glm::vec3(-6.0f, 0.5f, 35.0f));
	collectable[2]->setPosition(glm::vec3(-6.0f, 0.5f, 40.0f));
	collectable[3]->setPosition(glm::vec3(-6.0f, 0.5f, 45.0f));
	collectable[4]->setPosition(glm::vec3(-6.0f, 0.5f, 50.0f));

	enemy[0]->setEnemyPosition(glm::vec3(-6.0f, 0.5f, 60.0f));
	enemy[1]->setEnemyPosition(glm::vec3(-6.0f, 0.5f, 70.0f));
	enemy[0]->setMinRange(glm::vec3(0.0f, 0.0f, 55.0f));
	enemy[0]->setMaxRange(glm::vec3(0.0f, 0.0f, 65.0f));
	enemy[1]->setMinRange(glm::vec3(0.0f, 0.0f, 65.0f));
	enemy[1]->setMaxRange(glm::vec3(0.0f, 0.0f, 75.0f));

	proj_Enemy->setMinRange(glm::vec3(0.0f, 0.0f, 45.0f));
	proj_Enemy->setMaxRange(glm::vec3(0.0f, 0.0f, 65.0f));

	checkPoint[0]->setPosition(glm::vec3(-6.0f, 0.5f, 10.0f));
	checkPoint[1]->setPosition(glm::vec3(-6.0f, 0.5f, 80.0f));
	checkPoint[2]->setPosition(glm::vec3(-6.0f, 0.5f, -10.0f));

	player->init();
}

void Level_1::update(AbstractLevel** level)
{
	for (int i = 0; i < 5; i++)
	{
		if (Collision::collisionDetection(player, collectable[i]))
		{
			player->addCollectable();
			collectable[i]->setPosition(glm::vec3(collectable[i]->getPosition().x,
				collectable[i]->getPosition().y, collectable[i]->getPosition().z + 1000.0f));
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (Collision::collisionDetection(player, platform[i]))
		{
			player->setJump(false);
			player->getPosition().y > platform[i]->getPosition().y;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (Collision::collisionDetection(player, enemy[i]))
		{
			if (player->getAllowDamage())
			{
				player->setAllowDamage(false);
				player->takeDamage();
			}
		}
	}

	proj_Enemy->update();
	player->update();

	for (int i = 0; i < 2; i++)
	{
		enemy[i]->update();
	}

	if (player->getPosition().z == proj_Enemy->getPosition().z - 5
		|| player->getPosition().z == proj_Enemy->getPosition().z + 5)
	{
		proj_Enemy->shoot();
	}


	for (int i = 0; i < 3; i++)
	{
		if (Collision::collisionDetection(player, checkPoint[i]))
		{
			player->setCheckPoint(checkPoint[i]->getPosition());
		}
	}
	
	if (Collision::collisionDetection(player, endPoint))
	{
		delete endPoint;
		delete* collectable;
		delete* platform;
		delete* enemy;
		lUpdate->update(level);
	}
}

void Level_1::draw(SDL_Window* window)
{
	display->draw(window);
	player->draw(window);
	endPoint->draw(window);
	proj_Enemy->draw(window);

	for (int i = 0; i < 2; i++)
	{
		enemy[i]->draw(window);
	}
	for (int i = 0; i < 5; i++)
	{
		collectable[i]->draw(window);
	}
	for (int i = 0; i < 5; i++)
	{
		platform[i]->draw(window);
	}
	for (int i = 0; i < 3; i++)
	{
		checkPoint[i]->draw(window);
	}

	SDL_GL_SwapWindow(window);
}