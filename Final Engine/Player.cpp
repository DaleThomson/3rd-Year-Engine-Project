#include "Player.h"

void Player::init()
{
	printf("%i joysticks were found.\n\n", SDL_NumJoysticks());

	gamePad = SDL_GameControllerOpen(0);

	//starting the array of labels
	labels[0] = 0;

	samples = new HSAMPLE[5];	//array of sound  files
	samples[0] = Sound::loadSample("../Resources/SoundFiles/jump.wav", BASS_SAMPLE_OVER_POS);	//adding sound files to the array to be played later in code
	samples[1] = Sound::loadSample("../Resources/SoundFiles/Damage.wav", BASS_SAMPLE_OVER_POS);

	//shader
	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light0);
	rt3d::setMaterial(shaderProgram, material1);

	textureProgram = rt3d::initShaders("../Resources/Shaders/textured.vert", "../Resources/Shaders/textured.frag");

	//model loading
	/*rt3d::loadObj("../Resources/3D_Objects/tris.MD2", verts, norms, tex_coords, indices);
	meshIndexCount[0] = indices.size();
	textures[0] = loadTexture::loadTextures("../Resources/Textures/fabric.png");
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(),
		meshIndexCount[0], indices.data());
	verts.clear(), norms.clear(), tex_coords.clear(), indices.clear();*/


	//model loading
	rt3d::loadObj("../Resources/3D_Objects/cube.obj", verts, norms, tex_coords, indices);
	meshIndexCount[1] = indices.size();
	meshObjects[1] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(),
		meshIndexCount[1], indices.data());
	verts.clear(), norms.clear(), tex_coords.clear(), indices.clear();

	textures[0] = loadTexture::loadTextures("../Resources/Textures/hobgoblin2.bmp");
	meshObjects[0] = tmpModel.ReadMD2Model("tris.MD2");
	md2VertCount = tmpModel.getVertDataCount();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Player::setPlayerPosition(glm::vec3 position)
{
	playerPosition = position;
}

glm::vec3 Player::getPosition()
{
	return playerPosition;
}

void Player::setPlayerRotate(GLfloat newRotate)
{
	playerRotate = newRotate;
}

glm::vec3 Player::getScale()
{
	return scale;
}

void Player::takeDamage()
{
	//reset lives count
	playerLives--;
	Sound::playSample(samples[1]);
	cout << playerLives << endl;
}

void Player::setJump(bool setJump)
{
	doJump = setJump;
}

void Player::setCheckPoint(glm::vec3 checkpoint)
{
	chekPointPos = checkpoint;
}

bool Player::getAllowDamage()
{
	return allowDamage;
}

void Player::setAllowDamage(bool setdamage)
{
	allowDamage = setdamage;
}

int Player::getCollectablesFound()
{
	return collectablesFound;
}

void Player::addCollectable()
{
	collectablesFound++;
}

void Player::update()
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	setPlayerPosition(Move::grav(getPosition()));

	glm::vec3 camPos = camera::getEye();
	camPos.z = getPosition().z;
	camera::setEye(camPos);

	if (keys[SDL_SCANCODE_D] || SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
		setPlayerPosition(Move::moveRight(getPosition(), Move::getRotation(), 0.125f));
		setPlayerRotate(0.0f);
	}

	if (keys[SDL_SCANCODE_A] || SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
		setPlayerPosition(Move::moveRight(getPosition(), Move::getRotation(), -0.125f));
		setPlayerRotate(3.0f);
	}

	if (keys[SDL_SCANCODE_SPACE] || SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A)) {
		doJump = true;
		Move::setGrav(-0.05f                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              );
	}
	else if (getPosition().y <= 0.0f)
	{
		Move::resetV();
		doJump = false;
	}

	if (keys[SDL_SCANCODE_X])
	{
		if (allowJumpSound)
		{
			Sound::playSample(samples[0]);
			cout << "sound played" << endl;
			allowJumpSound = false;

			//damage player
			takeDamage();
		}
	}
	else
		allowJumpSound = true;

	if (keys[SDL_SCANCODE_L])
		cout << collectablesFound << endl;

	if (doJump)
	{
		glm::vec3 position = getPosition();
		position.y += Move::jump();
		setPlayerPosition(position);
		cout << "JUMPING" << endl;

	}

	if (getPosition().y <= 0.0f)
	{
		glm::vec3 position = getPosition();
		position.y = 0.0f;
		setPlayerPosition(position);
	}

	if (playerLives <= 0)
	{
		playerLives = 5;
		
		//kill player
		setPlayerPosition(chekPointPos);
		
		glm::vec3 camPos = camera::getEye();
		camPos.z = getPosition().z;
		camera::setEye(camPos);
	}

	if (noCollision == true)
	{
		Move::setGrav(-0.3);
	}
}

