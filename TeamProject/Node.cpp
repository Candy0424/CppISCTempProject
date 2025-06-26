#include "Node.h"

Node::Node()
    : active(false), spawnTime(0), lane(0), x(0), y(0), prevX(0), prevY(0),
    isHit(false), prevActive(false), symbolIndex(0) {
}

void Node::Activate(float time, int laneIndex, int startX, int startY, int symbolIdx)
{
    active = true;
    spawnTime = time;
    lane = laneIndex;
    x = startX;
    y = startY;
    prevX = startX;
    prevY = startY;
    isHit = false;
    prevActive = false;
    symbolIndex = symbolIdx;
}

void Node::Deactivate()
{
    prevActive = active;
    active = false;
    x = -1;
}
