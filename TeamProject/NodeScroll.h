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
    NodeManager(int areaWidth, int areaHeight, int maxNodeCount, int nodeSpeed = 2);
    void Init(Player* player);
    void LoadChart(const std::string& filename);
    void Update(float currentTime);
    JudgeResult Judge(int lane);
    Node* GetNearestJudgeableNode(int lane, int judgeRange);
    void HitNode(Node* node);
     std::vector<Node>& GetNodes() ;
    int LaneToY(int laneIndex) const;
    int GetJudgeLineX() const;
    int GetAreaWidth() const;
    int GetAreaHeight() const;
    bool IsAllNotesFinished() const;
private:
    int areaWidth, areaHeight, laneCount, maxNodeCount;
    int judgeLineX;
    int startX;
    int nodeSpeed;
    float moveDuration;
    std::vector<Node> nodePool;
    std::vector<NoteChartInfo> chart;
    int nextChartIdx = 0;
    Player* playerPtr = nullptr;
};
