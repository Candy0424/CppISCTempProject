#pragma once
#include "Scene.h"
#include "San232Scene.h"
#include "Console.h"
#include "NodeScroll.h"
#include "InputManager.h"
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
    SceneScript* scene;
    bool judgeState[2];
    float currentTime;
    int width, height;
};
