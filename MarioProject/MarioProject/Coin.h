#ifndef _COIN_H
#define _COIN_H

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "constant.h"
#include "Texture2D.h"
#include "Character.h"

using namespace std;

class LevelMap;

class Coin : public Character
{
public:
	Coin(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position);
	~Coin();

	void Render()override;
	void Update(float deltaTime, SDL_Event e)override;

private:
	float m_single_sprite_w;
	float m_single_sprite_h;

	int m_current_frame;
	float m_frame_delay;
};

#endif // !_COIN_H
