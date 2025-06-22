#pragma once
#include <vector>
#include "Enums.h"
#include "Node.h"

struct JudgeMsg {
    JudgeResult result;
    int frameLeft;
};

class NodeRenderer {
public:
    NodeRenderer(int areaWidth, int areaHeight, int laneCount);
    void Render(const std::vector<Node>& nodes, const bool judgeState[2], const std::vector<JudgeMsg> judgeMsgs[2], int judgeLineX);
    void FillMapBuffer(const std::vector<Node>& nodes, int areaWidth, int areaHeight, int laneCount, int judgeLineX);
    void RegisterJudgeMsg(int lane, JudgeResult res, int duration = 30);
    const std::vector<JudgeMsg>* GetJudgeMsgs() const;
private:
    std::vector<std::vector<Tile>> mapBuffer;
    std::vector<JudgeMsg> judgeMsgs[2];
    int areaWidth, areaHeight, laneCount;
};
