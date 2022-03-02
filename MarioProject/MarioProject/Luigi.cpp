#include "Luigi.h"
#include "Texture2D.h"
Luigi::Luigi(SDL_Renderer* renderer, string imagePath, Vector2D start_postion) : Character(renderer, imagePath, start_postion)
{
	m_facing_direction = FACING_LEFT;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load background texture" << endl;
	}
}

Luigi::~Luigi()
{
	m_renderer = nullptr;
}

void Luigi::Render()
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

void Luigi::Update(float deltaTime, SDL_Event e)
{
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = true;
			break;

		case SDLK_d:
			m_moving_right = true;
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			m_moving_left = false;
			break;

		case SDLK_d:
			m_moving_right = false;
			break;
		}
		break;
	}
	Character::Update(deltaTime, e);
}

void Luigi::AddGravity(float deltaTime)
{

}

void Luigi::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x += deltaTime * MOVEMENTSPEED;
}

void Luigi::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x -= deltaTime * MOVEMENTSPEED;
}
