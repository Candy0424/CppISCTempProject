#pragma once
#include "Enums.h"
#include <functional>

class InputManager {
public:
    static InputManager* GetInstance();
    static void DestroyInstance();
    void Update(bool judgeState[2], std::function<void(int)> onJudgeLane);
private:
    InputManager();
    static InputManager* instance;
};
