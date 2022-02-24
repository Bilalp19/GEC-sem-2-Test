#include "Character.h"
#include "Texture2D.h"
#include "constant.h"
using namespace std;


Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_postion)
{
	m_renderer = renderer;
	m_position = start_postion;

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
}

void Character::Update(float deltaTime, SDL_Event e)
{
	switch (e.key.keysym.sym)
	{
		case SDLK_LEFT:
			m_position.x -= deltaTime * MOVEMENTSPEED;
			break;

		case SDLK_RIGHT:	
			m_position.x += deltaTime * MOVEMENTSPEED;
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
