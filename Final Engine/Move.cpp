#include "Move.h"

namespace Move
{
	//variables
	GLfloat r = 0.0f;
	float velocity = 1.0f;
	float gravity = -0.05f;

	void setGrav(float newGrav)
	{
		gravity = newGrav;
	}

	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d) {
		return glm::vec3(pos.x + d, pos.y, pos.z);
	}

	glm::vec3 moveRight(glm::vec3 pos, GLfloat angle, GLfloat d) {
		return glm::vec3(pos.x, pos.y, pos.z + d);
	}

	glm::vec3 grav(glm::vec3 pos) {
		return glm::vec3(pos.x, pos.y + gravity, pos.z);
	}

	float jump()
	{
		while (velocity >= -1.0f)
		{
			velocity += gravity;
			return velocity;
		}
		return velocity;
	}

	void resetV()
	{
		velocity = 1.0f;
	}

	const GLfloat getRotation()
	{
		return r;
	}
}