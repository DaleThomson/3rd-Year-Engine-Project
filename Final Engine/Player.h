#pragma once
#include "Entity.h"
#include "PlaySound.h"
#include "Collision.h"

class Player : public Entity
{
private:
	bool allowJumpSound = true, doJump = false, allowDamage = true;
	HSAMPLE *samples = NULL;
	int playerLives = 5;
	glm::vec3 playerPosition = glm::vec3(-3.0f, 0.1f, 0.0f);
	GLfloat playerRotate = 0.0f;
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 chekPointPos = playerPosition;
	int collectablesFound = 0;

public:
	Player() {}
	void init();
	void update();
	void draw(SDL_Window* window);
	void setPlayerPosition(glm::vec3);
	glm::vec3 getPosition();
	void setPlayerRotate(GLfloat);
	glm::vec3 getScale();
	void setJump(bool);
	void takeDamage();
	void setCheckPoint(glm::vec3);
	bool getAllowDamage();
	void setAllowDamage(bool);
	int getCollectablesFound();
	void addCollectable();
	bool noCollision = true;
};