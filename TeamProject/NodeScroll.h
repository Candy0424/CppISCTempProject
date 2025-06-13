#pragma once
#include <vector>
#include <string>
#include "Node.h"

struct NoteChartInfo {
    float spawnTime;
    int lane;
};

class NodeManager {
public:
    NodeManager(int playAreaWidth, int laneCount, int startX, int maxNodeCount);

    void LoadChart(const std::string& filename);
    void Update(float currentTime);
    void Render() const;

    Node* GetJudgeableNode(int lane);
    void HitNode(Node* node);

    int LaneToY(int laneIndex) const;
    int judgeLineX;

private:
    std::vector<Node> nodePool;
    std::vector<NoteChartInfo> chart;
    int areaWidth, laneCount, startX;
    int nextChartIdx = 0;
};
