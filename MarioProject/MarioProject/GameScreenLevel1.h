#pragma once
#include "GameScreen.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include "Commons.h"




class Texture2D;


class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
Texture2D* m_background_texture;
bool SetUpLevel();
};
