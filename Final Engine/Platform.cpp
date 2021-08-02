#include "Platform.h"

void Platform::init()
{
	//shader
	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light0);
	rt3d::setMaterial(shaderProgram, material1);

	rt3d::loadObj("../Resources/3D_Objects/cube.obj", verts, norms, tex_coords, indices);
	meshIndexCount[0] = indices.size();
	textures[0] = loadTexture::loadTextures("../Resources/Textures/fabric.png");
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(),
		meshIndexCount[0], indices.data());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

glm::vec3 Platform::getPosition()
{
	return position;
}
void Platform::setPosition(glm::vec3 setPosition)
{
	position = setPosition;
}

glm::vec3 Platform::getScale()
{
	return scale;
}

void Platform::setScale(glm::vec3 setScale)
{
	scale = setScale;
}

void Platform::draw(SDL_Window* window)
{
	glm::mat4 modelview(1.0); // set base position for scene
	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 150.0f);
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));
	stack<glm::mat4> mvStack;
	mvStack.push(modelview);

	camera::setAt(Move::moveForward(camera::getEye(), Move::getRotation(), 1.0f));
	mvStack.top() = glm::lookAt(camera::getEye(), camera::getAt(), camera::getUp());

	glUseProgram(shaderProgram);
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), position);
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(scale));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::setMaterial(shaderProgram, material1);
	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount[0], GL_TRIANGLES);
	mvStack.pop();

	mvStack.pop();
	glDepthMask(GL_TRUE);
}


void Platform::update()
{
}