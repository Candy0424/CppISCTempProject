#pragma once

#include "Console.h"
#include "Enums.h"
#include "Score.h"
#include "Combo.h"
#include <fcntl.h>
#include <io.h>
#include <string>

class GameClear
{
private:

	COLOR colors[8]
	{
		COLOR::RED,
		COLOR::YELLOW,
		COLOR::GREEN,
		COLOR::LIGHT_BLUE,
		COLOR::BLUE,
		COLOR::VOILET,
		COLOR::LIGHT_VIOLET,
		COLOR::GRAY,
	};

	wstring ranks[48]
	{
		L"   ▄████████ \n",
		L"  ███    ███ \n",
		L"  ███    █▀  \n",
		L"  ███        \n",
		L"▀███████████ \n",
		L"         ███ \n",
		L"   ▄█    ███ \n",
		L" ▄████████▀  \n",

		L"   ▄████████\n",
		L"  ███    ███\n",
		L"  ███    ███\n",
		L"  ███    ███\n",
		L"▀███████████\n",
		L"  ███    ███\n",
		L"  ███    ███\n",
		L"  ███    █▀\n",

		L"▀█████████▄\n",
		L"  ███    ███\n",
		L"  ███    ███\n",
		L" ▄███▄▄▄██▀\n",
		L"▀▀███▀▀▀██▄\n",
		L"  ███    ██▄\n",
		L"  ███    ███\n",
		L"▄█████████▀\n",

		L" ▄████████\n",
		L"███    ███\n",
		L"███    █▀\n",
		L"███\n",
		L"███\n",
		L"███    █▄\n",
		L"███    ███\n",
		L"████████▀\n",

		L"████████▄\n",
		L"███   ▀███\n",
		L"███    ███\n",
		L"███    ███\n",
		L"███    ███\n",
		L"███    ███\n",
		L"███   ▄███\n",
		L"████████▀\n",

		L"   ▄████████\n",
		L"  ███    ███\n",
		L"  ███    █▀\n",
		L" ▄███▄▄▄\n",
		L"▀▀███▀▀▀\n",
		L"  ███    █▄\n",
		L"  ███    ███\n",
		L"  ██████████\n",
	};

	string judges[4]
	{
		"PERFECT",
		"GOOD",
		"BAD",
		"MISS",
	};


	Rank rank;

	int start = 0, end = 0;

	double rate = 0;

	bool endAnimation = false;


public:
	void RateCalculate(Score& score);
	void RankCalculate();
	void RankLoad();
	void EnterAnimation();
	void Init(Score& score);
	void Update(Score& score);
	void JudgesRender(Score& score);
	void Render(Score& score, Combo& combo);
};