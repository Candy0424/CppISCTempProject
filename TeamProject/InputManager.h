#include "Player.h"

class InputManager {
public:
    InputManager();
    void Update(bool judgeState[2], Player* player);
};
