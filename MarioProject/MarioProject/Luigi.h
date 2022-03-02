#ifndef _LUIGI_H
#define _LUIGI_H
#include "Character.h"
class Luigi : public Character
{
public:
	Luigi(SDL_Renderer* renderer, string imagePath, Vector2D start_postion);
	~Luigi();

	void MoveLeft(float deltaTime)override;
	void MoveRight(float deltaTime)override;
	void AddGravity(float deltaTime)override;
	void Render()override;
	void Update(float deltaTime, SDL_Event e)override;


private:
	FACING m_facing_direction;


};

#endif // !_MARIO_H