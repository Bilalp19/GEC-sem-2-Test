#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "constant.h"
#include "Texture2D.h"
#include "Character.h"

using namespace std;


class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void Render()override;
	void Update(float deltaTime, SDL_Event e)override;

	void TakeDamage();
	void Jump();
	bool GetInjured() { return m_injured; }

	void MoveLeft(float deltaTime) override;
	void MoveRight(float deltaTime) override;

private:

	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	void FlipRightwayUp();


};

#endif // !_CHARACTERKOOPA_H
