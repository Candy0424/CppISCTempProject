#include "GameScene.h"
#include "Console.h"
#include <fcntl.h>
#include <io.h>

GameScene::GameScene()
    : width(0), height(0), currentTime(0.0f),
    nodeManager(80, 31, 32), nodeRenderer(80, 31, 2)
{
    prevTime = clock();
}

void GameScene::Init(Player* player, SOUNDID songId)
{
    system("cls");
    curSongId = songId;
    const SongInfo& info = g_songTable[static_cast<int>(songId)];
    COORD res = GetConsoleResolution();
    width = res.X;
    height = res.Y;
    nodeManager.Init(player);
    nodeManager.LoadChart(info.chartPath);
    PlaySoundID(songId, true);
    SetCursorVisual(false, 1);
    currentTime = 0.0f;
    judgeState[0] = judgeState[1] = false;
}
void GameScene::Update(Player* player)
{
    /*clock_t now = clock();
    float deltaTime = float(now - prevTime) / CLOCKS_PER_SEC;
    prevTime = now;*/

    currentTime += 0.0166666666666667f /*deltaTime*/;
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

    if (!judgeState[0]) player->GetNode(1)->tileState = Tile::INPUT_NODE;
    if (!judgeState[1]) player->GetNode(2)->tileState = Tile::INPUT_NODE;

    nodeManager.Update(currentTime);

    auto& nodes = const_cast<std::vector<Node>&>(nodeManager.GetNodes());
    for (auto& node : nodes) {
        if (!node.active && node.prevActive && !node.isHit) {
            nodeRenderer.RegisterJudgeMsg(node.lane, JudgeResult::MISS, 30);
            node.prevActive = false;
        }
    }

    nodeRenderer.UpdateJudgeMsg();
}

void GameScene::Render(Player* player)
{
    static int previousLife = 0;

	COORD res = GetConsoleResolution();

    int curLife = player->GetCurrentLife();
    if (previousLife != curLife)
    {
	    int maxLife = player->GetMaxLife();
        IsGotoxy(res.X / 2, 1);
        for (int i = 1; i <= maxLife; ++i)
        {
            if (i <= curLife)
                cout << "■";
            else
			    cout << "□";
        }
		previousLife = curLife;
    }

    nodeRenderer.Render(nodeManager.GetNodes(), judgeState, nodeManager.GetJudgeLineX(), nodeManager);

    auto upperNode = player->GetNode(1);
    auto downperNode = player->GetNode(2);



    IsGotoxy(upperNode->position.x, upperNode->position.y);
    std::cout << (upperNode->tileState == Tile::OUTPUT_NODE ? "●" : "○");

    IsGotoxy(downperNode->position.x, downperNode->position.y);
    std::cout << (downperNode->tileState == Tile::OUTPUT_NODE ? "●" : "○");

    IsGotoxy(player->position.x, player->position.y);
    int previous = _setmode(_fileno(stdout), _O_U8TEXT);
    std::wcout << L"🎤";
    _setmode(_fileno(stdout), previous);

    judgeState[0] = judgeState[1] = false;
    SetCursorVisual(false, 1);
}
