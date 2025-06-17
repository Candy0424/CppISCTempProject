#include "InputManager.h"
#include <conio.h>

void InputManager::Update(NodeManager* nodeManager, bool judgeState[2]) {
    if (_kbhit()) {
        char key = _getch();
        int lane = -1;
        switch (key) {
        case 'd': case 'D': lane = 0; break;
        case 'f': case 'F': lane = 1; break;
        }
        if (lane != -1) {
            judgeState[lane] = true;
            nodeManager->Judge(lane);
        }
    }
}
