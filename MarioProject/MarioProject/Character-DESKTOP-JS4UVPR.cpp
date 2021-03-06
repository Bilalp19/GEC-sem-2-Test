#include "Character.h"
#include "Texture2D.h"
#include "constant.h"
#include "Commons.h"
using namespace std;


Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_postion)
{
	m_renderer = renderer;
	m_position = start_postion;
	m_facing_direction = FACING_RIGHT;
	m_moving_left = false;
	m_moving_right = false;

	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load background texture!" << endl;
	
	}

}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if(m_moving_right)
	{
		MoveRight(deltaTime);
	}
	
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
			}
		break;
	}
	
}

Vector2D Character::getPosition()
{
	return m_position;
}

void Character::SetPosition(Vector2D new_postion)
{
	m_position = new_postion;
}

void Character::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= deltaTime * MOVEMENTSPEED;
}

void Character::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += deltaTime * MOVEMENTSPEED;
}

void Character::AddGravity(float deltaTime)
{
	if (m_position + 
}
