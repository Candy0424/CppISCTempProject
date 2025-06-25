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
    int symbolTypeCount;
    int colorCount;
    std::vector<COLOR> colorCandidates;
    std::vector<std::wstring> colorNames;
    bool upPrev, downPrev, leftPrev, rightPrev, enterPrev;
};
