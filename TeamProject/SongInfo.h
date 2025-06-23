#pragma once
#include <string>
#include "Mci.h"

struct SongInfo
{
    SOUNDID id;
    std::wstring title;
    std::wstring bgmPath;
    std::string chartPath;
};
