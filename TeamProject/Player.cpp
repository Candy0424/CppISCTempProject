#include "Player.h"
#include <algorithm>

Player* Player::instance = nullptr;

Player::Player() { }

void Player::InitPlayer(int life)
{	

	upperNode.position.SetpositionXY(10, 25);

	downperNode.position.SetpositionXY(10, 30);

	SetPosition(5, downperNode.position.y);

	upperNode.tileState = Tile::INPUT_NODE;
	downperNode.tileState = Tile::INPUT_NODE;

	maxLife = life;
	currentLife = maxLife;
	isDie = false;
}

PlayerNode* Player::GetNode(int number)
{
	switch (number)
	{
	case 1:
		return upperNodePtr;
	case 2:
		return downperNodePtr;
	default:
		return nullptr; // 존재하는 노드가 없음.
	}
}

void Player::SetPosition(int x, int y)
{
	position.SetpositionXY(x, y);
}

void Player::PlayerHit(int damage)
{
	currentLife = std::clamp(currentLife - abs(damage), 0, maxLife);
	if (currentLife <= 0)
		isDie = true;
}

void Player::PlayerHeal(int heal)
{
	currentLife = std::clamp(currentLife + abs(heal), 0, maxLife);
}
