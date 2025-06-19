#include "InputManager.h"
#include <Windows.h>
#include "NodeScroll.h"

InputManager::InputManager() {}


void InputManager::Update(bool judgeState[2], Player* player) 
{
    static const int VKList[2][2] = { {'D','F'}, {'J','K'} };
    /*for (int lane = 0; lane < 2; ++lane) {
        for (int k = 0; k < 2; ++k) {
            if (GetAsyncKeyState(VKList[lane][k]) & 0x8000) {
                judgeState[lane] = true;
                JudgeResult jr = NodeManager::GetInstance()->Judge(lane);
                if (jr == JudgeResult::PERFECT || jr == JudgeResult::GOOD)
                    NodeManager::GetInstance()->RegisterJudgeMsg(lane, jr, 30);
            }
        }
    }*/
	NodeManager* nodeManager = new NodeManager();

    if ((GetAsyncKeyState('D') & 0x8000) || (GetAsyncKeyState('F') & 0x8000))
    {
		judgeState[0] = true; // 상단 노드 판정
        player->GetNode(1)->tileState = Tile::OUTPUT_NODE; // 상단 노드 상태 변경
    }
    else
    {
		judgeState[0] = false; // 상단 노드 판정
	    player->GetNode(1)->tileState = Tile::INPUT_NODE; // 상단 노드 상태 변경
    }

    JudgeResult jr1 = nodeManager->Judge(1); // 상단 노드 판정
    if (jr1 == JudgeResult::PERFECT || jr1 == JudgeResult::GOOD)
        nodeManager->RegisterJudgeMsg(1, jr1, 30);

    if ((GetAsyncKeyState('J') & 0x8000) || (GetAsyncKeyState('K') & 0x8000))
    {
		judgeState[1] = true; // 하단 노드 판정
        player->GetNode(2)->tileState = Tile::OUTPUT_NODE; // 하단 노드 상태 변경
    }
    else
    {
		judgeState[1] = false; // 하단 노드 판정
		player->GetNode(2)->tileState = Tile::INPUT_NODE; // 하단 노드 상태 변경
    }
    JudgeResult jr2 = nodeManager->Judge(2); // 상단 노드 판정
    if (jr2 == JudgeResult::PERFECT || jr2 == JudgeResult::GOOD)
        nodeManager->RegisterJudgeMsg(2, jr2, 30);

}
