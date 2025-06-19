#pragma once
#include "Scene.h"
#include "Console.h"
#include "NodeScroll.h"
#include "InputManager.h"
#include "GameScene.h"
#include "TitleScene.h"
class Core
{
public:
    void Run();
    Core();
    ~Core();
private:
    void Init();
    void Update();
    void Render();
    bool judgeState[2];
    float currentTime;
    int width, height;
    TitleScene titleScene;
    GameScene gameScene;
    Scene currentScene;
    Scene prevScene;
    Player* player;
};
