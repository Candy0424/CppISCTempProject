#pragma once
#include "Player.h"
#include "NodeScroll.h"
#include "NodeRenderer.h"
#include "SettingManager.h"
#include "InputManager.h"
#include "SongTable.h"
#include "Mci.h"
#include <chrono>
#include "Combo.h"
#include "Score.h"

class GameScene {
public:
    GameScene();
    void Init(Player* player, SOUNDID songId);
    void ClearTextRender();
    void Update(Player* player, Scene& curScene, Score& setScore, Combo& setCombo);    
    void Render(Player* player);
private:

    COLOR colors[3]
    {
        COLOR::LIGHT_BLUE,
        COLOR::VOILET,
        COLOR::LIGHT_VIOLET,
    };

    wstring clearText[3]
    {
        L"╔═╗╔═╗╔╦╗╔═╗  ╔═╗╦  ╔═╗╔═╗╦═╗\n",
        L"║ ╦╠═╣║║║║╣   ║  ║  ║╣ ╠═╣╠╦╝\n",
        L"╚═╝╩ ╩╩ ╩╚═╝  ╚═╝╩═╝╚═╝╩ ╩╩╚═\n",
    };

    wstring fullComboText[3]
    {
        L"╔═╗╦ ╦╦ ╦╦  ╦    ╔═╗╔═╗╔╦╗╔╗ ╔═╗\n",
        L"╠╣ ║ ║║ ║║  ║    ║  ║ ║║║║╠╩╗║ ║\n",
        L"╚  ╚═╝╚═╝╩═╝╩═╝  ╚═╝╚═╝╩ ╩╚═╝╚═╝\n",
    };

    wstring allPerfectText[3]
    {
        L"╔═╗╦  ╦    ╔═╗╔═╗╦═╗╔═╗╔═╗╔═╗╔╦╗\n",
        L"╠═╣║  ║    ╠═╝║╣ ╠╦╝╠╣ ║╣ ║   ║\n",
        L"╩ ╩╩═╝╩═╝  ╩  ╚═╝╩╚═╚  ╚═╝╚═╝ ╩\n",
    };


    int width, height;
    float currentTime;
    bool judgeState[2];
    bool initPlayer = false;
    bool nodeOneCanJudge, nodeTwoCanJudge;
    bool endTextAnimation = false;
    bool endGame = false;
    NodeManager nodeManager;
    NodeRenderer nodeRenderer;
    SOUNDID curSongId;
    Combo combo;
    Score score;
    std::chrono::steady_clock::time_point t_start;
};
