#pragma once
#include "Player.h"
#include "NodeScroll.h"
#include "NodeRenderer.h"
#include "InputManager.h"
#include "SongTable.h"
#include "Mci.h"
#include <chrono>
#include "Combo.h"

class GameScene {
public:
    GameScene();
    void Init(Player* player, SOUNDID songId);
    void Update(Player* player, Scene& curScene);
    void Render(Player* player);
private:
    int width, height;
    float currentTime;
    bool judgeState[2];
    bool initPlayer = false;
    bool nodeOneCanJudge, nodeTwoCanJudge;
    clock_t prevTime;
    NodeManager nodeManager;
    NodeRenderer nodeRenderer;
    SOUNDID curSongId;
    Combo combo;
};
