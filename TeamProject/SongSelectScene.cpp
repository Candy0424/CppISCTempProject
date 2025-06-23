#include "SongSelectScene.h"
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include "Console.h"

SongSelectScene::SongSelectScene()
    : selectedIdx(0), upPrev(false), downPrev(false), enterPrev(false)
{
}

void SongSelectScene::Init()
{
    system("cls");
    Sleep(1);
}

void SongSelectScene::Update(Scene& curScene, SOUNDID& selectedSongId)
{
    bool up = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
    bool down = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
    bool enter = (GetAsyncKeyState(VK_RETURN) & 0x8000) != 0;

    int songCount = (int)g_songTable.size();
    if (up && !upPrev)   selectedIdx = (selectedIdx + songCount - 1) % songCount;
    if (down && !downPrev) selectedIdx = (selectedIdx + 1) % songCount;

    if (enter && !enterPrev) {
        selectedSongId = g_songTable[selectedIdx].id;
        curScene = Scene::GAME;
    }
    upPrev = up; downPrev = down; enterPrev = enter;
}

void SongSelectScene::Render()
{
    int y = 10;
    int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);
    for (size_t i = 0; i < g_songTable.size(); ++i)
    {
        Gotoxy(20, y + i * 2);
        if (selectedIdx == (int)i)
            wcout << L">  " << g_songTable[i].title;
        else
            wcout << L"  " << g_songTable[i].title;
    }
    _setmode(_fileno(stdout), prevmode);
}
