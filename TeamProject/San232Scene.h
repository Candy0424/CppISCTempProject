#pragma once
#include "Scene.h"
#include "NodeScroll.h"
#include "InputManager.h"

class San232Scene : public SceneScript
{
public:
    San232Scene();
    ~San232Scene();
    void Init() override;
    void Update() override;
    void Render() override;
private:
    NodeManager* nodeScroll;
    InputManager* inputManager;
    float currentTime;
    int width, height;
    bool judgeState[2];
};
