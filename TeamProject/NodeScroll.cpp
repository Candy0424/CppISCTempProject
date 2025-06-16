#include "NodeScroll.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include "Console.h"

NodeManager::NodeManager(int playAreaWidth, int playAreaHeight, int maxNodeCount)
    : areaWidth(playAreaWidth), areaHeight(playAreaHeight), laneCount(2)
{
    int centerX = areaWidth / 2;
    judgeLineX = centerX - 20;
    startX = areaWidth - 2;
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
        Gotoxy(node.x, node.y); std::cout << " ";
        node.prevX = node.x;
        node.prevY = node.y;
        node.x -= 1;
        if (node.x < judgeLineX - 1 && !node.isHit) {
            node.Deactivate();
        }
        else if (node.x < 0 || node.isHit) {
            node.Deactivate();
        }
    }
}

void NodeManager::Render(const bool judgeState[2]) {
    int y0 = LaneToY(0);
    int y1 = LaneToY(1);
    Gotoxy(judgeLineX, y0); std::cout << (judgeState[0] ? "★" : "◆");
    Gotoxy(judgeLineX, y1); std::cout << (judgeState[1] ? "★" : "◆");
    for (const auto& node : nodePool) {
        if (!node.active) continue;
        Gotoxy(node.x, node.y); std::cout << "●";
    }
}

Node* NodeManager::GetNearestJudgeableNode(int lane) {
    Node* best = nullptr;
    int minDiff = 9999;
    for (auto& node : nodePool) {
        if (!node.active || node.lane != lane || node.isHit) continue;
        int diff = std::abs(node.x - judgeLineX);
        if (diff <= 1 && diff < minDiff) {
            minDiff = diff;
            best = &node;
        }
    }
    return best;
}

JudgeResult NodeManager::Judge(int lane) {
    Node* node = GetNearestJudgeableNode(lane);
    if (node) {
        int diff = std::abs(node->x - judgeLineX);
        HitNode(node);
        if (diff == 0) return JudgeResult::PERFECT;
        if (diff == 1) return JudgeResult::GOOD;
    }
    return JudgeResult::MISS;
}

void NodeManager::HitNode(Node* node) {
    if (node) node->isHit = true;
}

int NodeManager::LaneToY(int laneIndex) const {
    int centerY = areaHeight / 2;
    if (laneIndex == 0) return centerY - 1;
    if (laneIndex == 1) return centerY + 1;
    return centerY;
}
