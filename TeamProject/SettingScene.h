#pragma once
#include "Scene.h"
#include "Console.h"
#include "SettingManager.h"
#include <vector>
#include <string>

class SettingScene
{
public:
    SettingScene();
    void Init();
    void Update(Scene& curScene);
    void Render();
private:
    int selectedMenu;
    int menuCount;
    int symbolTypeCount;
    int colorCount;
    int playerInstrumentCount;
    int playerColorCount;
    std::vector<COLOR> colorCandidates;
    std::vector<std::wstring> colorNames;
    std::vector<PlayerNodeInstrument> playerInstruments;
    std::vector<std::wstring> playerInstrumentNames;
    std::vector<COLOR> playerColorCandidates;
    std::vector<std::wstring> playerColorNames;
    bool upPrev, downPrev, leftPrev, rightPrev, enterPrev;
};
