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

	colorIdx = 0;

	maxLife = life;
	currentLife = maxLife;
	isDie = false;
}

COLOR Player::rainbowNode()
{
	colorIdx %= 7;
	return nodeColors[colorIdx++];
}

void Player::ColorInit()
{
	colorIdx = 0;
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

void Player::PlayerHeal(JudgeResult& jr)
{
	switch (jr)
	{
	case JudgeResult::PERFECT:
		currentLife = std::clamp(currentLife + 2, 0, maxLife);
		break;
	case JudgeResult::GOOD:
		currentLife = std::clamp(currentLife + 1, 0, maxLife);
		break;
	default:
		break;

	}
}
