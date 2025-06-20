#include "NodeScroll.h"
#include <fstream>
#include <iostream>
#include "Console.h"
#undef max
#undef min
#include <algorithm>



NodeManager* NodeManager::instance = nullptr;

NodeManager* NodeManager::GetInstance(int width, int height, int maxNodeCount) {
    if (!instance)
        instance = new NodeManager(width, height, maxNodeCount);
    return instance;
}

void NodeManager::DestroyInstance() {
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

NodeManager::NodeManager(int playAreaWidth, int playAreaHeight, int maxNodeCount)
    : areaWidth(playAreaWidth), areaHeight(playAreaHeight), laneCount(2)
{
    //int centerX = areaWidth / 2;
    judgeLineX = 10;
    startX = areaWidth - 2;
    nodePool.resize(maxNodeCount);
    mapBuffer.resize(areaHeight, std::vector<Tile>(areaWidth, Tile::SPACE));
}
NodeManager::~NodeManager() {}

void NodeManager::LoadChart(const std::string& filename) {
    chart.clear();
    nextChartIdx = 0;
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "채보 파일을 열 수 없습니다. 이름을 확인하세요 " << filename << std::endl;
        return;
    }
    float t; int lane;
    while (fin >> t >> lane) {
        chart.push_back({ t, lane });
    }
    fin.close();
}

void NodeManager::Update(float currentTime) {
    while (nextChartIdx < chart.size() && currentTime >= chart[nextChartIdx].spawnTime) {
        for (auto& node : nodePool) {
            if (!node.active) {
                int y = LaneToY(chart[nextChartIdx].lane);
                node.Activate(chart[nextChartIdx].spawnTime, chart[nextChartIdx].lane, startX, y);
                break;
            }
        }
        ++nextChartIdx;
    }
    for (auto& node : nodePool) {
        if (!node.active) continue;
        node.prevX = node.x;
        node.prevY = node.y;
        node.x -= 1;
        if (node.x < judgeLineX - 3 && !node.isHit) {
            RegisterJudgeMsg(node.lane, JudgeResult::MISS, 30);
            node.Deactivate();
        }
        else if (node.x < 0 || node.isHit) {
            node.Deactivate();
        }
    }
    for (int l = 0; l < 2; ++l) {
        for (auto& msg : judgeMsgs[l])
            if (msg.frameLeft > 0) --msg.frameLeft;
        while (!judgeMsgs[l].empty() && judgeMsgs[l].front().frameLeft <= 0)
            judgeMsgs[l].erase(judgeMsgs[l].begin());
    }
}

void NodeManager::FillMapBuffer(const bool judgeState[2]) {
    for (auto& row : mapBuffer) std::fill(row.begin(), row.end(), Tile::SPACE);
    for (int l = 0; l < laneCount; ++l)
        mapBuffer[LaneToY(l)][judgeLineX] = Tile::ROAD;
    for (const auto& node : nodePool) {
        if (node.active && node.x >= 0 && node.x < areaWidth && node.y >= 0 && node.y < areaHeight)
            mapBuffer[node.y][node.x] = Tile::NODE;
    }
}

static void PrintJudgeResult(JudgeResult r) {
    switch (r) {
    case JudgeResult::PERFECT: std::cout << "PERFECT!"; break;
    case JudgeResult::GOOD:    std::cout << "GOOD!"; break;
    case JudgeResult::MISS:    std::cout << "MISS!"; break;
    default: break;
    }
}

void NodeManager::Render(const bool judgeState[2]) {
    FillMapBuffer(judgeState);
    for (int y = 0; y < areaHeight; ++y) {
        Gotoxy(0, y);
        for (int x = 0; x < areaWidth; ++x) {
            switch (mapBuffer[y][x]) {
            case Tile::NODE: std::cout << "●"; break;
            case Tile::SPACE: std::cout << " "; break;
            default: std::cout << " "; break;
            }
        }
    }

    int msgBaseY = LaneToY(0) - 2;
    int msgBaseX0 = judgeLineX + 13;
    int msgBaseX1 = judgeLineX + 13;

    for (size_t i = 0; i < judgeMsgs[0].size(); ++i) {
        if (judgeMsgs[0][i].frameLeft > 0) {
            Gotoxy(msgBaseX0, msgBaseY - (int)i);
            PrintJudgeResult(judgeMsgs[0][i].result);
        }
    }
    for (size_t i = 0; i < judgeMsgs[1].size(); ++i) {
        if (judgeMsgs[1][i].frameLeft > 0) {
            Gotoxy(msgBaseX1, msgBaseY - (int)i);
            PrintJudgeResult(judgeMsgs[1][i].result);
        }
    }
}


Node* NodeManager::GetNearestJudgeableNode(int lane, int judgeRange) {
    Node* best = nullptr;
    int minDiff = 9999;
    for (auto& node : nodePool) {
        if (!node.active || node.lane != lane || node.isHit) continue;
        int diff = std::abs(node.x - judgeLineX);
        if (diff <= judgeRange && diff < minDiff) {
            minDiff = diff;
            best = &node;
        }
    }
    return best;
}

JudgeResult NodeManager::Judge(int lane) {
    Node* node = GetNearestJudgeableNode(lane, 2);
    if (node) {
        int diff = std::abs(node->x - judgeLineX);
        if (diff <= 1) {
            HitNode(node);
            return JudgeResult::PERFECT;
        }
        if (diff == 2) {
            HitNode(node);
            return JudgeResult::GOOD;
        }
    }
    return JudgeResult::NONE;
}


void NodeManager::HitNode(Node* node) {
    if (node) node->isHit = true;
}

int NodeManager::LaneToY(int laneIndex) const {
    if (laneIndex == 0) return 10;
    if (laneIndex == 1) return 15;
    return areaHeight / 2;
}

void NodeManager::RegisterJudgeMsg(int lane, JudgeResult res, int duration) {
    if (res == JudgeResult::NONE) return;
    if (judgeMsgs[lane].size() >= 10)
        judgeMsgs[lane].erase(judgeMsgs[lane].begin());
    judgeMsgs[lane].push_back({ res, duration });
}
