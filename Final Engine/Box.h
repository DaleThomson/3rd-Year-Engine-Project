#pragma once
#include "Entity.h"

class Box : public Entity
{
private:
	glm::vec3 position = glm::vec3(4.0f, 0.0f, 4.0f);
	glm::vec3 scale = glm::vec3(13.0f, 12.0f, 13.0f);
	GLuint texture;

public:
	Box(GLuint texture) : texture(texture) {}

	void init();
	void update();
	void draw(SDL_Window* window);

	glm::vec3 getPosition();
	glm::vec3 getScale();

	void setPosition(glm::vec3);
};

