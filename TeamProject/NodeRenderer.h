#pragma once
#include <vector>
#include "Enums.h"
#include "Node.h"
#include "NodeScroll.h"

struct JudgeMsg {
    JudgeResult result;
    int frameLeft;
};

class NodeRenderer {
public:
    NodeRenderer(int areaWidth, int areaHeight, int laneCount);
    void Render(const std::vector<Node>& nodes, const bool judgeState[2], int judgeLineX, const NodeManager& nodeManager);
    void FillMapBuffer(const std::vector<Node>& nodes, int areaWidth, int areaHeight, int laneCount, int judgeLineX, const NodeManager& nodeManager);
    void RegisterJudgeMsg(int lane, JudgeResult res, int duration = 30);
    void UpdateJudgeMsg();
    void Init(NodeManager& nodeManager);
private:
    std::vector<std::vector<Tile>> mapBuffer;
    std::vector<std::vector<Tile>> prevBuffer;
    struct SimpleJudgeMsg {
        JudgeResult result = JudgeResult::NONE;
        int frameLeft = 0;
    };
    std::vector<SimpleJudgeMsg> judgeMsgs;
    int areaWidth, areaHeight, laneCount;
};
