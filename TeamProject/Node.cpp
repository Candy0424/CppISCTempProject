#include "Node.h"

Node::Node()
    : active(false), spawnTime(0), lane(0), x(0), y(0), isHit(false) {}

void Node::Activate(float time, int laneIndex, int startX, int startY)
{
    active = true;
    spawnTime = time;
    lane = laneIndex;
    x = startX;
    y = startY;
    prevX = startX;
    prevY = startY;
    isHit = false;
}

void Node::Deactivate()
{
    active = false;
}
