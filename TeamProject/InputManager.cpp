#include "InputManager.h"
#include <Windows.h>

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() {}

InputManager* InputManager::GetInstance() {
    if (!instance) instance = new InputManager();
    return instance;
}

void InputManager::DestroyInstance() {
    if (instance) { delete instance; instance = nullptr; }
}

void InputManager::Update(bool judgeState[2], std::function<void(int)> onJudgeLane)
{
    if ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState('F') & 0x8000)) {
        judgeState[0] = true;
        onJudgeLane(0);
    }
    if ((GetAsyncKeyState('J') & 0x8000) || (GetAsyncKeyState('K') & 0x8000)) {
        judgeState[1] = true;
        onJudgeLane(1);
    }
}
