#pragma once
#include "Scene.h"
#include "Console.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "SongSelectScene.h"
#include "SongInfo.h"
#include "Enums.h"
#include "Player.h"

class Core
{
public:
    Core();
    ~Core();
    void Run();
private:
    void Init();
    void Update();
    void Render();

    Scene currentScene;
    Scene prevScene;
    TitleScene titleScene;
    SongSelectScene songSelectScene;
    GameScene gameScene;
    Player* player;
    SOUNDID selectedSongId;
};
