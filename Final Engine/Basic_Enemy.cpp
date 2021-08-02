#include "Basic_Enemy.h"

void Basic_Enemy::init()
{
	//shader
	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light0);
	rt3d::setMaterial(shaderProgram, material1);

	//model loading
	rt3d::loadObj("../Resources/3D_Objects/MODEL.obj", verts, norms, tex_coords, indices);
	meshIndexCount[0] = indices.size();
	textures[0] = loadTexture::loadTextures("../Resources/Textures/fabric.png");
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(),
		meshIndexCount[0], indices.data());
	verts.clear(), norms.clear(), tex_coords.clear(), indices.clear();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Basic_Enemy::setEnemyPosition(glm::vec3 newPosition)
{
	position = newPosition;
}

void Basic_Enemy::setMinRange(glm::vec3 position)
{
	minRange = position;
}

void Basic_Enemy::setMaxRange(glm::vec3 position)
{
	maxRange = position;
}

glm::vec3 Basic_Enemy::getPosition()
{
	return position;
}

void Basic_Enemy::setEnemyRotate(GLfloat newRotate)
{
	rotate = newRotate;
}

glm::vec3 Basic_Enemy::getScale()
{
	return scale;
}

void Basic_Enemy::update()
{

	setEnemyPosition(Move::moveRight(getPosition(), Move::getRotation(), velocity));

	if (position.z < minRange.z)
	{
		velocity *= -1.0f;
		rotate = 0.0f;
	}

	if (position.z > maxRange.z)
	{
		velocity *= -1.0f;
		rotate = 3.0f;
	}
}

void Basic_Enemy::draw(SDL_Window* window)
{
	//GLfloat scale(1.0f); // just to allow easy scaling of complete scene
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
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(position));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(scale));
	mvStack.top() = glm::rotate(mvStack.top(), rotate, glm::vec3(0.0f, 1.0f, 0.0f));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::setMaterial(shaderProgram, material1);
	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount[0], GL_TRIANGLES);
	mvStack.pop();

	glDepthMask(GL_TRUE);
}