#pragma once
#include <vector>
#include <string>
#include "Node.h"
#include "Enums.h"

struct NoteChartInfo {
    float spawnTime;
    int lane;
};

class NodeManager {
public:
    NodeManager(int playAreaWidth, int playAreaHeight, int maxNodeCount);
    void LoadChart(const std::string& filename);
    void Update(float currentTime);
    void Render(const bool judgeState[2]);
    JudgeResult Judge(int lane);
    Node* GetNearestJudgeableNode(int lane);
    void HitNode(Node* node);
    int LaneToY(int laneIndex) const;
    int judgeLineX;
    int startX;
private:
    std::vector<Node> nodePool;
    std::vector<NoteChartInfo> chart;
    int areaWidth, areaHeight, laneCount;
    int nextChartIdx = 0;
};
