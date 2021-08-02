#pragma once

#ifndef LOADTEXTURE
#define LOADTEXTURE

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>


namespace loadTexture {
	GLuint loadTextures(const char *fname);
	GLuint textToTexture(const char * str, GLuint textID, SDL_Color);
	void clearTextTexture(GLuint textID);
	GLuint loadCubeMap(const char *fname[6], GLuint *texID);
};
#endif