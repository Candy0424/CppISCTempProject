#include "GameScene.h"
#include "Console.h"
#include <fcntl.h>
#include <io.h>

GameScene::GameScene()
    : width(0), height(0), currentTime(0.0f),
    nodeManager(80, 31, 32, 1), nodeRenderer(80, 31, 2)
{
}

void GameScene::Init(Player* player, SOUNDID songId)
{
    ReleaseAllSounds();
    InitAllSounds();
    nodeRenderer.Init(nodeManager);
    initPlayer = false;
    system("cls");
    player->InitPlayer(40);
    curSongId = songId;
    const SongInfo& info = g_songTable[static_cast<int>(songId)];
    COORD res = GetConsoleResolution();
    width = res.X;
    height = res.Y;
    nodeManager.Init(player);
    nodeManager.LoadChart(info.chartPath);
    PlaySoundID(songId, true);
    SetCursorVisual(false, 1);
    t_start = std::chrono::steady_clock::now();
    currentTime = 0.0f;
    judgeState[0] = judgeState[1] = false;
    initPlayer = true;
    combo.ClearCombo();
    score.Init();
}

void GameScene::Update(Player* player, Scene& curScene, Score& setScore, Combo& setCombo)
{
    setScore = score;
    setCombo = combo;
    if (nodeManager.IsAllNotesFinished())
    {
        CloseMciDeviceID(curSongId);
        curScene = Scene::GAME_CLEAR;
    }

    if (player->GetCurrentLife() <= 0 && initPlayer)
    {
        CloseMciDeviceID(curSongId);
        curScene = Scene::GAME_OVER;
    }
    combo.FiverCheck(currentTime);
    combo.FiverCool(currentTime);
    bool fiver = combo.GetFiver();

    auto t_now = std::chrono::steady_clock::now();
    currentTime = std::chrono::duration<float>(t_now - t_start).count();

    InputManager::GetInstance()->Update(judgeState, [this, player](int lane) {
        if (lane == 0) {
            PlayerNode* node = player->GetNode(1);
            if (node->tileState != Tile::OUTPUT_NODE) {
                node->tileState = Tile::OUTPUT_NODE;
                nodeOneCanJudge = true;
            }
            else {
                nodeOneCanJudge = false;
            }
        }
        else if (lane == 1) {
            PlayerNode* node = player->GetNode(2);
            if (node->tileState != Tile::OUTPUT_NODE) {
                node->tileState = Tile::OUTPUT_NODE;
                nodeTwoCanJudge = true;
            }
            else {
                nodeTwoCanJudge = false;
            }
        }

        JudgeResult jr = JudgeResult::NONE;

        if ((nodeOneCanJudge && lane == 0) || (nodeTwoCanJudge && lane == 1)) {
            jr = nodeManager.Judge(lane);
            if (jr == JudgeResult::MISS || jr == JudgeResult::BAD)
            {
                combo.ClearCombo();
            }
            else if (jr != JudgeResult::NONE)
            {
                combo.AddCombo(1);
            }

            if (combo.GetFiver() && jr == JudgeResult::MISS) {
                jr = JudgeResult::GOOD;
            }

            player->PlayerHeal(jr);
            score.AddScore(jr);
            score.RecordJudge(jr);
        }
        if (jr != JudgeResult::NONE)
            nodeRenderer.RegisterJudgeMsg(lane, jr, 30);
        });

    if (!judgeState[0]) player->GetNode(1)->tileState = Tile::INPUT_NODE;
    if (!judgeState[1]) player->GetNode(2)->tileState = Tile::INPUT_NODE;

    nodeManager.Update(currentTime);

    auto& nodes = const_cast<std::vector<Node>&>(nodeManager.GetNodes());
    for (auto& node : nodes) {
        if (!node.active && node.prevActive && !node.isHit) {
            JudgeResult jr = fiver ? JudgeResult::GOOD : JudgeResult::MISS;
            nodeRenderer.RegisterJudgeMsg(node.lane, jr, 30);
            if (fiver) {
                player->PlayerHeal(jr);
                score.AddScore(jr);
                combo.AddCombo(1);
            }
            else {
                player->PlayerHit(4);
                combo.ClearCombo();
            }
            score.RecordJudge(jr);
            node.prevActive = false;
        }
    }

    nodeRenderer.UpdateJudgeMsg();
}

void GameScene::Render(Player* player)
{
    COORD res = GetConsoleResolution();

    int curLife = player->GetCurrentLife();
    int maxLife = player->GetMaxLife();

    unsigned int fiverGage = combo.GetMaxFiverGage();
    unsigned int curFiverGate = combo.GetCurrentFiverGage();

    IsGotoxy(2, 1);
    int previous1 = _setmode(_fileno(stdout), _O_U16TEXT);
    for (int i = 1; i <= maxLife; ++i) {
        if (i <= curLife) {
            SetColor(COLOR::RED);
            wcout << L"█";
        }
        else {
            SetColor(COLOR::GRAY);
            wcout << L"█";
        }
    }
    
    SetColor(COLOR::WHITE);

    IsGotoxy(2, 4);
    for (int i = 1; i <= fiverGage; ++i)
    {
        if (i <= curFiverGate) {
            SetColor(COLOR::WHITE);
            wcout << L"█";
        }
        else {
            SetColor(COLOR::GRAY);
            wcout << L"█";
        }
    }

    SetColor(COLOR::WHITE);
    _setmode(_fileno(stdout), previous1);

    nodeRenderer.Render(nodeManager.GetNodes(), judgeState, nodeManager.GetJudgeLineX(), nodeManager);

    auto upperNode = player->GetNode(1);
    auto downperNode = player->GetNode(2);

    bool isFiver = combo.GetFiver();

    if (isFiver)
    {
        COLOR color = player->rainbowNode();
        SetColor(color);
    }
    else
        player->ColorInit();

    IsGotoxy(upperNode->position.x, upperNode->position.y);    
    std::cout << (upperNode->tileState == Tile::OUTPUT_NODE ? "●" : "○");
    IsGotoxy(downperNode->position.x, downperNode->position.y);
    std::cout << (downperNode->tileState == Tile::OUTPUT_NODE ? "●" : "○");

    IsGotoxy(player->position.x, player->position.y);
    int previous2 = _setmode(_fileno(stdout), _O_U8TEXT);
    std::wcout << L"🎤";
    _setmode(_fileno(stdout), previous2);

    SetColor(COLOR::WHITE);


    judgeState[0] = judgeState[1] = false;

    int curScore = score.GetCurrentScore();
    IsGotoxy(res.X / 10 * 7, 1);
    cout << "Score : " << curScore;

    int curCombo = combo.GetCurrentCombo();
    int clearNum = combo.GetCrrentClearNum();
    for (int i = 1; i <= clearNum; ++i) {
        IsGotoxy(res.X / 3 + i, res.Y / 2);
        std::cout << ' ';
    }
    IsGotoxy(res.X / 3, res.Y / 2);
    std::cout << curCombo;
    combo.ClearNum();

    SetCursorVisual(false, 1);
}
