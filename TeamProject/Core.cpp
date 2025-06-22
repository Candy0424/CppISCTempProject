#include "Core.h"
#include "Console.h"
#include "NodeScroll.h"
#include "InputManager.h"


Core::~Core()
{
    InputManager::DestroyInstance();
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

Core::Core()
{
    SetConsoleFont(L"Consolas", { 8, 14 }, FW_NORMAL);
    SetConsoleSettings(740, 500, false, L"Type Something");
    SetLockResize();
    currentScene = Scene::TITLE;
    prevScene = Scene::TITLE;
    player = Player::GetInstance();
    player->InitPlayer(3); // Ã¼·Â 3
}

void Core::Init()
{
    switch (currentScene)
    {
    case Scene::TITLE:
        titleScene.Init();
        break;
    case Scene::GAME:
	    gameScene.Init(player);
        break;
    case Scene::SETTING:
        break;
    case Scene::QUIT:
        break;
    case Scene::END:
        break;
    default:
        break;
    }
}

void Core::Update()
{
    if (currentScene != prevScene)
    {
        switch (currentScene)
        {
        case Scene::TITLE:
            titleScene.Init();
            break;
        case Scene::GAME:
            gameScene.Init(player);
            break;
        case Scene::SETTING:
            break;
        case Scene::QUIT:
            break;
        case Scene::END:
            break;
        default:
            break;
        }
    }
    
    prevScene = currentScene;
    
    switch (currentScene)
    {
    case Scene::TITLE:
        titleScene.Update(currentScene);
        break;
    case Scene::GAME:
        gameScene.Update(player);
        break;
    case Scene::SETTING:
        break;
    case Scene::QUIT:
        break;
    case Scene::END:
        break;
    default:
        break;
    }

}

void Core::Render()
{
    switch (currentScene)
    {
    case Scene::TITLE:
        titleScene.Render();
        break;
    case Scene::GAME:
        gameScene.Render(player);
        break;
    case Scene::SETTING:
        break;
    case Scene::QUIT:
        break;
    case Scene::END:
        break;
    default:
        break;
    }
}
