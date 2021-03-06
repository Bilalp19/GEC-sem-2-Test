#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "LevelMap.h"
#include <iostream>
#include <vector>

class Texture2D;
class Mario;
class Luigi;
class CharacterKoopa;
class LevelMap;
class PowBlock;
class Coin;


class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePowBlock();

	

private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	Mario* mario;
	Luigi* luigi;
	CharacterKoopa* koopa;
	Coin* coin;
	void SetLevelMap();
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	float k_timer;
	void DoScreenShake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoin(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position);
	std::vector<CharacterKoopa*> m_enemies;
	std::vector<Coin*> m_coins;
	

};

#endif

