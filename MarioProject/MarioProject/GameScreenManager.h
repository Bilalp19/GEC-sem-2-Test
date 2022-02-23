#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H


class GameScreen;

#pragma once
class GameScreenManager
{

public: 
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS new_screen);

private:
	SDL_Renderer* m_renderer;
	GameScreen* m_current_screen;

};


#endif // !_GAMESCREENMANAGER_H
