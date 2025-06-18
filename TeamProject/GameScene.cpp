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
	cout << ((upperNode->tileState == Tile::OUTPUT_NODE) ? "��" : "��"); // ��� ��� ǥ��

	IsGotoxy(downperX, downperY);
	cout << ((downperNode->tileState == Tile::OUTPUT_NODE) ? "��" : "��"); // ��� ��� ǥ��; // �ϴ� ��� ǥ��
}
