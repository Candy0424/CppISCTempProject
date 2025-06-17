#pragma once
#include "Player.h"
class GameScene
{
public :
	void Init();
	void Update();
	void Render(const Player* player);
};

