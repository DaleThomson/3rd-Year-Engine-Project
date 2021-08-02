#pragma once

#ifndef MOVE
#define MOVE
#define DEG_TO_RADIAN 0.017453293
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Move
{
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 moveRight(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 grav(glm::vec3 pos);
	const GLfloat getRotation();
	void setGrav(float);
	float jump();
	void resetV();
};
#endif