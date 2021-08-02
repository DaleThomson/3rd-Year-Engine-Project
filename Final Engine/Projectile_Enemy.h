#pragma once
#include "Entity.h"
#include "Projectile.h"

class Projectile_Enemy : public Entity
{
private:
	Projectile* projectile = new Projectile();
	glm::vec3 enemyPosition = glm::vec3(-3.0f, 0.1f, 45.0f);
	GLfloat enemyRotate = 0.0f;
	
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 minRange;
	glm::vec3 maxRange;
	bool flag = true, bulletActive = false;
	float velocity = 0.125f;
	
public:
	Projectile_Enemy() {}
	void init();
	void update();
	void draw(SDL_Window*);
	void setEnemyPosition(glm::vec3);
	void setMinRange(glm::vec3);
	void setMaxRange(glm::vec3);
	glm::vec3 getPosition();
	void setEnemyRotate(GLfloat);
	glm::vec3 getScale();
	void shoot();
	void stopShooting();
};

