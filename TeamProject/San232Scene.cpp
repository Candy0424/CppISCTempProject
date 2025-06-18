#include "San232Scene.h"
#include "Console.h"
#include "NodeScroll.h"
#include "InputManager.h"

San232Scene::San232Scene() : currentTime(0.0f) {
    judgeState[0] = false; judgeState[1] = false;
}
San232Scene::~San232Scene() {
    NodeManager::DestroyInstance();
    InputManager::DestroyInstance();
}
void San232Scene::Init() {
    SetConsoleSettings(800, 500, false, L"2라인 콘솔 리듬게임");
    COORD res = GetConsoleResolution();
    width = res.X;
    height = res.Y;
    NodeManager::GetInstance(width, height, 32)->LoadChart("Chart.txt");
    SetCursorVisual(false, 1);
    currentTime = 0.0f;
}
void San232Scene::Update() {
    currentTime += 0.016f;
    InputManager::GetInstance()->Update(judgeState);
    NodeManager::GetInstance()->Update(currentTime);
}
void San232Scene::Render() {
    NodeManager::GetInstance()->Render(judgeState);
    judgeState[0] = judgeState[1] = false;
}
