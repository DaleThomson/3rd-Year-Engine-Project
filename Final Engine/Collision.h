#pragma once
#ifndef COLLISION
#define COLLISION

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Entity.h"

namespace Collision
{
	bool collisionDetection(Entity*, Entity*);
	bool returnDetected();
};
#endif

