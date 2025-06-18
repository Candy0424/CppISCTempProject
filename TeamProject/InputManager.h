#pragma once
#include "Enums.h"

class InputManager {
public:
    static InputManager* GetInstance();
    static void DestroyInstance();
    void Update(bool judgeState[2]);
private:
    InputManager();
    static InputManager* instance;
};
