#include "GameScene.h"
#include "Enums.h"
#include "Console.h"
#include "NodeScroll.h"
#include "InputManager.h"
#include <io.h>
#include <fcntl.h>
#include <iostream>

GameScene::GameScene()
    : width(0), height(0), currentTime(0.0f)
{
    judgeState[0] = judgeState[1] = false;
}

void GameScene::Init(Player* player)
{
    system("cls");
    COORD res = GetConsoleResolution();
    width = res.X;
    height = res.Y;
    NodeManager::GetInstance(width, height, 32)->LoadChart("Chart.txt");
    SetCursorVisual(false, 1);
    currentTime = 0.0f;
    judgeState[0] = judgeState[1] = false;
}

void GameScene::Update(Player* player)
{
    currentTime += 0.016f;
    InputManager::GetInstance()->Update(judgeState, player);
    NodeManager::GetInstance()->Update(currentTime);
}

void GameScene::Render(Player* player)
{
    Gotoxy(0, 0);
    NodeManager::GetInstance()->Render(judgeState);

    auto upperNode = player->GetNode(1);
    auto downperNode = player->GetNode(2);

    IsGotoxy(upperNode->position.x, upperNode->position.y);
    std::cout << (upperNode->tileState == Tile::OUTPUT_NODE ? "●" : "○");

    IsGotoxy(downperNode->position.x, downperNode->position.y);
    std::cout << (downperNode->tileState == Tile::OUTPUT_NODE ? "●" : "○");

	IsGotoxy(player->position.x, player->position.y);
	int previous = _setmode(_fileno(stdout), _O_U8TEXT);
    std::wcout << L"🎤";
    previous = _setmode(_fileno(stdout), previous);

    judgeState[0] = judgeState[1] = false;
    SetCursorVisual(false, 1);
}
