#pragma once

#include "Box.h"
#include "AbstractDisplay.h"
#include <iostream>
#include <wtypes.h>
#include "GL/GL.h"

using namespace std;

class OpeningWindow : public AbstractDisplay
{
private:
	Box* box[5];
	glm::vec3 buttonPos[3];
	int currentPos = 0;
	GLuint textures[10];
	bool pressed = false;
	bool running = false; // set running to true if play, false if quit
	int horizontal = 800;
	int vertical = 600;

	SDL_GameController* gamePad = NULL;
	bool foundController = true;

public:
	OpeningWindow() {}

	void init();
	void update();
	void draw(SDL_Window*);

	void GetDesktopResolution(int& horizontal, int& vertical);
	void play();
	void options();
	void quit();
	void findController();

	glm::vec2 getPos();
	bool getRunning();
	void setRunning(bool);

	bool runOpening = true;
};

