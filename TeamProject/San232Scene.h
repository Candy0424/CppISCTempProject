#pragma once
#include "Scene.h"

class San232Scene : public SceneScript
{
public:
    San232Scene();
    ~San232Scene();
    void Init() override;
    void Update() override;
    void Render() override;
private:
    float currentTime;
    int width, height;
    bool judgeState[2];
};