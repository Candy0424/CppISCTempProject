#include "Player.h"

Player* Player::instance = nullptr;

void Player::InitPlayer(int life)
{
	upperNode.position.SetpositionXY(20, 8);

	downperNode.position.SetpositionXY(20, 18);

	this->life = life;
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
