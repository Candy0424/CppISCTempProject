#pragma once
#include "Enums.h"
#include <string>
#include "Console.h"
class PlayerNodeStyle
{
public:
    PlayerNodeStyle(PlayerNodeInstrument instrument = PlayerNodeInstrument::MIC, COLOR color = COLOR::WHITE)
        : instrument(instrument), color(color) {
    }

    PlayerNodeInstrument GetInstrument() const { return instrument; }
    COLOR GetColor() const { return color; }

    void SetInstrument(PlayerNodeInstrument ins) { instrument = ins; }
    void SetColor(COLOR c) { color = c; }

    std::wstring GetInstrumentEmoji() const
    {
        switch (instrument)
        {
        case PlayerNodeInstrument::MIC:    return L"🎤";
        case PlayerNodeInstrument::PIANO:  return L"🎹";
        case PlayerNodeInstrument::VIOLIN: return L"🎻";
        case PlayerNodeInstrument::GUITAR: return L"🎸";
        case PlayerNodeInstrument::TRUMPET:return L"🎺";
        case PlayerNodeInstrument::DRUM:   return L"🥁";
        }
        return L"?";
    }
private:
    PlayerNodeInstrument instrument;
    COLOR color;
};