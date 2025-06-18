#pragma once
#include "San232Scene.h"

class TitleScene
{
public:
    TitleScene();
    ~TitleScene();
    void Init();
    void Update();
    void Render();
    int GetNextScene() const;

private:
    int selectedIdx;
    int topBarOffset;
    int botBarOffset;
    int barLen;
    int barMoveDir;
    bool upPrev, downPrev, enterPrev;
    int nextScene;
};
