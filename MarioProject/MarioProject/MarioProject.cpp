#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include "constant.h"
using namespace std;

//Globals
SDL_Window* g_window = nullptr;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
	


int main(int argc, char* args[])
{
	if (InitSDL())
	{
		bool quit = false; 

		while (!quit)
		{
			quit = Update();
		}
	}


	CloseSDL();
		
	return 0;
		
}

		
bool Update()
{
	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
		case SDL_QUIT: 
			return true;
		break;
	}
	switch (e.key.keysym.sym)
	{
		case SDLK_q :
		return true;
		break;

	}

	

	return false;
}



bool InitSDL()
{
		
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Second" << endl;
		cout << "SDL did not initalise. Error" << SDL_GetError() << endl;
		return false;
	}
	else
	{
		

		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (g_window == nullptr)
		{
			// window failed 
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
			//release the window

		
	}
}

void CloseSDL() 
{
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	// quit SDL
	IMG_Quit();
	SDL_Quit();

}





