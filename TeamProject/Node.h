#pragma once
struct Node
{
    bool active;
    float spawnTime;
    int lane;
    int x, y;
    bool isHit;

    Node();

    void Activate(float time, int laneIndex, int startX, int startY);
    void Deactivate();
};