#pragma once
#include "Player.h"
#include "NodeScroll.h"
#include "NodeRenderer.h"
#include "InputManager.h"
#include "SongTable.h"
#include "Mci.h"
#include <chrono>
#include "Combo.h"
#include "Score.h"

class GameScene {
public:
    GameScene();
    void Init(Player* player, SOUNDID songId);
    void ClearAnimation();
    void Update(Player* player, Scene& curScene, Score& setScore, Combo& setCombo);
    void Render(Player* player);
private:
    int width, height;
    float currentTime;
    bool judgeState[2];
    bool initPlayer = false;
    bool nodeOneCanJudge, nodeTwoCanJudge;
    NodeManager nodeManager;
    NodeRenderer nodeRenderer;
    SOUNDID curSongId;
    Combo combo;
    Score score;
    std::chrono::steady_clock::time_point t_start;
};
