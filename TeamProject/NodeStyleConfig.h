#pragma once
#include "Console.h"
#include "Enums.h"
#include <vector>
#include <string>

struct NodeStyleConfig {
    NodeSymbolType symbolType = NodeSymbolType::CLASSIC;
    std::vector<std::wstring> classicSymbols{ L"♫", L"♫" };
    std::vector<std::wstring> alternateSymbols{ L"◆", L"◈" };
    COLOR nodeColor = COLOR::YELLOW;
};