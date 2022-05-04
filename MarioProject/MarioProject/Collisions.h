#ifndef _COLLISIONS_H
#define _COLLISIONS_H
#include "Commons.h"

class Character;


class Collisions
{
public:
	~Collisions();
	static Collisions* Instance();
	bool Circle(Circle2D character1, Circle2D character2);
	bool Box(Rect2D rect1, Rect2D rect2);

private: 
	Collisions();
	static Collisions* m_instance;
};
#endif // !_COLLISIONS_H
