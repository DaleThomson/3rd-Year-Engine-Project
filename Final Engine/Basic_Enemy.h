#pragma once
#include "Entity.h"

class Basic_Enemy : public Entity
{
private:
	glm::vec3 position = glm::vec3(-3.0f, 0.1f, 0.0f);
	GLfloat rotate = 0.0f;
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 minRange;
	glm::vec3 maxRange;
	bool flag = true;
	float velocity = 0.125f;

public:
	Basic_Enemy() {}
	void init();
	void update();
	void draw(SDL_Window*);
	void setEnemyPosition(glm::vec3);
	void setMinRange(glm::vec3);
	void setMaxRange(glm::vec3);
	glm::vec3 getPosition();
	void setEnemyRotate(GLfloat);
	glm::vec3 getScale();
};