#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include <iostream>
#include "Commons.h"




class Texture2D;
class Mario;
class Luigi;


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
Mario* mario;
Luigi* luigi;
};

#endif

