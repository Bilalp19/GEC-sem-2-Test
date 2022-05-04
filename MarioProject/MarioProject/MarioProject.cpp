#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include "constant.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
using namespace std;

//Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
Mix_Music* g_music = nullptr;



//Function Prototypes
bool InitSDL();
bool CloseSDL();
bool Update();
void Render();
void LoadMusic(string path);

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		LoadMusic("Music/Mario.mp3");
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(g_music, -1);
		}

		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
		//set the time
		g_old_time = SDL_GetTicks();
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
	Uint32 new_time = SDL_GetTicks();
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
		case SDLK_0:
			game_screen_manager->ChangeScreen(SCREEN_MENU);
			break;
		case SDLK_1:
			game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
			break;
		case SDLK_2:
			game_screen_manager->ChangeScreen(SCREEN_LEVEL2);
			break;
	}
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
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
		//initialise the mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not init. Error: " << Mix_GetError();
			return false;
		}


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

	//destroy the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;

}

void Render()
{
	//clear screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();

	//update the screen
	SDL_RenderPresent(g_renderer);

}

void LoadMusic(string path)
{
	g_music = Mix_LoadMUS(path.c_str());
	if (g_music == nullptr)
	{
		cout << "Failed to load music. Error: " << Mix_GetError() << endl;
	}
}










