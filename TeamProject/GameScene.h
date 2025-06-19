#pragma once
#include "Enums.h"
#include "Player.h"

class GameScene
{
    int width;
    int height;
    float currentTime;
    bool judgeState[2];

public:
    GameScene();
    void Init(Player* player);
    void Update(Player* player);
    void Render(Player* player);
};
