#include "TitleScene.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
#include "Enums.h"

static const wchar_t* TITLE[] = {
    L"████████╗██╗   ██╗██████╗ ███████╗    ███████╗ ██████╗ ███╗   ███╗███████╗████████╗██╗  ██╗██╗███╗   ██╗ ██████╗     ",
    L"╚══██╔══╝╚██╗ ██╔╝██╔══██╗██╔════╝    ██╔════╝██╔═══██╗████╗ ████║██╔════╝╚══██╔══╝██║  ██║██║████╗  ██║██╔════╝     ",
    L"   ██║    ╚████╔╝ ██████╔╝█████╗      ███████╗██║   ██║██╔████╔██║█████╗     ██║   ███████║██║██╔██╗ ██║██║  ███╗    ",
    L"   ██║     ╚██╔╝  ██╔═══╝ ██╔══╝      ╚════██║██║   ██║██║╚██╔╝██║██╔══╝     ██║   ██╔══██║██║██║╚██╗██║██║   ██║    ",
    L"   ██║      ██║   ██║     ███████╗    ███████║╚██████╔╝██║ ╚═╝ ██║███████╗   ██║   ██║  ██║██║██║ ╚████║╚██████╔╝    ",
    L"   ╚═╝      ╚═╝   ╚═╝     ╚══════╝    ╚══════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝     ",
};
static const wchar_t* BUTTONS[] = {
    L"게임시작",
    L"게임설정",
    L"나가기",
};

TitleScene::TitleScene()
    : selectedIdx(0), topBarOffset(0), botBarOffset(0), barLen(90), barMoveDir(1),
    upPrev(false), downPrev(false), enterPrev(false), nextScene((int)Scene::TITLE) {}

TitleScene::~TitleScene() {}

void TitleScene::Init() {}

void TitleScene::Update() {
    bool up = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
    bool down = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
    bool enter = (GetAsyncKeyState(VK_RETURN) & 0x8000) != 0;

    if (up && !upPrev) selectedIdx = (selectedIdx + 2) % 3;
    if (down && !downPrev) selectedIdx = (selectedIdx + 1) % 3;

    if (enter && !enterPrev) {
        if (selectedIdx == 0) nextScene = (int)Scene::GAME;
        //else if (selectedIdx == 1) nextScene = (int)Scene::SETTING;
        //else if (selectedIdx == 2) nextScene = (int)Scene::EXIT;
    }

    upPrev = up;
    downPrev = down;
    enterPrev = enter;

    topBarOffset = (topBarOffset + 1) % (barLen + 20);
    botBarOffset = (botBarOffset - 1 + barLen + 20) % (barLen + 20);
}

void TitleScene::Render() {
    system("cls");
    int width = barLen;

    for (int i = 0; i < width; ++i)
        std::wcout << ((i + topBarOffset) % 8 < 4 ? L'=' : L' ');
    std::wcout << std::endl;

    for (auto line : TITLE) std::wcout << line << std::endl;

    std::wcout << std::endl << std::endl;
    for (int i = 0; i < 3; ++i) {
        if (selectedIdx == i) std::wcout << L"> ";
        else std::wcout << L"  ";
        std::wcout << BUTTONS[i] << std::endl;
    }

    for (int i = 0; i < width; ++i)
        std::wcout << ((i + botBarOffset) % 8 < 4 ? L'=' : L' ');
    std::wcout << std::endl;
}

int TitleScene::GetNextScene() const { return nextScene; }
