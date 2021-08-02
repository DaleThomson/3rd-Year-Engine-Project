#pragma once
#include "Entity.h"

class Collectable : public Entity
{
private:
	glm::vec3 position = glm::vec3(4.0f, 1.0f, 4.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
public:
	Collectable() {}

	void init();
	void update();
	void draw(SDL_Window* window);
	
	glm::vec3 getPosition();
	glm::vec3 getScale();

	void setPosition(glm::vec3);
};

