#include "NodeScroll.h"
#include <fstream>
#include <algorithm>
#include <cmath>

NodeManager::NodeManager(int areaWidth, int areaHeight, int maxNodeCount, int nodeSpeed)
    : areaWidth(areaWidth), areaHeight(areaHeight), laneCount(2), nodeSpeed(nodeSpeed)
{
    judgeLineX = 10;
    startX = areaWidth - 2;
    nodePool.resize(maxNodeCount);
    moveDuration = float(startX - judgeLineX) / float(nodeSpeed) / 60;

}

void NodeManager::Init(Player* player)
{
    playerPtr = player;
}

void NodeManager::LoadChart(const std::string& filename)
{
    chart.clear();
    nextChartIdx = 0;
    std::ifstream fin(filename);
    if (!fin.is_open()) return;
    float judgeTime;
    int lane;
    while (fin >> judgeTime >> lane)
        chart.push_back({ judgeTime - moveDuration, lane });
    fin.close();
}

void NodeManager::Update(float currentTime)
{
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
        node.x -= nodeSpeed;
        if (node.x < judgeLineX - 3 && !node.isHit) {
            node.Deactivate();
        }
        else if (node.x < 0 || node.isHit) {
            node.Deactivate();
        }
    }
}

JudgeResult NodeManager::Judge(int lane)
{
    Node* node = GetNearestJudgeableNode(lane, 2);
    if (node) {
        int diff = std::abs(node->x - judgeLineX);
        if (diff <= 0) {
            HitNode(node);
            return JudgeResult::PERFECT;
        }
        if (diff <= 2) {
            HitNode(node);
            return JudgeResult::GOOD;
        }
    }
    return JudgeResult::NONE;
}

Node* NodeManager::GetNearestJudgeableNode(int lane, int judgeRange)
{
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

void NodeManager::HitNode(Node* node)
{
    if (node) node->isHit = true;
}

const std::vector<Node>& NodeManager::GetNodes() const { return nodePool; }
int NodeManager::LaneToY(int laneIndex) const
{
    if (playerPtr) {
        if (laneIndex == 0) return playerPtr->GetNode(1)->position.y;
        if (laneIndex == 1) return playerPtr->GetNode(2)->position.y;
    }
    return (laneIndex == 0 ? 25 : 30);
}
int NodeManager::GetJudgeLineX() const { return judgeLineX; }
int NodeManager::GetAreaWidth() const { return areaWidth; }
int NodeManager::GetAreaHeight() const { return areaHeight; }
