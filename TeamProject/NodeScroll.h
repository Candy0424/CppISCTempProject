#include <vector>
#include "Node.h"
#include <string>

struct NoteChartInfo {
    float spawnTime;
    int lane;
};

struct JudgeMsg {
    JudgeResult result;
    int frameLeft;
};


class NodeManager {
public:
    NodeManager(int playAreaWidth, int playAreaHeight, int maxNodeCount);
    ~NodeManager();

    void LoadChart(const std::string& filename);
    void Update(float currentTime);
    void FillMapBuffer(const bool judgeState[2]);
    void Render(const bool judgeState[2]);
    JudgeResult Judge(int lane);
    Node* GetNearestJudgeableNode(int lane, int judgeRange);
    void HitNode(Node* node);
    int LaneToY(int laneIndex) const;
    void RegisterJudgeMsg(int lane, JudgeResult res, int duration = 30);

    int judgeLineX;
    int startX;
    int areaWidth, areaHeight, laneCount;
    std::vector<std::vector<Tile>> mapBuffer;
    std::vector<JudgeMsg> judgeMsgs[2];
private:
    std::vector<Node> nodePool;
    std::vector<NoteChartInfo> chart;
    int nextChartIdx = 0;
};
