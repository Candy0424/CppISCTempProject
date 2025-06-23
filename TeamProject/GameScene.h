#pragma once
#include "Player.h"
#include "NodeScroll.h"
#include "NodeRenderer.h"
#include "InputManager.h"
#include <chrono>

class GameScene {
public:
    GameScene();
    void Init(Player* player);
    void Update(Player* player);
    void Render(Player* player);
private:
    int width, height;
    float currentTime;
    bool judgeState[2];
    clock_t prevTime;
    NodeManager nodeManager;
    NodeRenderer nodeRenderer;
};
