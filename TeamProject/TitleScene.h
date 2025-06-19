#pragma once
#include "Enums.h"
#include "Console.h"
#include <vector>
#include <string>

class TitleScene
{
public:
    TitleScene();
    ~TitleScene();

    void Init();
    void Update(Scene& curScene);
    void Render();

private:
    void RenderAsciiTitle();
    void RenderMenu();
    void RenderScrollBars();

    std::vector<std::wstring> titleLines;
    int titleScrollX;
    int scrollBarWidth;

    int selectedIdx;
    int menuYStart;
    bool upPrev, downPrev, enterPrev;
};
