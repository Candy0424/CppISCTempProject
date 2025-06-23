#pragma once
#include "SongInfo.h"
#include "Mci.h"
#include <vector>

static const std::vector<SongInfo> g_songTable = {
    { SOUNDID::ELECTRIC_JOY_RIDE, L"Electric Joy Ride", L"Sound\\Electric Joy Ride.mp3", "Chart_Electric_Joy_Ride.txt" },
    { SOUNDID::DREAM_OF_MEMORIES, L"Dream of Memories", L"Sound\\Dream of Memories.mp3", "Chart_DREAM_OF_MEMORIES.txt" },
    { SOUNDID::IKAZUCHI, L"Ikazuchi", L"Sound\\Ikazuchi.mp3", "Chart_IKAZUCHI.txt" },
    { SOUNDID::FREEDOM_DIVE, L"Freedom Dive", L"Sound\\Freedom Dive.mp3", "Chart_FREEDOM_DIVE.txt" }
};
