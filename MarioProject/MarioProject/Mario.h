#ifndef _MARIO_H
#define _MARIO_H
#include "Character.h"
class Mario : public Character
{
public: 
	Mario(SDL_Renderer* renderer, string imagePath, Vector2D start_postion);
	~Mario();
	
	void MoveLeft(float deltaTime)override;
	void MoveRight(float deltaTime)override;
	void AddGravity(float deltaTime)override;
	void Render()override;
	void Update(float deltaTime, SDL_Event e)override;


private: 
	FACING m_facing_direction;

	
};

#endif // !_MARIO_H

