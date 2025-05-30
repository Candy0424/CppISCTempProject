#pragma once
#include<iostream>
using std::cout;
using std::wcout;
using std::endl;
#include<string>
using std::string;
using std::wstring;
#include<Windows.h>

void SetConsoleSettings(int width, int height, bool isFullscreen, const std::wstring& title);
void SetLockResize();
COORD GetConsoleResolution();


void Gotoxy(int x, int y);
BOOL IsGotoxy(int x, int y);
COORD CursorPos();
void SetCursorVisual(bool isVis, DWORD size);
enum class COLOR
{
    BLACK, BLUE, GREEN, SKYBLUE, RED,
    VOILET, YELLOW, LIGHT_GRAY, GRAY, LIGHT_BLUE,
    LIGHT_GREEN, MINT, LIGHT_RED, LIGHT_VIOLET,
    LIGHT_YELLOW, WHITE, END
};
void SetColor(COLOR textcolor = COLOR::WHITE, COLOR bgcolor=COLOR::BLACK);
void FrameSync(unsigned int _frame);
void SetConsoleFont(LPCWSTR _fontname, COORD _size, UINT _weight);