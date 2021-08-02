#include "Level_4_Display.h"

// A simple rt3d draw class
void Level_4_Display::init()
{
	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light0);
	rt3d::setMaterial(shaderProgram, material1);

	textureProgram = rt3d::initShaders("../Resources/Shaders/textured.vert", "../Resources/Shaders/textured.frag");
	skyboxProgram = rt3d::initShaders("../Resources/Shaders/cubeMap.vert", "../Resources/Shaders/cubeMap.frag");

	// set light attenuation shader uniforms
	GLuint uniformIndex = glGetUniformLocation(shaderProgram, "attConst");
	glUniform1f(uniformIndex, attConstant);
	uniformIndex = glGetUniformLocation(shaderProgram, "attLinear");
	glUniform1f(uniformIndex, attLinear);
	uniformIndex = glGetUniformLocation(shaderProgram, "attQuadratic");
	glUniform1f(uniformIndex, attQuadratic);

	const char *cubeTexFiles[6] = {
		"../Resources/Town-skybox/Town_bk.bmp", "../Resources/Town-skybox/Town_ft.bmp", "../Resources/Town-skybox/Jungle_1.bmp", "../Resources/Town-skybox/Town_lf.bmp", "../Resources/Town-skybox/Town_up.bmp", "../Resources/Town-skybox/Town_dn.bmp"
	};
	loadTexture::loadCubeMap(cubeTexFiles, &skybox[0]);

	rt3d::loadObj("../Resources/3D_Objects/cube.obj", verts, norms, tex_coords, indices);
	meshIndexCount = indices.size();
	textures[0] = loadTexture::loadTextures("../Resources/Textures/fabric.png");
	meshObjects[0] = rt3d::createMesh(verts.size() / 3, verts.data(), nullptr, norms.data(), tex_coords.data(), meshIndexCount, indices.data());
	verts.clear(), norms.clear(), tex_coords.clear(), indices.clear();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Level_4_Display::draw(SDL_Window* window)
{
	glEnable(GL_CULL_FACE);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 150.0f);
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));
	GLfloat scale(1.0f); // just to allow easy scaling of complete scene
	glm::mat4 modelview(1.0); // set base position for scene
	mvStack.push(modelview);


	camera::setAt(Move::moveForward(camera::getEye(), Move::getRotation(), 1.0f));
	mvStack.top() = glm::lookAt(camera::getEye(), camera::getAt(), camera::getUp());

	glUseProgram(skyboxProgram);
	rt3d::setUniformMatrix4fv(skyboxProgram, "projection", glm::value_ptr(projection));

	glDepthMask(GL_FALSE); // make sure writing to update depth test is off
	glm::mat3 mvRotOnlyMat3 = glm::mat3(mvStack.top());
	mvStack.push(glm::mat4(mvRotOnlyMat3));

	glCullFace(GL_FRONT); // drawing inside of cube!
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox[0]);
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(1.5f, 1.5f, 1.5f));
	rt3d::setUniformMatrix4fv(skyboxProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
	mvStack.pop();
	glCullFace(GL_BACK); // drawing inside of cube!


	// back to remainder of rendering
	glDepthMask(GL_TRUE); // make sure depth test is on

	glUseProgram(shaderProgram);
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));

	glm::vec4 tmp = mvStack.top()*lightPos;
	light0.position[0] = tmp.x;
	light0.position[1] = tmp.y;
	light0.position[2] = tmp.z;
	rt3d::setLightPos(shaderProgram, glm::value_ptr(tmp));

	// GROUND PLANE
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), glm::vec3(-10.0f, -0.1f, -10.0f));
	mvStack.top() = glm::scale(mvStack.top(), glm::vec3(50.0f, 0.1f, 100.0f));
	rt3d::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	rt3d::setMaterial(shaderProgram, material0);
	rt3d::drawIndexedMesh(meshObjects[0], meshIndexCount, GL_TRIANGLES);
	mvStack.pop();

	glDepthMask(GL_TRUE);
}