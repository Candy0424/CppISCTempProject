#include "NodeRenderer.h"
#include "Console.h"
#include <iostream>
#include <algorithm>

static constexpr int MAX_JUDGE_MSG_LEN = 8;

NodeRenderer::NodeRenderer(int areaWidth, int areaHeight, int laneCount)
    : areaWidth(areaWidth), areaHeight(areaHeight), laneCount(laneCount)
{
    mapBuffer.resize(areaHeight, std::vector<Tile>(areaWidth, Tile::SPACE));
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
    case JudgeResult::MISS:
        SetColor(COLOR::RED);
        std::cout << "MISS!";
        SetColor(COLOR::WHITE);
        break;
    default:
        break;
    }
}

void NodeRenderer::Render(const std::vector<Node>& nodes, const bool judgeState[2], const std::vector<JudgeMsg> judgeMsgs[2], int judgeLineX, const NodeManager& nodeManager)
{
    FillMapBuffer(nodes, areaWidth, areaHeight, laneCount, judgeLineX, nodeManager);
    for (int y = 0; y < areaHeight; ++y) {
        Gotoxy(0, y);
        for (int x = 0; x < areaWidth; ++x) {
            switch (mapBuffer[y][x]) {
            case Tile::NODE: std::cout << "●"; break;
            case Tile::ROAD: std::cout << "━"; break;
            case Tile::SPACE: std::cout << " "; break;
            default: std::cout << " "; break;
            }
        }
    }

    int msgBaseY = nodeManager.LaneToY(0) - 2; // 판정 메시지도 판정라인 기준
    int msgBaseX0 = judgeLineX + 13;
    int msgBaseX1 = judgeLineX + 13;
    for (size_t i = 0; i < judgeMsgs[0].size(); ++i) {
        if (judgeMsgs[0][i].frameLeft > 0) {
            PrintJudgeResult(judgeMsgs[0][i].result, msgBaseX0, msgBaseY - (int)i);
        }
    }
    for (size_t i = 0; i < judgeMsgs[1].size(); ++i) {
        if (judgeMsgs[1][i].frameLeft > 0) {
            PrintJudgeResult(judgeMsgs[1][i].result, msgBaseX1, msgBaseY - (int)i);
        }
    }
}

void NodeRenderer::RegisterJudgeMsg(int lane, JudgeResult res, int duration)
{
    if (res == JudgeResult::NONE) return;
    if (lane < 0 || lane >= laneCount) return;
    if (judgeMsgs[lane].size() >= 10)
        judgeMsgs[lane].erase(judgeMsgs[lane].begin());
    judgeMsgs[lane].push_back({ res, duration });
}

const std::vector<JudgeMsg>* NodeRenderer::GetJudgeMsgs() const
{
    return judgeMsgs;
}
