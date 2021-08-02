#include "IntroductionLevel.h"

void IntroductionLevel::init()
{
	//SOUND EFFECT
	samples = new HSAMPLE[5];	//array of sound  files
	samples[0] = Sound::loadSample("../Resources/SoundFiles/rainforest.wav", BASS_SAMPLE_LOOP);	//adding sound files to the array to be played later in code

	Sound::playSample(samples[0]);

	//INITIALISING OBJECTS
	for (int i = 0; i < MAX_COLLECTABLES; i++)
	{
		collectable[i]->init();
	}

	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		platform[i]->init();
	}
	
	for (int i = 0; i < MAX_CHECKPOINTS; i++)
	{
		checkPoint[i]->init();
	}

	checkPoint[0]->setPosition(glm::vec3(-6.0f, 0.5f, 55.0f));
	checkPoint[1]->setPosition(glm::vec3(-6.0f, 0.5f, 150.0f));
	checkPoint[2]->setPosition(glm::vec3(-6.0f, 0.5f, 190.0f));

	endPoint->init();
	enemy->init();
	projectile_Enemy->init();
	player->init();

	//SETTING POSITIONS FOR OBJECTS
	endPoint->setPosition(glm::vec3(-6.0f, 1.0f, 230.0f));

	platform[0]->setPosition(glm::vec3(-6.0f, 2.0f, 40.0f));
	platform[1]->setPosition(glm::vec3(-6.0f, 4.0f, 45.0f));
	
	platform[2]->setPosition(glm::vec3(-6.0f, 2.0f, 70.0f));
	platform[3]->setPosition(glm::vec3(-6.0f, 4.0f, 75.0f));
	platform[4]->setPosition(glm::vec3(-6.0f, 6.0f, 80.0f));
	platform[5]->setPosition(glm::vec3(-6.0f, 8.0f, 85.0f));
	platform[6]->setPosition(glm::vec3(-6.0f, 10.0f, 90.0f));

	collectable[0]->setPosition(glm::vec3(-6.0f, 0.5f, 100.0f));
	collectable[1]->setPosition(glm::vec3(-6.0f, 0.5f, 105.0f));
	collectable[2]->setPosition(glm::vec3(-6.0f, 0.5f, 110.0f));

	enemy->setEnemyPosition(glm::vec3(-6.0f, 0.5f, 120.0f));
	enemy->setMinRange(glm::vec3(0.0f, 0.0f, 120.0f));
	enemy->setMaxRange(glm::vec3(0.0f, 0.0f, 140.0f));

	projectile_Enemy->setEnemyPosition(glm::vec3(-6.0f, 0.5f, 160.0f));
	projectile_Enemy->setMinRange(glm::vec3(0.0f, 0.0f, 160.0f));
	projectile_Enemy->setMaxRange(glm::vec3(0.0f, 0.0f, 180.0f));
}

void IntroductionLevel::update(AbstractLevel ** level)
{
	//RUNNING UPDATE LOOP FOR EACH OBJECT
	player->update();
	enemy->update();
	projectile_Enemy->update();
	

	//CHECKING COLLISION FOR COLLECTABLES
	for (int i = 0; i < MAX_COLLECTABLES; i++)
	{
		if (Collision::collisionDetection(player, collectable[i]))
		{
			player->addCollectable();
			collectable[i]->setPosition(glm::vec3(collectable[i]->getPosition().x,
				collectable[i]->getPosition().y, collectable[i]->getPosition().z + 1000.0f));
		}
	}

	//CHECKING COLLISION FOR PLATFORMS
	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		if (Collision::collisionDetection(player, platform[i]))
		{
			//if (player->getPosition().y > platform[i]->getPosition().y)
			//{
			player->setJump(false);
			player->setPlayerPosition(glm::vec3(player->getPosition().x, platform[i]->getPosition().y + 1.0f, player->getPosition().z));
			//}
		}
	}

	//CHECKING COLLISION FOR CHECKPOINTS
	for (int i = 0; i < MAX_CHECKPOINTS; i++)
	{
		if (Collision::collisionDetection(player, checkPoint[i]))
		{
			player->setCheckPoint(checkPoint[i]->getPosition());
		}
	}

	//CHECKING COLLISION FOR COLLECTABLES
	if (Collision::collisionDetection(player, enemy))
	{
		if (player->getAllowDamage())
		{
			player->setAllowDamage(false);
			player->takeDamage();
		}
	}


	if (player->getPosition().z == projectile_Enemy->getPosition().z - 5
		|| player->getPosition().z == projectile_Enemy->getPosition().z + 5)
	{
		projectile_Enemy->shoot();
	}


	if (Collision::collisionDetection(player, endPoint))
	{
		delete endPoint;
		delete* collectable;
		delete* platform;
		delete enemy;
		lUpdate->update(level);
	}
}

void IntroductionLevel::draw(SDL_Window * window)
{
	//DRAWING THE OBJECTS
	display->draw(window);
	player->draw(window);
	endPoint->draw(window);
	projectile_Enemy->draw(window);
	enemy->draw(window);

	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		platform[i]->draw(window);
	}

	for (int i = 0; i < MAX_CHECKPOINTS; i++)
	{
		checkPoint[i]->draw(window);
	}

	for (int i = 0; i < 5; i++)
	{
		collectable[i]->draw(window);
	}

	SDL_GL_SwapWindow(window);
}