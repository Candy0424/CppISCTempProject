#include "Core.h"
#include "San232Scene.h"
#include "Console.h"

Core::Core()
    : scene(nullptr)
{
    //scene = new San232Scene();
}

Core::~Core()
{
    delete scene;
}

void Core::Run()
{
    Init();
    while (true)
    {
        Update();
        Render();
        FrameSync(60);
    }
}

void Core::Init()
{
    SetConsoleFont(L"Consolas", { 12, 24 }, FW_NORMAL);
    if (scene) scene->Init();
}

void Core::Update()
{
    if (scene) scene->Update();
}

void Core::Render()
{
    if (scene) scene->Render();
}
