#pragma once
#include <vector>
#include <string>
#include "Node.h"
#include "Enums.h"
#include "Player.h"

struct NoteChartInfo {
    float spawnTime;
    int lane;
};

class NodeManager {
public:
    NodeManager(int areaWidth, int areaHeight, int maxNodeCount);
    void Init(Player* player); // Player* 저장
    void LoadChart(const std::string& filename);
    void Update(float currentTime);
    JudgeResult Judge(int lane);
    Node* GetNearestJudgeableNode(int lane, int judgeRange);
    void HitNode(Node* node);
    const std::vector<Node>& GetNodes() const;
    int LaneToY(int laneIndex) const;
    int GetJudgeLineX() const;
    int GetAreaWidth() const;
    int GetAreaHeight() const;
private:
    int areaWidth, areaHeight, laneCount;
    int judgeLineX;
    int startX;
    std::vector<Node> nodePool;
    std::vector<NoteChartInfo> chart;
    int nextChartIdx = 0;
    Player* playerPtr = nullptr; // 추가
};
