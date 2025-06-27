#pragma once
#include "Defines.h"
#include "Enums.h"
#include "Console.h"

typedef struct _pos
{
	int x;
	int y;
	bool operator == (const _pos& _other) const
	{
		return (x == _other.x && y == _other.y);
	}

	void SetpositionXY(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

}POS, * PPOS;

typedef struct _playerNode
{
	POS position;
	Tile tileState;

} PlayerNode, * PPlayerNode;



class Player
{
public:
	POS position;

	static Player* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Player;
		}
		return instance;
	}
	static void DestroyInstance()
	{
		SAFE_DELETE(instance);
	}

	void InitPlayer(int life);
	void SetPosition(int x, int y);
	void PlayerHit(int damage);
	void PlayerHeal(JudgeResult& jr);
	int GetCurrentLife() const { return currentLife; }
	int GetMaxLife() const { return maxLife; }
	COLOR rainbowNode();
	void ColorInit();

	PlayerNode* GetNode(int number); // 1일때는 upper 2일때는 downper Node를 반환하는 함수
	


private:
	COLOR nodeColors[7]
	{
		COLOR::RED,
		COLOR::YELLOW,
		COLOR::GREEN,
		COLOR::LIGHT_BLUE,
		COLOR::BLUE,
		COLOR::VOILET,
		COLOR::LIGHT_VIOLET,
	};

	int colorIdx = 0;

	PlayerNode upperNode;
	PlayerNode downperNode;

	PPlayerNode upperNodePtr = &upperNode;
	PPlayerNode downperNodePtr = &downperNode;

	int currentLife;
	int maxLife;

	bool isDie;
	Player();
	static Player* instance;
};

