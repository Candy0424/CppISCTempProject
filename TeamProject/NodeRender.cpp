#include "NodeRenderer.h"
#include "Console.h"
#include "SettingManager.h"
#include <iostream>
#include <algorithm>
#include <io.h>
#include <fcntl.h>
#include <cstdlib>

static constexpr int MAX_JUDGE_MSG_LEN = 8;

NodeRenderer::NodeRenderer(int areaWidth, int areaHeight, int laneCount)
    : areaWidth(areaWidth), areaHeight(areaHeight), laneCount(laneCount)
{
    mapBuffer.resize(areaHeight, std::vector<Tile>(areaWidth, Tile::SPACE));
    prevBuffer.resize(areaHeight, std::vector<Tile>(areaWidth, Tile::SPACE));
    judgeMsgs.resize(laneCount);
}

void NodeRenderer::FillMapBuffer(const std::vector<Node>& nodes, int areaWidth, int areaHeight, int laneCount, int judgeLineX, const NodeManager& nodeManager)
{
    for (auto& row : mapBuffer) std::fill(row.begin(), row.end(), Tile::SPACE);
    for (int l = 0; l < areaWidth; ++l) {
        int y = nodeManager.LaneToY(l);
        if (y >= 0 && y < areaHeight)
            mapBuffer[y][judgeLineX] = Tile::ROAD;
    }
    for (const auto& node : nodes) {
        if (node.active && node.x >= 0 && node.x < areaWidth && node.y >= 0 && node.y < areaHeight)
            mapBuffer[node.y][node.x] = Tile::NODE;
    }
}

static void PrintJudgeResult(JudgeResult r, int x, int y) {
    Gotoxy(x, y);
    for (int i = 0; i < MAX_JUDGE_MSG_LEN; ++i)
        std::cout << " ";
    Gotoxy(x, y);
    switch (r) {
    case JudgeResult::PERFECT: {
        COLOR rainbow[7] = {
            COLOR::RED, COLOR::YELLOW, COLOR::GREEN, COLOR::SKYBLUE, COLOR::BLUE, COLOR::VOILET, COLOR::LIGHT_VIOLET
        };
        const char* msg = "PERFECT";
        for (int i = 0; i < 7; ++i) {
            SetColor(rainbow[i]);
            std::cout << msg[i];
        }
        SetColor(COLOR::LIGHT_VIOLET);
        std::cout << "!";
        SetColor(COLOR::WHITE);
        break;
    }
    case JudgeResult::GOOD:
        SetColor(COLOR::BLUE);
        std::cout << "GOOD!";
        SetColor(COLOR::WHITE);
        break;
    case JudgeResult::BAD:
        SetColor(COLOR::GRAY);
        std::cout << "BAD...";
        SetColor(COLOR::WHITE);
        break;
    case JudgeResult::MISS:
        SetColor(COLOR::RED);
        std::cout << "MISS";
        SetColor(COLOR::WHITE);
        break;
    default:
        break;
    }
}

void NodeRenderer::Render(const std::vector<Node>& nodes, const bool judgeState[2], int judgeLineX, const NodeManager& nodeManager)
{
    FillMapBuffer(nodes, areaWidth, areaHeight, laneCount, judgeLineX, nodeManager);
    auto& cfg = SettingManager::GetInstance()->GetConfig();
    std::vector<std::wstring> nodeSymbols =
        (cfg.symbolType == NodeSymbolType::CLASSIC) ? cfg.classicSymbols : cfg.alternateSymbols;

    int prevmode = _setmode(_fileno(stdout), _O_U16TEXT);

    for (int y = 0; y < areaHeight; ++y) {
        for (int x = 0; x < areaWidth; ++x) {
            if (mapBuffer[y][x] != prevBuffer[y][x]) {
                Gotoxy(x, y);
                if (mapBuffer[y][x] == Tile::NODE) {
                    SetColor(cfg.nodeColor);
                    for (const auto& node : nodes) {
                        if (node.active && node.x == x && node.y == y) {
                            std::wstring symbol = nodeSymbols[node.symbolIndex % nodeSymbols.size()];
                            std::wcout << symbol;
                            break;
                        }
                    }
                    SetColor(COLOR::WHITE);
                }
                else {
                    std::wcout << L" ";
                }
            }
        }
    }

    _setmode(_fileno(stdout), prevmode);

    prevBuffer = mapBuffer;

    UpdateJudgeMsg();
    JudgeResult latestResult = JudgeResult::NONE;
    for (const auto& msg : judgeMsgs)
        if (msg.frameLeft > 0)
            latestResult = msg.result;

    int msgBaseY = nodeManager.LaneToY(0) - 2;
    int msgBaseX = judgeLineX + 13;

    if (latestResult != JudgeResult::NONE)
        PrintJudgeResult(latestResult, msgBaseX, msgBaseY);
}

void NodeRenderer::RegisterJudgeMsg(int lane, JudgeResult res, int duration)
{
    if (res == JudgeResult::NONE) return;
    if (lane < 0 || lane >= laneCount) return;
    judgeMsgs[lane].result = res;
    judgeMsgs[lane].frameLeft = duration;
}

void NodeRenderer::UpdateJudgeMsg()
{
    for (auto& msg : judgeMsgs) {
        if (msg.frameLeft > 0) --msg.frameLeft;
        if (msg.frameLeft == 0) msg.result = JudgeResult::NONE;
    }
}

void NodeRenderer::Init(NodeManager& nodeManager)
{
    mapBuffer.clear();
    prevBuffer.clear();
    judgeMsgs.clear();
    mapBuffer.resize(areaHeight, std::vector<Tile>(areaWidth, Tile::SPACE));
    prevBuffer.resize(areaHeight, std::vector<Tile>(areaWidth, Tile::SPACE));
    judgeMsgs.resize(laneCount);

    auto& cfg = SettingManager::GetInstance()->GetConfig();
    std::vector<std::wstring> nodeSymbols =
        (cfg.symbolType == NodeSymbolType::CLASSIC) ? cfg.classicSymbols : cfg.alternateSymbols;

    int symbolCount = nodeSymbols.size();
    if (symbolCount == 0) symbolCount = 1;
    for (auto& node : nodeManager.GetNodes()) {
        if (node.active)
            node.symbolIndex = rand() % symbolCount;
    }
}
