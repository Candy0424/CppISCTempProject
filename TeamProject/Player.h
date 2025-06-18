#pragma once
#include "Defines.h"
#include "Enums.h"

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
private:
	PlayerNode upperNode;
	PlayerNode downperNode;

	PPlayerNode upperNodePtr = &upperNode;
	PPlayerNode downperNodePtr = &downperNode;

	int life;
	bool isDie;
	Player() {};
public:
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

	PlayerNode* GetNode(int number); // 1�϶��� upper 2�϶��� downper Node�� ��ȯ�ϴ� �Լ�

private:
	static Player* instance;
};

