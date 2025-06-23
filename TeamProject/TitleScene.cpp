#include "TitleScene.h"
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

static const wchar_t* TITLE[] = {
    L"████████╗██╗   ██╗██████╗ ███████╗    ███████╗ ██████╗ ███╗   ███╗███████╗████████╗██╗  ██╗██╗███╗   ██╗ ██████╗     ",
    L"╚══██╔══╝╚██╗ ██╔╝██╔══██╗██╔════╝    ██╔════╝██╔═══██╗████╗ ████║██╔════╝╚══██╔══╝██║  ██║██║████╗  ██║██╔════╝     ",
    L"   ██║    ╚████╔╝ ██████╔╝█████╗      ███████╗██║   ██║██╔████╔██║█████╗     ██║   ███████║██║██╔██╗ ██║██║  ███╗    ",
    L"   ██║     ╚██╔╝  ██╔═══╝ ██╔══╝      ╚════██║██║   ██║██║╚██╔╝██║██╔══╝     ██║   ██╔══██║██║██║╚██╗██║██║   ██║    ",
    L"   ██║      ██║   ██║     ███████╗    ███████║╚██████╔╝██║ ╚═╝ ██║███████╗   ██║   ██║  ██║██║██║ ╚████║╚██████╔╝    ",
    L"   ╚═╝      ╚═╝   ╚═╝     ╚══════╝    ╚══════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝     ",
};
static const wchar_t* MENUS[] = { L"게임 시작", L"게임 설정", L"나가기" };

TitleScene::TitleScene()
    : titleScrollX(0), scrollBarWidth(100), selectedIdx(0),
    upPrev(false), downPrev(false), enterPrev(false)
{
    for (auto line : TITLE)
        titleLines.push_back(line);
    menuYStart = 20;
}

TitleScene::~TitleScene() {}

void TitleScene::Init() {}

void TitleScene::Update(Scene& curScene)
{
    // 입력(비동기)
    bool up = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
    bool down = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
    bool enter = (GetAsyncKeyState(VK_RETURN) & 0x8000) != 0;

    if (up && !upPrev)   selectedIdx = (selectedIdx + 2) % 3;
    if (down && !downPrev) selectedIdx = (selectedIdx + 1) % 3;

    if (enter && !enterPrev) {
        if (selectedIdx == 0) curScene = Scene::SONG_SELECT;
        else if (selectedIdx == 1) curScene = Scene::SETTING;
        else if (selectedIdx == 2) curScene = Scene::QUIT;
    }
    upPrev = up; downPrev = down; enterPrev = enter;

    titleScrollX = (titleScrollX + 2) % (int)titleLines[0].size();
}

void TitleScene::Render()
{
    Gotoxy(0, 0);
    int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);

    RenderScrollBars();
    RenderAsciiTitle();
    RenderMenu();

    _setmode(_fileno(stdout), prevmode);
}

void TitleScene::RenderAsciiTitle()
{
    int winW = 100;
    int winH = (int)titleLines.size();

    for (int row = 0; row < winH; ++row) {
        Gotoxy(0, row + 2);
        std::wstring& line = titleLines[row];
        int n = (int)line.size();
        for (int col = 0; col < winW; ++col) {
            int idx = (titleScrollX + col) % n;
            wcout << line[idx];
        }
    }
}

void TitleScene::RenderMenu()
{
    int x = 37, y = menuYStart;
    for (int i = 0; i < 3; ++i) {
        Gotoxy(x, y + i * 2);
        if (selectedIdx == i) wcout << L">  " << MENUS[i];
        else wcout << L"  " << MENUS[i];
    }
}

void TitleScene::RenderScrollBars()
{
    // 상단 바 (왼->오)
    Gotoxy(0, 0);
    for (int i = 0; i < scrollBarWidth; ++i)
        wcout << (((i + titleScrollX) % 10 < 5) ? L'=' : L' ');

    // 하단 바 (오->왼)
    Gotoxy(0, menuYStart + 8);
    for (int i = 0; i < scrollBarWidth; ++i)
        wcout << (((i - titleScrollX + 100) % 10 < 5) ? L'=' : L' ');
}
