#pragma once
#include "Entity.h"

class Platform : public Entity
{
private:
	glm::vec3 position = glm::vec3(-6.0f, 2.0f, 0.0f);
	glm::vec3 position2 = glm::vec3(-6.0f, 2.1f, 5.0f);
	glm::vec3 position3 = glm::vec3(-6.0f, 0.1f, 0.0f);
	glm::vec3 position4 = glm::vec3(-6.0f, 0.1f, 0.0f);
	glm::vec3 position5 = glm::vec3(-6.0f, 0.1f, 0.0f);
	glm::vec3 position6 = glm::vec3(-6.0f, 0.1f, 0.0f);
	glm::vec3 position7 = glm::vec3(-6.0f, 0.1f, 0.0f);
	glm::vec3 position8 = glm::vec3(-6.0f, 0.1f, 0.0f);
	glm::vec3 position9 = glm::vec3(-6.0f, 0.1f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 0.5f, 1.0f);
public:
	Platform()
	{

	}

	void init();
	void update();
	void draw(SDL_Window* window);

	glm::vec3 getPosition();
	glm::vec3 getScale();

	void setPosition(glm::vec3);
	void setScale(glm::vec3);
};