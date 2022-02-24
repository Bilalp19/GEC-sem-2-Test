#include "GameScreen.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include "constant.h"
#include "Texture2D.h"
#include "Commons.h"
using namespace std;


GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}


void GameScreen::Render()
{

}

void GameScreen::Update(float deltaTime, SDL_Event e)
{

}


