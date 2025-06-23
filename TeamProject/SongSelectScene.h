#pragma once
#include "Enums.h"
#include "SongTable.h"
#include <vector>

class SongSelectScene
{
public:
    SongSelectScene();
    void Init();
    void Update(Scene& curScene, SOUNDID& selectedSongId);
    void Render();
private:
    std::vector<SongInfo> songList;
    int selectedIdx;
    bool upPrev, downPrev, enterPrev;
};
