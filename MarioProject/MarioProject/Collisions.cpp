#include "Collisions.h"
#include "Character.h"

Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	m_instance = nullptr;
	
	
}

Collisions* Collisions::Instance()
{
	if (!m_instance)
	{
		m_instance = new Collisions;
	}

	return m_instance;
}

bool Collisions::Circle(Circle2D character1, Circle2D character2)
{
	Vector2D vec = Vector2D((character1.x - character2.x), character1.y - character2.y);
	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	double combined_distance = (character1.radius + character2.radius);
	return distance < combined_distance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.x + (rect1.width/2) > rect2.x && 
		rect1.x + (rect1.width/2) < rect2.x + rect2.width &&
		rect1.y + (rect1.height/2) > rect2.y && 
		rect1.y + (rect1.height / 2) < rect2.y + rect2.height)
	{
		return true;
	}

	return false;
}



