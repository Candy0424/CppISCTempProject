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
    Sleep(100);
}

void SongSelectScene::Update(Scene& curScene, SOUNDID& selectedSongId)
{
    bool up = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
    bool down = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
    bool enter = (GetAsyncKeyState(VK_RETURN) & 0x8000) != 0;

    int songCount = (int)g_songTable.size();
    if (up && !upPrev) {
        if (selectedIdx == 0)
            selectedIdx = songCount;
        else
            selectedIdx--;
    }
    if (down && !downPrev) {
        selectedIdx = (selectedIdx + 1) % (songCount + 1);
    }


    if (enter && !enterPrev) {
        if(selectedIdx == songCount) {
            curScene = Scene::TITLE;
            return;
		}
        selectedSongId = g_songTable[selectedIdx].id;
        curScene = Scene::GAME;
    }
    upPrev = up; downPrev = down; enterPrev = enter;
}

void SongSelectScene::Render()
{
    int songCount = (int)g_songTable.size();
    int y = 10;
    int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);
    for (int i = 0; i < songCount + 1; ++i) // songCount+1개
    {
        Gotoxy(20, y + i * 2);
        if (i == songCount) // 마지막은 "타이틀 화면으로"
        {
            if (selectedIdx == i)
                wcout << L">  " << L"타이틀 화면으로";
            else
                wcout << L"  " << L"타이틀 화면으로";
        }
        else // 곡 출력
        {
            if (selectedIdx == i)
                wcout << L">  " << g_songTable[i].title;
            else
                wcout << L"  " << g_songTable[i].title;
        }
    }
    _setmode(_fileno(stdout), prevmode);
}

