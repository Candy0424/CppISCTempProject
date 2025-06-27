#include "Core.h"
#include "Console.h"

Core::Core()
{
    SetConsoleFont(L"Consolas", { 8, 14 }, FW_NORMAL);
    SetConsoleSettings(740, 500, false, L"Type Something");
    SetLockResize();
    currentScene = Scene::TITLE;
    prevScene = Scene::TITLE;
    player = Player::GetInstance();
    selectedSongId = SOUNDID::END;
    InitAllSounds();
}

Core::~Core()
{
    Player::DestroyInstance();
    ReleaseAllSounds();
}

void Core::Run()
{
    bool isRunning = true;
    while (isRunning)
    {
        Update();
        Render();
        FrameSync(60);
        if (currentScene == Scene::QUIT)
            isRunning = false;
    }
}

void Core::Init()
{
    switch (currentScene)
    {
    case Scene::TITLE: titleScene.Init(); break;
    case Scene::SONG_SELECT: songSelectScene.Init(); break;
	case Scene::SETTING: settingScene.Init(); break;
    case Scene::GAME: gameScene.Init(player, selectedSongId); break;
    case Scene::GAME_OVER: gameOverScene.Init(); break;
    case Scene::GAME_CLEAR: gameClearScene.Init(score); break;
    default: break;
    }
}

void Core::Update()
{
    if (currentScene != prevScene)
        Init();
    prevScene = currentScene;

    switch (currentScene)
    {
    case Scene::TITLE:
        titleScene.Update(currentScene);
        break;
    case Scene::SONG_SELECT:
        songSelectScene.Update(currentScene, selectedSongId);
        break;
	case Scene::SETTING:
        settingScene.Update(currentScene);
		break;
    case Scene::GAME:
        gameScene.Update(player, currentScene, score, combo);
        break;
    case Scene::GAME_OVER:
        gameOverScene.Update(currentScene);
        break;
    case Scene::GAME_CLEAR:
        gameClearScene.Update(score);
        break;
    case Scene::QUIT:
        break;
    default: break;
    }
}

void Core::Render()
{
    switch (currentScene)
    {
    case Scene::TITLE:
        titleScene.Render();
        break;
    case Scene::SONG_SELECT:
        songSelectScene.Render();
        break;
	case Scene::SETTING:
        settingScene.Render();
		break;
    case Scene::GAME:
        gameScene.Render(player);
        break;
    case Scene::GAME_OVER:
        gameOverScene.Render();
        break;
    case Scene::GAME_CLEAR:
        gameClearScene.Render(score, combo);
        break;
    default: break;
    }
}
