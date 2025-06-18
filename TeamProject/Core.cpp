#include "Core.h"
#include "San232Scene.h"
#include "Console.h"
#include "NodeScroll.h"
#include "InputManager.h"

Core::Core() : currentTime(0.0f), scene(nullptr)
{

    judgeState[0] = false; judgeState[1] = false;
    scene = new San232Scene();
}

Core::~Core()
{
    NodeManager::DestroyInstance();
    InputManager::DestroyInstance();
    delete scene;
}

void Core::Run()
{
    Init();
    while (true)
    {
        Update();
        Render();
        FrameSync(60);
    }
}

void Core::Init()
{
    SetConsoleFont(L"Consolas", { 12, 24 }, FW_NORMAL);
    SetConsoleSettings(800, 500, false, L"2���� �ܼ� �������");
    COORD res = GetConsoleResolution();
    width = res.X;
    height = res.Y;
    NodeManager::GetInstance(width, height, 32)->LoadChart("Chart.txt");
    SetCursorVisual(false, 1);
    currentTime = 0.0f;
    if (scene) scene->Init();
}

void Core::Update()
{
    currentTime += 0.016f;
    InputManager::GetInstance()->Update(judgeState);
    NodeManager::GetInstance()->Update(currentTime);
    if (scene) scene->Update();
}

void Core::Render()
{
    NodeManager::GetInstance()->Render(judgeState);
    judgeState[0] = judgeState[1] = false;
    if (scene) scene->Render();
}
