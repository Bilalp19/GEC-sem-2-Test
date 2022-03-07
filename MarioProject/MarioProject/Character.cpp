#include "Character.h"
#include "Texture2D.h"
#include "constant.h"
#include "Commons.h"
using namespace std;


Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_postion)
{
	m_renderer = renderer;
	m_position = start_postion;
	m_moving_left = false;
	m_moving_right = false;
	m_collision_radius = 15.0f;

	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load background texture!" << endl;
	
	}

}

Character::~Character() { m_renderer = nullptr; }

void Character::Render(){}

void Character::Update(float deltaTime, SDL_Event e){}

Vector2D Character::getPosition() { return m_position; }

void Character::SetPosition(Vector2D new_postion) { m_position = new_postion; }

void Character::MoveLeft(float deltaTime){}

void Character::MoveRight(float deltaTime){}

void Character::AddGravity(float deltaTime){}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
}

