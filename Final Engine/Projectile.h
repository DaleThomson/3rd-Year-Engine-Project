#pragma once
#include "Entity.h"

class Projectile : public Entity
{
private:
	glm::vec3 position;
	GLfloat rotate = 0.0f;
public:
	Projectile() {}

	void init();
	void update();
	void draw(SDL_Window*);

	glm::vec3 getPosition();
	void setPosition(glm::vec3);
	void shoot();
	void stopShooting();
};

