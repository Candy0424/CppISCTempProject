#include "GameScene.h"
#include "Enums.h"
#include "Player.h"
#include "Console.h"


void GameScene::Init()
{
}

void GameScene::Update()
{
}

void GameScene::Render(const Player* player)
{
	int x = player->nodeOnePosition.x;
	int y = player->nodeOnePosition.y;

	IsGotoxy(x, y);

	cout << "¡Û";
	cout << "¡Ü";
}
