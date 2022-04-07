#ifndef _LUIGI_H
#define _LUIGI_H
#include "Character.h"

class Luigi : public Character
{
public:
	Luigi(SDL_Renderer* renderer, string imagePath, Vector2D start_postion, LevelMap* map);

	void Update(float deltaTime, SDL_Event e) override;

};

#endif // !_MARIO_H