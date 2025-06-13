#include "NodeScroll.h"
#include <fstream>
#include <iostream>
#include "Console.h"

NodeScroll::NodeScroll(int playAreaWidth, int laneCount, int startX, int maxNodeCount)
    : areaWidth(playAreaWidth), laneCount(laneCount), startX(startX) {
    judgeLineX = areaWidth - 5;
    nodePool.resize(maxNodeCount);
}

void NodeScroll::LoadChart(const std::string& filename) {
    chart.clear();
    nextChartIdx = 0;
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "채보 파일 오픈 실패: " << filename << std::endl;
        return;
    }
    float t; int lane;
    while (fin >> t >> lane) {
        chart.push_back({ t, lane });
    }
    fin.close();
}

void NodeScroll::Update(float currentTime) {
    while (nextChartIdx < chart.size() && currentTime >= chart[nextChartIdx].spawnTime) {
        bool activated = false;
        for (auto& node : nodePool) {
            if (!node.active) {
                int y = LaneToY(chart[nextChartIdx].lane);
                node.Activate(chart[nextChartIdx].spawnTime, chart[nextChartIdx].lane, startX, y);
                activated = true;
                break;
            }
        }
        ++nextChartIdx;
    }

    for (auto& node : nodePool) {
        if (!node.active) continue;
        node.x += 1;
        if (node.x > areaWidth || node.isHit) {
            node.Deactivate();
        }
    }
}

void NodeScroll::Render() const {
    for (const auto& node : nodePool) {
        if (!node.active) continue;
        SetColor(COLOR::YELLOW);
        Gotoxy(node.x, node.y);
        std::cout << "●";
        SetColor(COLOR::WHITE);
    }
}

Node* NodeScroll::GetJudgeableNode(int lane) {
    for (auto& node : nodePool) {
        if (node.active && node.lane == lane && node.x == judgeLineX && !node.isHit)
            return &node;
    }
    return nullptr;
}

void NodeScroll::HitNode(Node* node) {
    if (node) node->isHit = true;
}

int NodeScroll::LaneToY(int laneIndex) const {
    return 5 + laneIndex * 2;
}
