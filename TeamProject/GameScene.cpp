#include "GameScene.h"
#include "Enums.h"
#include "Console.h"


void GameScene::Init(Player* player)
{
}

void GameScene::Update(Player* player)
{
}

void GameScene::Render(Player* player)
{
	PPlayerNode upperNode = player->GetNode(1);
	PPlayerNode downperNode = player->GetNode(2);

	int upperX = upperNode->position.x;
	int upperY = upperNode->position.y;

	int downperX = downperNode->position.x;
	int downperY = downperNode->position.y;

	IsGotoxy(upperX, upperY);
	cout << "G"; // 상단 노드 표시

	IsGotoxy(downperX, downperY);
	cout << "F"; // 하단 노드 표시
}
