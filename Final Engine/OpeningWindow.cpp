#include "OpeningWindow.h"

void OpeningWindow::init()
{
	cout << "1. Play" << endl;
	cout << "2. Options" << endl;
	cout << "3. Quit" << endl;
		
	//shader
	shaderProgram = rt3d::initShaders("../Resources/Shaders/phong.vert", "../Resources/Shaders/phong.frag");
	rt3d::setLight(shaderProgram, light0);
	rt3d::setMaterial(shaderProgram, material0);

	textures[0] = loadTexture::loadTextures("../Resources/Textures/Introduction.png");
	textures[1] = loadTexture::loadTextures("../Resources/Textures/Play_Button.png");
	textures[2] = loadTexture::loadTextures("../Resources/Textures/Options_Button.png");
	textures[3] = loadTexture::loadTextures("../Resources/Textures/Quit_Button.png");
	textures[4] = loadTexture::loadTextures("../Resources/Textures/highlight.png");

	buttonPos[0] = glm::vec3(1, 0, 1);
	buttonPos[1] = glm::vec3(1, 0, 1);
	buttonPos[2] = glm::vec3(1, 0, 1);


	for (int i = 0; i < 5; i++)
	{
		box[i] = new Box(textures[0]);
		box[i]->init();
	}

	box[0]->setPosition(glm::vec3(0.0f, 3.0f, 0.0f));
	box[1]->setPosition(glm::vec3(-6.0f, 0.5f, 35.0f));
	box[2]->setPosition(glm::vec3(-6.0f, 0.5f, 40.0f));
	box[3]->setPosition(glm::vec3(-6.0f, 0.5f, 45.0f));
	box[4]->setPosition(glm::vec3(-6.0f, 0.5f, 50.0f));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpeningWindow::findController()
{
	int attempts = 0;

	do {
		attempts++;
		printf("%i joysticks were found.\n\n", SDL_NumJoysticks());
	} while ((SDL_NumJoysticks() < 0) || attempts <= 0);

	
	if (SDL_NumJoysticks() > 0)
		gamePad = SDL_GameControllerOpen(0);

	foundController = false;
}

glm::vec2 OpeningWindow::getPos()
{
	return glm::vec2(horizontal, vertical);
}

// Get the horizontal and vertical screen sizes in pixel
void OpeningWindow::GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void OpeningWindow::play()
{
	//play game
	cout << "play game" << endl;
	running = true;
	runOpening = false;
}

void OpeningWindow::options()
{
	cout << "1. Fullscreen" << endl;
	cout << "2. Windowed" << endl;
	cout << "Option: ";

	int option;
	cin >> option;

	switch (option)
	{
	case 1:
	{
		//make full screen
		GetDesktopResolution(horizontal, vertical);
	}
	break;
	case 2:
		break;
	default:
		cout << "Please pick a valid option" << endl;
	}
}

void OpeningWindow::quit()
{
	//close program
	cout << "quit" << endl;
	running = false; 
	runOpening = false;
}

bool OpeningWindow::getRunning()
{
	return running;
}

void OpeningWindow::setRunning(bool newRunning)
{
	running = newRunning;
}

void OpeningWindow::update()
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	
	if(foundController)
		findController();

	if (keys[SDL_SCANCODE_DOWN] || SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		//move down
		if (!pressed)
		{
			//highlight option 1 down
			currentPos++;

			//box[4]->setPos(buttonPos[currentPos]);
			cout << currentPos << endl;
			pressed = true;
		}
	}

	if (keys[SDL_SCANCODE_UP] || SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_UP))
	{
		if (!pressed)
		{
			//highlight option 1 up

			currentPos--;

			//box[4]->setPos(buttonPos[currentPos]);
			cout << currentPos << endl;
			pressed = true;
		}
	}

	if (keys[SDL_SCANCODE_RETURN] || SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A))
	{
		//select
		if (!pressed)
		{
			//Chose the highlighted options
			cout << "option chosen: " << endl;

			switch (currentPos)
			{
			case 0:
				play();
				break;
			case 1:
				options();
				break;
			case 2:
				quit();
				break;
			}

			pressed = true;
		}
	}

	//keeps position within range
	if (currentPos >= 3)
	{
		currentPos = 0;
	}

	if (currentPos <= -1)
	{
		currentPos = 2;
	}

	if (currentPos == 0)
		cout << "Current Option: Play" << endl;
	if (currentPos == 1)
		cout << "Current Option: Options" << endl;
	if (currentPos == 2)
		cout << "Current Option: Quit" << endl;

	if (!keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_SPACE]
		&& !SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A)
		&& !SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_UP)
		&& !SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		pressed = false;
	}
}

void OpeningWindow::draw(SDL_Window* window)
{
	glEnable(GL_CULL_FACE);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection(1.0f);
	glm::mat4 modelview(1.0);
	mvStack.push(modelview);
	projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 1.0f, 50.0f);
	rt3d::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));

	camera::setAt(Move::moveForward(camera::getEye(), Move::getRotation(), 1.0f));
	mvStack.top() = glm::lookAt(camera::getEye(), camera::getAt(), camera::getUp());

	for (int i = 0; i < 5; i++)
	{
		box[i]->draw(window);
	}

	SDL_GL_SwapWindow(window); // swap buffers
}