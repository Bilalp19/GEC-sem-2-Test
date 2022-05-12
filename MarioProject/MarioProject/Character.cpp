#include "Character.h"
#include "Texture2D.h"
#include "constant.h"
#include "Commons.h"
#include "LevelMap.h"
using namespace std;


Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_postion, LevelMap* map) 
{
	m_renderer = renderer;
	m_position = start_postion;
	m_moving_left = false;
	m_moving_right = false;
	m_collision_radius = 15.0f;
	m_alive = true;
	m_jumping = false;
	m_current_level_map = map;

	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load background texture!" << endl;
	}

}

Character::~Character() { m_renderer = nullptr; }

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
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	OnScreen(deltaTime);

	if (m_jumping)
	{
		//adjust position
		m_position.y -= m_jump_force * deltaTime;

		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//is jump force 0?
		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}
	}

	//collision postion variables
	int centralX_postion = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;


	//cout << "X pos: " << centralX_postion << " FootPos: " << foot_position << " Tile: " << m_current_level_map->GetTileAt(foot_position, centralX_postion) << endl;
	
	//deal with gravity
	if (m_current_level_map->GetTileAt(foot_position, centralX_postion) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//collided with ground so we can jump again
		m_can_jump = true;
	}

}

Vector2D Character::getPosition() { return m_position; }

void Character::SetPosition(Vector2D new_postion) { m_position = new_postion; }

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
	if (m_position.y + 64 <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
	}
	else
	{
		m_can_jump = true;
	}
}

void Character::OnScreen(float deltaTime)
{
	if (m_position.x + m_texture->GetWidth() >= SCREEN_WIDTH)
	{
		m_facing_direction = FACING_LEFT;
		m_position.x -= deltaTime * MOVEMENTSPEED;
	}
	else if (m_position.x <0)
	{
		m_facing_direction = FACING_RIGHT;
		m_position.x += deltaTime * MOVEMENTSPEED;
	}
}

void Character::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITAL_JUMP_FORCE;
		m_jumping = true; 
		m_can_jump = false; 
	}
}

Circle2D Character::GetCollisionRadius()
{
	return Circle2D(m_position.x, m_position.y, m_collision_radius);
}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
}