void Player::draw(SDL_Window* window)
{
	GLfloat scale(1.0f); // just to allow easy scaling of complete scene
	glm::mat4 modelview(1.0); // set base position for scene
	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 150.0f);
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));
	stack<glm::mat4> mvStack;
	mvStack.push(modelview);

	camera::setAt(Move::moveForward(camera::getEye(), Move::getRotation(), 1.0f));
	mvStack.top() = glm::lookAt(camera::getEye(), camera::getAt(), camera::getUp());

	tmpModel.Animate(currentAnim, 0.1);
	rt3d::updateMesh(meshObjects[0], RT3D_VERTEX, tmpModel.getAnimVerts(), tmpModel.getVertDataSize());

	// draw the hobgoblin
	glCullFace(GL_FRONT);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	rt3d::materialStruct tmpMaterial = material1;
	rt3d::setMaterial(shaderProgram, tmpMaterial);
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(1.0f, 1.2f, -5.0f));
	mvStack.top() = glm::rotate(mvStack.top(), float(90.0f*DEG_TO_RADIAN), glm::vec3(-1.0f, 0.0f, 0.0f));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(scale*0.05, scale*0.05, scale*0.05));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::drawMesh(meshObjects[0], md2VertCount, GL_TRIANGLES);
	mvStack.pop();
	glCullFace(GL_BACK);


	////////////////////////////////////////////////////////////////////
	//	This renders a HUD labels
	////////////////////////////////////////////////////////////////////

	//glUseProgram(textureProgram);
	//glDisable(GL_DEPTH_TEST);	//Disable depth test for HUD label
	//
	//labels[0] = loadTexture::textToTexture("Level: " /*+ LevelNum*/, labels[0], { 0, 0, 0 });
	//glBindTexture(GL_TEXTURE_2D, labels[0]);
	//mvStack.push(glm::mat4(1.0));
	//mvStack.top() = glm::translate(mvStack.top(), glm::vec3(-0.8f, 0.8f, 0.0f));
	//mvStack.top() = glm::scale(mvStack.top(), glm::vec3(0.1f, 0.1f, 0.1f));
	//rt3d::setUniformMatrix4fv(textureProgram, "projection", glm::value_ptr(glm::mat4(1.0)));
	//rt3d::setUniformMatrix4fv(textureProgram, "modelview", glm::value_ptr(mvStack.top()));
	//rt3d::drawIndexedMesh(meshObjects[1], meshIndexCount[1], GL_TRIANGLES);
	//mvStack.pop();


	//labels[1] = loadTexture::textToTexture("HEALTH: " /*+ playerLives*/, labels[1], { 0, 0, 0 });
	//glBindTexture(GL_TEXTURE_2D, labels[1]);
	//mvStack.push(glm::mat4(1.0));
	//mvStack.top() = glm::translate(mvStack.top(), glm::vec3(-0.8f, 0.7f, 0.0f));
	//mvStack.top() = glm::scale(mvStack.top(), glm::vec3(0.1, 0.1, 0.1f));
	//rt3d::setUniformMatrix4fv(textureProgram, "projection", glm::value_ptr(glm::mat4(1.0)));
	//rt3d::setUniformMatrix4fv(textureProgram, "modelview", glm::value_ptr(mvStack.top()));
	//rt3d::drawIndexedMesh(meshObjects[1], meshIndexCount[1], GL_TRIANGLES);
	//mvStack.pop();

	//
	//labels[2] = loadTexture::textToTexture("COLLECTABLES: " /*+ numCollectables*/, labels[2], { 0, 0, 0 });
	//glBindTexture(GL_TEXTURE_2D, labels[2]);
	//mvStack.push(glm::mat4(1.0));
	//mvStack.top() = glm::translate(mvStack.top(), glm::vec3(-0.8f, 0.6f, 0.0f));
	//mvStack.top() = glm::scale(mvStack.top(), glm::vec3(0.1, 0.1, 0.1f));
	//rt3d::setUniformMatrix4fv(textureProgram, "projection", glm::value_ptr(glm::mat4(1.0)));
	//rt3d::setUniformMatrix4fv(textureProgram, "modelview", glm::value_ptr(mvStack.top()));
	//rt3d::drawIndexedMesh(meshObjects[1], meshIndexCount[1], GL_TRIANGLES);
	//mvStack.pop();
	
	glEnable(GL_DEPTH_TEST);	//Re-enable depth test after HUD label 
	mvStack.pop();	 // initial matrix
	glCullFace(GL_BACK);
	glDepthMask(GL_TRUE);
}