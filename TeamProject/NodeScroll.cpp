#include "NodeScroll.h"
#include <fstream>
#include <iostream>
#include "Console.h"

NodeManager::NodeManager(int playAreaWidth, int laneCount, int startX, int maxNodeCount)
    : areaWidth(playAreaWidth), laneCount(laneCount), startX(startX) {
    judgeLineX = 5;
    nodePool.resize(maxNodeCount);
}

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
        bool activated = false;
        for (auto& node : nodePool) {
            if (!node.active) {
                int y = LaneToY(chart[nextChartIdx].lane);
                node.Activate(chart[nextChartIdx].spawnTime, chart[nextChartIdx].lane, areaWidth - 1, y);
                activated = true;
                break;
            }
        }
        ++nextChartIdx;
    }

    for (auto& node : nodePool) {
        if (!node.active) continue;
        node.x -= 1;
        if (node.x < 0 || node.isHit) {
            node.Deactivate();
        }
    }
}

void NodeManager::Render() const {
    for (const auto& node : nodePool) {
        if (!node.active) continue;
        SetColor(COLOR::YELLOW);
        Gotoxy(node.x, node.y);
        std::cout << "●";
        SetColor(COLOR::WHITE);
    }
}

Node* NodeManager::GetJudgeableNode(int lane) {
    for (auto& node : nodePool) {
        if (node.active && node.lane == lane && node.x == judgeLineX && !node.isHit)
            return &node;
    }
    return nullptr;
}

void NodeManager::HitNode(Node* node) {
    if (node) node->isHit = true;
}

int NodeManager::LaneToY(int laneIndex) const {
    return 5 + laneIndex * 2;
}
