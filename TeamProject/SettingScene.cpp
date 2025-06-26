#include "SettingScene.h"
#include <Windows.h>
#include <algorithm>
#include <io.h>
#include <fcntl.h>
#include "Mci.h"

SettingScene::SettingScene()
    : selectedMenu(0), upPrev(false), downPrev(false), leftPrev(false), rightPrev(false), enterPrev(false)
{
    symbolTypeCount = 2;
    colorCandidates = { COLOR::YELLOW, COLOR::RED, COLOR::GREEN, COLOR::SKYBLUE, COLOR::VOILET, COLOR::WHITE };
    colorNames = { L"YELLOW     ", L"RED      ", L"GREEN       ", L"SKYBLUE      ", L"VOILET      ", L"WHITE     " };
    colorCount = static_cast<int>(colorCandidates.size());

    // Player 커스텀 관련
    playerInstruments = {
        PlayerNodeInstrument::MIC, PlayerNodeInstrument::PIANO, PlayerNodeInstrument::VIOLIN,
        PlayerNodeInstrument::GUITAR, PlayerNodeInstrument::TRUMPET, PlayerNodeInstrument::DRUM
    };
    playerInstrumentNames = { L"🎤 MIC", L"🎹 PIANO", L"🎻 VIOLIN", L"🎸 GUITAR", L"🎺 TRUMPET", L"🥁 DRUM" };
    playerInstrumentCount = static_cast<int>(playerInstruments.size());

    playerColorCandidates = { COLOR::YELLOW, COLOR::RED, COLOR::GREEN, COLOR::SKYBLUE, COLOR::VOILET, COLOR::WHITE };
    playerColorNames = { L"YELLOW     ", L"RED      ", L"GREEN       ", L"SKYBLUE      ", L"VOILET      ", L"WHITE     " };
    playerColorCount = static_cast<int>(playerColorCandidates.size());

    menuCount = 5; // 노드 타입, 노드 색상, 플레이어 모양, 플레이어 색상, 나가기
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
    auto* playerStyle = &SettingManager::GetInstance()->GetPlayerStyle();

    if (up && !upPrev) {
        selectedMenu = (selectedMenu + menuCount - 1) % menuCount;
        PlaySoundID(SOUNDID::CURSOR_SOUND);
    }
    else if (down && !downPrev) {
        selectedMenu = (selectedMenu + 1) % menuCount;
        PlaySoundID(SOUNDID::CURSOR_SOUND);
    }


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
        if (selectedMenu == 2) {
            int instIdx = 0;
            for (int i = 0; i < playerInstrumentCount; ++i)
                if (playerStyle->GetInstrument() == playerInstruments[i]) instIdx = i;
            instIdx = (instIdx + playerInstrumentCount - 1) % playerInstrumentCount;
            playerStyle->SetInstrument(playerInstruments[instIdx]);
        }
        if (selectedMenu == 3) {
            int idx = 0;
            for (int i = 0; i < playerColorCount; ++i)
                if (playerStyle->GetColor() == playerColorCandidates[i]) idx = i;
            idx = (idx + playerColorCount - 1) % playerColorCount;
            playerStyle->SetColor(playerColorCandidates[idx]);
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
        if (selectedMenu == 2) {
            int instIdx = 0;
            for (int i = 0; i < playerInstrumentCount; ++i)
                if (playerStyle->GetInstrument() == playerInstruments[i]) instIdx = i;
            instIdx = (instIdx + 1) % playerInstrumentCount;
            playerStyle->SetInstrument(playerInstruments[instIdx]);
        }
        if (selectedMenu == 3) {
            int idx = 0;
            for (int i = 0; i < playerColorCount; ++i)
                if (playerStyle->GetColor() == playerColorCandidates[i]) idx = i;
            idx = (idx + 1) % playerColorCount;
            playerStyle->SetColor(playerColorCandidates[idx]);
        }
    }
    if (enter && !enterPrev) {
        if (selectedMenu == 4)
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

    auto& config = SettingManager::GetInstance()->GetConfig();
    auto& playerStyle = SettingManager::GetInstance()->GetPlayerStyle();

    std::wstring menuList[5] = {
        L"노드 타입: " + std::wstring(config.symbolType == NodeSymbolType::CLASSIC ? L"(♬,♫)" : L"(♩,♪)"),
        L"노드 색상: " + colorNames[std::distance(colorCandidates.begin(),
            std::find(colorCandidates.begin(), colorCandidates.end(), config.nodeColor))],
        L"플레이어 모양: " + playerInstrumentNames[std::distance(playerInstruments.begin(),
            std::find(playerInstruments.begin(), playerInstruments.end(), playerStyle.GetInstrument()))],
        L"플레이어 색상: " + playerColorNames[std::distance(playerColorCandidates.begin(),
            std::find(playerColorCandidates.begin(), playerColorCandidates.end(), playerStyle.GetColor()))],
        L"타이틀 화면으로"
    };
    for (int i = 0; i < 5; ++i) {
        Gotoxy(5, 5 + i * 2);
        if (selectedMenu == i) std::wcout << L">  ";
        else std::wcout << L"  ";
        if (i == 1) SetColor(config.nodeColor);
        else if (i == 3) SetColor(playerStyle.GetColor());
        std::wcout << menuList[i];
        SetColor(COLOR::WHITE);
    }
    _setmode(_fileno(stdout), prevmode);
}
