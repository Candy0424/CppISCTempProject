#include "SettingScene.h"
#include <Windows.h>
#include <algorithm>
#include <io.h>
#include <fcntl.h>

SettingScene::SettingScene()
    : selectedMenu(0), upPrev(false), downPrev(false), leftPrev(false), rightPrev(false), enterPrev(false)
{
    symbolTypeCount = 2;
    colorCandidates = { COLOR::YELLOW, COLOR::RED, COLOR::GREEN, COLOR::SKYBLUE, COLOR::VOILET, COLOR::WHITE };
    colorNames = { L"YELLOW     ", L"RED      ", L"GREEN       ", L"SKYBLUE      ", L"VOILET      ", L"WHITE     " };
    colorCount = static_cast<int>(colorCandidates.size());
}

void SettingScene::Init()
{
	system("cls");
	Sleep(100);
}

void SettingScene::Update(Scene& curScene)
{
    bool up = (GetAsyncKeyState(VK_UP) & 0x8000) != 0;
    bool down = (GetAsyncKeyState(VK_DOWN) & 0x8000) != 0;
    bool left = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
    bool right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;
    bool enter = (GetAsyncKeyState(VK_RETURN) & 0x8000) != 0;

    auto* config = &SettingManager::GetInstance()->GetConfig();

    if (up && !upPrev)         selectedMenu = (selectedMenu + 2) % 3;
    else if (down && !downPrev)selectedMenu = (selectedMenu + 1) % 3;

    if (left && !leftPrev) {
        if (selectedMenu == 0) {
            int typeIdx = static_cast<int>(config->symbolType);
            typeIdx = (typeIdx + symbolTypeCount - 1) % symbolTypeCount;
            config->symbolType = static_cast<NodeSymbolType>(typeIdx);
        }
        if (selectedMenu == 1) {
            int idx = 0;
            for (int i = 0; i < colorCount; ++i)
                if (config->nodeColor == colorCandidates[i]) idx = i;
            idx = (idx + colorCount - 1) % colorCount;
            config->nodeColor = colorCandidates[idx];
        }
    }
    if (right && !rightPrev) {
        if (selectedMenu == 0) {
            int typeIdx = static_cast<int>(config->symbolType);
            typeIdx = (typeIdx + 1) % symbolTypeCount;
            config->symbolType = static_cast<NodeSymbolType>(typeIdx);
        }
        if (selectedMenu == 1) {
            int idx = 0;
            for (int i = 0; i < colorCount; ++i)
                if (config->nodeColor == colorCandidates[i]) idx = i;
            idx = (idx + 1) % colorCount;
            config->nodeColor = colorCandidates[idx];
        }
    }
    if (enter && !enterPrev) {
        if (selectedMenu == 2)
            curScene = Scene::TITLE;
    }

    upPrev = up;
    downPrev = down;
    leftPrev = left;
    rightPrev = right;
    enterPrev = enter;
}

void SettingScene::Render()
{
    int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);
    // 출력 코드

    auto& config = SettingManager::GetInstance()->GetConfig();
    std::wstring menuList[3] = {
        L"노드 타입: " + std::wstring(config.symbolType == NodeSymbolType::CLASSIC ? L"(♬,♫)" : L"(♩,♪)"),
        L"노드 색상: " + colorNames[std::distance(colorCandidates.begin(),
            std::find(colorCandidates.begin(), colorCandidates.end(), config.nodeColor))],
        L"타이틀 화면으로 나가기"
    };
    for (int i = 0; i < 3; ++i) {
        Gotoxy(5, 5 + i * 2);
        if (selectedMenu == i) std::wcout << L"> ";
        else std::wcout << L"  ";
        if (i == 1) SetColor(config.nodeColor);
        std::wcout << menuList[i];
        SetColor(COLOR::WHITE);
    }
    _setmode(_fileno(stdout), prevmode);
}
