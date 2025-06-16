#include "Node.h"

Node::Node()
    : active(false), spawnTime(0), lane(0), x(0), y(0), isHit(false) {}

void Node::Activate(float time, int laneIndex, int startX, int startY) {
    active = true;
    spawnTime = time;
    lane = laneIndex;
    x = startX;
    y = startY;
    isHit = false;
}

void Node::Deactivate() {
    if (isHit == false)
    {
        //노드를 못 친 상태로 끝에 도달했을 때. Miss.
    }
    active = false;
    //점수 증가 쏴주기
}
