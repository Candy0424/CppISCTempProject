#pragma once
#include "Enums.h"
#include "Player.h"

class InputManager {
public:
    static InputManager* GetInstance();
    static void DestroyInstance();
    void Update(bool judgeState[2], Player* player);
private:
    InputManager();
    static InputManager* instance;
};
