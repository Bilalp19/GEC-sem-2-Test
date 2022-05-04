#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Mario.h"
#include "Luigi.h"
#include "CharacterKoopa.h"
#include "Coin.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "PowBlock.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	//Set up player character

	
	m_level_map = nullptr;

	k_timer = 2.0f;
}
GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;
	m_pow_block = nullptr;
	delete m_pow_block;
	delete mario;
	delete luigi;
	mario = nullptr;
	m_enemies.clear();
}

void GameScreenLevel1::Render() 
{
	//draw the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	//draw the background 
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	m_pow_block->Render();
	
	for (int i = 0; i < m_coins.size(); i++)
	{
		if (m_coins[i]->GetAlive())
		{
			m_coins[i]->Render();
		}
	}

	if (mario->GetAlive())
		mario->Render();

	if(luigi->GetAlive())
		luigi->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
	UpdatePowBlock();
	UpdateCoin(deltaTime, e);
	UpdateEnemies(deltaTime, e);
	if (Collisions::Instance()->Circle(mario->GetCollisionRadius(), luigi->GetCollisionRadius()))
	{
		cout << "Circle hit!" << endl;
	}
	
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}
	
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_screenshake = false;
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	k_timer -= deltaTime;
	if (k_timer <= 0)//less or equal to zero
	{
		//call creatge koopa
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(300, 32), FACING_LEFT, KOOPA_SPEED);
		//reset timer
		k_timer = 2.0f;
	}
}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (mario->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				mario->CancelJump();
			}
		}
	}


	if (Collisions::Instance()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (luigi->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				luigi->CancelJump();
			}
		}
	}

}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;


	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{	//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->getPosition().y > 300.0f)
			{
				//is the enemy off screen to the left / right? 
				if (m_enemies[i]->getPosition().x  < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f)
					|| m_enemies[i]->getPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.5f))
				{
					m_enemies[i]->SetAlive(false);
				}

			}
				//update
				m_enemies[i]->Update(deltaTime, e);

				if ((m_enemies[i]->getPosition().y > 300 || m_enemies[i]->getPosition().y <= 64.0f) 
					&& (m_enemies[i]->getPosition().x < 64.0f || m_enemies[i]->getPosition().x > SCREEN_WIDTH - 96.0f))
				{
					//ignore collision if behind pip	
				}
				else
				{
				//check to see if enemy collides with players
					if (Collisions::Instance()->Box(m_enemies[i]->GetCollisionBox(), mario->GetCollisionBox()))
					{
						if (m_enemies[i]->GetInjured())
						{
							m_enemies[i]->SetAlive(false);
						}
						else 
						{
							if (mario->GetAlive())
							{
								//set alive to false
								mario->SetAlive(false);
							}
						}
					}

					if (Collisions::Instance()->Box(m_enemies[i]->GetCollisionBox(), luigi->GetCollisionBox()))
					{
						if (m_enemies[i]->GetInjured())
						{
							m_enemies[i]->SetAlive(false);
						}
						else
						{
							if (luigi->GetAlive())
							{
								//set alive to false
								luigi->SetAlive(false);
							}
						}
					}
				}
				
			

			//if the enemy is no longer alive then schedule it for deltion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}

}

void GameScreenLevel1::UpdateCoin(float deltaTime, SDL_Event e)
{
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Update(deltaTime, e);
		
		
			//check to see if enemy collides with players
			if (Collisions::Instance()->Box(m_coins[i]->GetCollisionBox(), mario->GetCollisionBox()))
			{
				m_coins[i]->SetAlive(false);
			}

			if (Collisions::Instance()->Box(m_coins[i]->GetCollisionBox(), luigi->GetCollisionBox()))
			{
				m_coins[i]->SetAlive(false);
			}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed );
	m_enemies.push_back(koopa);
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	Coin* coin = new Coin(m_renderer, "Images/Coin.png", m_level_map, position);
	m_coins.push_back(coin);
}

bool GameScreenLevel1::SetUpLevel()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	SetLevelMap();

	////set up player character
	mario = new Mario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	luigi = new Luigi(m_renderer, "Images/Luigi.png", Vector2D(100, 330), m_level_map);

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(300, 32), FACING_LEFT, KOOPA_SPEED);

	CreateCoin(Vector2D(150, 350));
	CreateCoin(Vector2D(200, 350));


	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;

}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { 
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } 
	};

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);



}

