#include "InputManager.h"
#include <Windows.h>
#include "NodeScroll.h"

InputManager* InputManager::instance = nullptr;
InputManager::InputManager() {}

InputManager* InputManager::GetInstance() {
    if (!instance) instance = new InputManager();
    return instance;
}
void InputManager::DestroyInstance() {
    if (instance) { delete instance; instance = nullptr; }
}

void InputManager::Update(bool judgeState[2]) {
    static const int VKList[2][2] = { {'D','F'}, {'J','K'} };
    for (int lane = 0; lane < 2; ++lane) {
        for (int k = 0; k < 2; ++k) {
            if (GetAsyncKeyState(VKList[lane][k]) & 0x8000) {
                judgeState[lane] = true;
                JudgeResult jr = NodeManager::GetInstance()->Judge(lane);
                if (jr == JudgeResult::PERFECT || jr == JudgeResult::GOOD)
                    NodeManager::GetInstance()->RegisterJudgeMsg(lane, jr, 30);
            }
        }
    }
}
