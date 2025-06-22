#pragma once
#include "Player.h"
#include "NodeScroll.h"
#include "NodeRenderer.h"
#include "InputManager.h"

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
    NodeManager nodeManager;
    NodeRenderer nodeRenderer;
};
