#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include "constant.h"
#include "Texture2D.h"
#include "Commons.h"
using namespace std;

//Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;


//Function Prototypes
bool InitSDL();
bool CloseSDL();
bool Update();
void Render();

	


int main(int argc, char* args[])
{
	if (InitSDL())
	{
		bool quit = false; 

		while (!quit)
		{
			Render();
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

		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

		if (g_renderer != nullptr)
		{
			int imageFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initalise. Error: " << IMG_GetError();
				return false; 
			}

			g_texture = new Texture2D(g_renderer);
			if (!g_texture->LoadFromFile("Images/test.bmp"))
			{
				return false;
			}
		}	
		else 
		{
			cout << "Renderer could not initialise, Error: " << SDL_GetError();
			return false;
		}
		if (g_window == nullptr)
		{
			// window failed 
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		//release the window
	}
}

bool CloseSDL() 
{
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	// quit SDL
	IMG_Quit();
	SDL_Quit();
	return true;

	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
	delete g_texture;
	g_texture = nullptr;

}

void Render()
{
	//clear screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	g_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//update the screen
	SDL_RenderPresent(g_renderer);

}










