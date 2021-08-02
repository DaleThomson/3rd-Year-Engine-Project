#pragma once
#include "SDL.h"
#include "rt3d.h"
#include "rt3dObjLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include <SDL_ttf.h>
#include "loadTexture.h"
#include "Camera.h"
#include "Move.h"
//This is the blue print class for the graphical part of an object.
//Any voids required should be added in here and followed down the pipeline.
//E.G. AbstractDisplay -> Level -> LevelDisplay
//Classes that inherit from abstract display should be for graphics only
using namespace std;

#define DEG_TO_RADIAN 0.017453293

class AbstractDisplay {
protected:
	GLuint meshIndexCount = 0;
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

	// light attenuation
	float attConstant = 1.0f;
	float attLinear = 0.0f;
	float attQuadratic = 0.0f;


	float theta = 0.0f;

public:
	virtual void init() = 0;
	virtual void draw(SDL_Window* window) = 0;
};