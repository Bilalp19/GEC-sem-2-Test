#include "Mario.h"
#include "Texture2D.h"

Mario::Mario(SDL_Renderer* renderer, string imagePath, Vector2D start_postion, LevelMap* map) : Character(renderer, imagePath, start_postion, map) {}

void Mario::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = true;
			break;

		case SDLK_RIGHT:
			m_moving_right = true;
			break;

		case SDLK_UP:
			Jump();
			break;
			

		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;

		case SDLK_RIGHT:
			m_moving_right = false;
			break;

		//case SDLK_UP:
		//	m_can_jump = false;
		//	break;


		}
		break;
	}
	Character::Update(deltaTime, e);
}


