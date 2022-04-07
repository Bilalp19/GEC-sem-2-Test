#ifndef _MARIO_H
#define _MARIO_H
#include "Character.h"

class Mario : public Character
{
public: 
	Mario(SDL_Renderer* renderer, string imagePath, Vector2D start_postion, LevelMap* map);

	void Update(float deltaTime, SDL_Event e) override;
};

#endif // !_MARIO_H

