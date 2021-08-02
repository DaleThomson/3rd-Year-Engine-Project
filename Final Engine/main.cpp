#include "Window.h"
#include "IntroductionLevel.h"
#include "Player.h"
#include "OpeningWindow.h"

//	#################
//	GAME DEMO
//	#################

Window* hWindow;
AbstractLevel* level;
OpeningWindow* opening;
Player* player;

void init()
{
	player = new Player();
	level = new IntroductionLevel(player);

	level->init();
}

void update(AbstractLevel** levels)
{
	level->update(levels);
}

void draw(SDL_Window* window)
{
	level->draw(hWindow->getWindow());
}

int main(int argc, char *argv[])
{
	//allows png files to be loaded
	IMG_Init(IMG_INIT_PNG);

	SDL_Renderer *renderTarget = nullptr;
	SDL_GLContext glContext; // OpenGL context handle
	SDL_Event sdlEvent;  // variable to detect SDL events

	hWindow = new Window(800, 600, "Introduction Screen");
	opening = new OpeningWindow();


	// Required on Windows *only* init GLEW to access OpenGL beyond 1.1
	hWindow->setupRC(glContext);
	renderTarget = SDL_CreateRenderer(hWindow->getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) { // glewInit failed, something is seriously wrong
		std::cout << "glewInit failed, aborting." << endl;
		exit(1);
	}
	opening->init();
	while (opening->runOpening)
	{
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT)
				opening->runOpening = false;
		}
		opening->update();
		opening->draw(hWindow->getWindow());
	}

	opening->getRunning();
	SDL_DestroyWindow(hWindow->getWindow());

	//########################
	//	MAIN GAME UNDER HERE
	//########################

	//hWindow = new Window(800, 600, "Graded Unit");
	hWindow = new Window(opening->getPos().x, opening->getPos().y, "Graded Unit");

	// Required on Windows *only* init GLEW to access OpenGL beyond 1.1
	hWindow->setupRC(glContext);
	renderTarget = SDL_CreateRenderer(hWindow->getWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	init();

	cout << glGetString(GL_VERSION) << endl;

	while (opening->getRunning()) {	// the event loop
		while (SDL_PollEvent(&sdlEvent)) {
			if (sdlEvent.type == SDL_QUIT)
				opening->setRunning(false);
		}
		update(&level);
		draw(hWindow->getWindow());
	}

	BASS_Free();
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(hWindow->getWindow());
	SDL_Quit();
	return 0;
}