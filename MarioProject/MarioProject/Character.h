#ifndef _CHARACTER_H
#define _CHARACTER_H
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "constant.h"
#include "Texture2D.h"
using namespace std;


class Texture2D;
class LevelMap;

class Character
{
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	bool m_moving_left;
	bool m_moving_right;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	bool m_jumping;
	bool m_can_jump;
	float m_movement_speed;
	float m_jump_force;
	float m_collision_radius;
	bool m_alive;
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_postion, LevelMap* map);
	~Character();
	float m_facing_direction;
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_postion);
	Vector2D getPosition();
	float GetCollisionRadius();
	Rect2D GetCollisionBox();
	void Jump();
	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jumping = false; }
	bool SetAlive(bool isAlive);
	bool GetAlive() { return m_alive; }
private: 
	LevelMap* m_current_level_map;

};


#endif 
