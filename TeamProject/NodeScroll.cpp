#include "NodeScroll.h"
#include "SettingManager.h"
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstdlib>

NodeManager::NodeManager(int areaWidth, int areaHeight, int maxNodeCount, int nodeSpeed)
    : areaWidth(areaWidth), areaHeight(areaHeight), laneCount(2), nodeSpeed(nodeSpeed), maxNodeCount(maxNodeCount)
{
    judgeLineX = 10;
    startX = areaWidth - 2;
    nodePool.resize(maxNodeCount);
    moveDuration = float(startX - judgeLineX) / float(nodeSpeed) / 60;
}

void NodeManager::Init(Player* player)
{
    playerPtr = player;
    nodePool.clear();
    nodePool.resize(maxNodeCount);
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
    auto& cfg = SettingManager::GetInstance()->GetConfig();
    int symbolCount = (cfg.symbolType == NodeSymbolType::CLASSIC) ? cfg.classicSymbols.size() : cfg.alternateSymbols.size();

    while (nextChartIdx < chart.size() && currentTime >= chart[nextChartIdx].spawnTime) {
        for (auto& node : nodePool) {
            if (!node.active) {
                int y = LaneToY(chart[nextChartIdx].lane);
                int symbolIdx = (symbolCount > 0) ? rand() % symbolCount : 0;
                node.Activate(chart[nextChartIdx].spawnTime, chart[nextChartIdx].lane, startX, y, symbolIdx);
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
        if (node.x < judgeLineX - 5 && !node.isHit) {
            node.Deactivate();
        }
        else if (node.isHit) {
            node.Deactivate();
        }
    }
}

JudgeResult NodeManager::Judge(int lane)
{
    Node* node = GetNearestJudgeableNode(lane, 5);
    if (!node) return JudgeResult::NONE;
    int diff = std::abs(node->x - judgeLineX);
    if (diff <= 1) { HitNode(node); return JudgeResult::PERFECT; }
    if (diff <= 3) { HitNode(node); return JudgeResult::GOOD; }
    if (diff <= 5) { HitNode(node); return JudgeResult::BAD; }
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

 std::vector<Node>& NodeManager::GetNodes()  { return nodePool; }
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

bool NodeManager::IsAllNotesFinished() const
{
    if (nextChartIdx < chart.size())
        return false;
    for (const auto& node : nodePool)
        if (node.active)
            return false;
    return true;
}
