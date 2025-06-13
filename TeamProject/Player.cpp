#include "Player.h"

void Player::InitPlayer(int& life)
{
	nodeOnePosition.x = 20;
	nodeOnePosition.y = 30;

	nodeTwoPosition.x = 20;
	nodeTwoPosition.y = 35;
	this->life = life;
	isDie = false;
}
