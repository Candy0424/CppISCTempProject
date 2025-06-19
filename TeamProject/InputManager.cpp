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
		judgeState[0] = true; // ��� ��� ����
        player->GetNode(1)->tileState = Tile::OUTPUT_NODE; // ��� ��� ���� ����
    }
    else
    {
		judgeState[0] = false; // ��� ��� ����
	    player->GetNode(1)->tileState = Tile::INPUT_NODE; // ��� ��� ���� ����
    }

    JudgeResult jr1 = nodeManager->Judge(1); // ��� ��� ����
    if (jr1 == JudgeResult::PERFECT || jr1 == JudgeResult::GOOD)
        nodeManager->RegisterJudgeMsg(1, jr1, 30);

    if ((GetAsyncKeyState('J') & 0x8000) || (GetAsyncKeyState('K') & 0x8000))
    {
		judgeState[1] = true; // �ϴ� ��� ����
        player->GetNode(2)->tileState = Tile::OUTPUT_NODE; // �ϴ� ��� ���� ����
    }
    else
    {
		judgeState[1] = false; // �ϴ� ��� ����
		player->GetNode(2)->tileState = Tile::INPUT_NODE; // �ϴ� ��� ���� ����
    }
    JudgeResult jr2 = nodeManager->Judge(2); // ��� ��� ����
    if (jr2 == JudgeResult::PERFECT || jr2 == JudgeResult::GOOD)
        nodeManager->RegisterJudgeMsg(2, jr2, 30);

}
