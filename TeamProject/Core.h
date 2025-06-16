#pragma once
#include "Scene.h"
class Core
{
public:
    void Run();
    Core();
    ~Core();
private:
    void Init();
    void Update();
    void Render();
    SceneScript* scene;
};
