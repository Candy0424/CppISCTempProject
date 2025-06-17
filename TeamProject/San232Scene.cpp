#include "San232Scene.h"
#include "Console.h"

San232Scene::San232Scene()
    : nodeScroll(nullptr), inputManager(nullptr), currentTime(0.0f)
{
    
    inputManager = new InputManager();
    judgeState[0] = false; judgeState[1] = false;
}

San232Scene::~San232Scene()
{
    delete nodeScroll;
    delete inputManager;
}

void San232Scene::Init()
{
    SetConsoleSettings(800, 500, false, L"2라인 콘솔 리듬게임");
    COORD res = GetConsoleResolution();
    width = res.X;
    height = res.Y;
    nodeScroll = new NodeManager(width, height, 32);
    SetCursorVisual(false, 1);
    nodeScroll->LoadChart("Chart.txt");
    currentTime = 0.0f;
}

void San232Scene::Update()
{
    currentTime += 0.016f;
    inputManager->Update(nodeScroll, judgeState);
    nodeScroll->Update(currentTime);
}

void San232Scene::Render()
{
    nodeScroll->Render(judgeState);
    judgeState[0] = false;
    judgeState[1] = false;
}
