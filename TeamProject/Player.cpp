#include "Player.h"

Player* Player::instance = nullptr;

Player::Player() { }

void Player::InitPlayer(int life)
{
	upperNode.position.SetpositionXY(10, 10);

	downperNode.position.SetpositionXY(10, 15);

	upperNode.tileState = Tile::INPUT_NODE;
	downperNode.tileState = Tile::INPUT_NODE;

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

void Player::SetPosition(int& x, int& y)
{
	position.SetpositionXY(x, y);
}
