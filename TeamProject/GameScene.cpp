#include "GameScene.h"
#include "Console.h"

GameScene::GameScene()
    : width(0), height(0), currentTime(0.0f),
    nodeManager(100, 20, 32), nodeRenderer(100, 20, 2) {}

void GameScene::Init(Player* player)
{
    system("cls");
    COORD res = GetConsoleResolution();
    width = res.X;
    height = res.Y;
    nodeManager.LoadChart("Chart.txt");
    SetCursorVisual(false, 1);
    currentTime = 0.0f;
    judgeState[0] = judgeState[1] = false;
}

void GameScene::Update(Player* player)
{
    currentTime += 0.016f;
    InputManager::GetInstance()->Update(judgeState, [this, player](int lane) {
        if (lane == 0) {
            player->GetNode(1)->tileState = Tile::OUTPUT_NODE;
        }
        else if (lane == 1) {
            player->GetNode(2)->tileState = Tile::OUTPUT_NODE;
        }

        JudgeResult jr = nodeManager.Judge(lane);
        if (jr != JudgeResult::NONE)
            nodeRenderer.RegisterJudgeMsg(lane, jr, 30);
        });

    // 입력이 해제된 경우, Player 노드 상태 복귀
    if (!judgeState[0]) player->GetNode(1)->tileState = Tile::INPUT_NODE;
    if (!judgeState[1]) player->GetNode(2)->tileState = Tile::INPUT_NODE;

    nodeManager.Update(currentTime);
}

void GameScene::Render(Player* player)
{
    nodeRenderer.Render(nodeManager.GetNodes(), judgeState, nodeRenderer.GetJudgeMsgs(), nodeManager.GetJudgeLineX());

    // 플레이어의 upper, downper 노드 출력
    auto upperNode = player->GetNode(1);
    auto downperNode = player->GetNode(2);

    IsGotoxy(upperNode->position.x, upperNode->position.y);
    std::cout << (upperNode->tileState == Tile::OUTPUT_NODE ? "●" : "○");

    IsGotoxy(downperNode->position.x, downperNode->position.y);
    std::cout << (downperNode->tileState == Tile::OUTPUT_NODE ? "●" : "○");

    judgeState[0] = judgeState[1] = false;
    SetCursorVisual(false, 1);
}
