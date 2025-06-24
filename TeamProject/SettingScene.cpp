#include "SettingScene.h"
#include <conio.h>
#include <algorithm>

SettingScene::SettingScene()
    : selectedMenu(0)
{
    symbolTypeCount = 2;
    colorCandidates = { COLOR::YELLOW, COLOR::RED, COLOR::GREEN, COLOR::SKYBLUE, COLOR::VOILET, COLOR::WHITE };
    colorNames = { L"YELLOW", L"RED", L"GREEN", L"SKYBLUE", L"VOILET", L"WHITE" };
    colorCount = static_cast<int>(colorCandidates.size());
}

void SettingScene::Init() {}

void SettingScene::Update(Scene& curScene)
{
    int key = 0;
    if (_kbhit()) key = _getch();
    if (key == 224 && _kbhit()) { // 방향키
        int arrow = _getch();
        auto* config = &SettingManager::GetInstance()->GetConfig();
        if (arrow == 72) selectedMenu = (selectedMenu + 2) % 3; // up
        else if (arrow == 80) selectedMenu = (selectedMenu + 1) % 3; // down
        else if (arrow == 75) { // left
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
        else if (arrow == 77) { // right
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
    }
    else if (key == 13) { // Enter
        if (selectedMenu == 2)
            curScene = Scene::TITLE;
    }
}

void SettingScene::Render()
{
    system("cls");
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
        if (i == 1) SetColor(config.nodeColor); // 노드 색상 줄만 적용
        std::wcout << menuList[i];
        SetColor(COLOR::WHITE);
    }
}
