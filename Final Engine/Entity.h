#pragma once
#include <SDL.h>
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include "SDL_ttf.h"
#include "loadTexture.h"
#include "Camera.h"
#include "Move.h"
#include "md2model.h"
using namespace std;

class Entity
{
protected:
	GLuint meshIndexCount[2];
	GLuint md2VertCount = 0;
	GLuint meshObjects[3];

	GLuint textureProgram;
	GLuint shaderProgram;
	GLuint skyboxProgram;

	vector<GLfloat> verts;
	vector<GLfloat> norms;
	vector<GLfloat> tex_coords;
	vector<GLuint> indices;

	GLfloat r = 0.0f;

	stack<glm::mat4> mvStack;

	// TEXTURE STUFF
	GLuint textures[3];
	GLuint skybox[5];
	GLuint labels[5];

	md2model tmpModel;

	rt3d::lightStruct light0 = {
		{0.4f, 0.4f, 0.4f, 1.0f}, // ambient
		{1.0f, 1.0f, 1.0f, 1.0f}, // diffuse
		{1.0f, 1.0f, 1.0f, 1.0f}, // specular
		{-5.0f, 2.0f, 2.0f, 1.0f}  // position
	};
	glm::vec4 lightPos = glm::vec4(-5.0f, 2.0f, 2.0f, 1.0f); //light position

	rt3d::materialStruct material0 = {
		{0.2f, 0.4f, 0.2f, 1.0f}, // ambient
		{0.5f, 1.0f, 0.5f, 1.0f}, // diffuse
		{0.0f, 0.1f, 0.0f, 1.0f}, // specular
		2.0f  // shininess
	};

	rt3d::materialStruct material1 = {
		{0.4f, 0.4f, 1.0f, 1.0f}, // ambient
		{0.8f, 0.8f, 1.0f, 1.0f}, // diffuse
		{0.8f, 0.8f, 0.8f, 1.0f}, // specular
		1.0f  // shininess
	};

	SDL_GameController* gamePad = NULL;

	int currentAnim;
public:
	virtual void init() = 0;
	virtual void draw(SDL_Window* window) = 0;
	virtual void update() = 0;
	virtual glm::vec3 getPosition() = 0;
};