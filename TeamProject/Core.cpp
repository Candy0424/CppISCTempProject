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
    player = Player::GetInstance();
	player->InitPlayer(3); // Ã¼·Â 3

    if (scene) scene->Init();
    
	gameScene.Init(player);
}

void Core::Update()
{
    if (scene) scene->Update();

	gameScene.Update(player);
}

void Core::Render()
{
    if (scene) scene->Render();

	gameScene.Render(player);
}
