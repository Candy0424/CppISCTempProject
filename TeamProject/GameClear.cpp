#include "GameClear.h"
#include <conio.h>
#include <iostream>

void GameClear::RateCalculate(Score& score)
{
	rate = score.CalculateRate();
}

void GameClear::RankCalculate()
{
	if (rate >= 95)
		rank = Rank::S;
	else if (rate >= 90)
		rank = Rank::A;
	else if (rate >= 80)
		rank = Rank::B;
	else if (rate >= 75)
		rank = Rank::C;
	else if (rate >= 70)
		rank = Rank::D;
	else
		rank = Rank::E;
}

void GameClear::RankLoad()
{
	end = (int)rank;
	switch (rank)
	{
	case Rank::S:
		start = 0;
		break;
	case Rank::A:
		start = 8;
		break;
	case Rank::B:
		start = 16;
		break;
	case Rank::C:
		start = 24;
		break;
	case Rank::D:
		start = 32;
		break;
	case Rank::E:
		start = 40;
		break;
	}
}

void GameClear::EnterAnimation()
{
	COORD res = GetConsoleResolution();
	IsGotoxy(0, 0);
	int previous = _setmode(_fileno(stdout), _O_U16TEXT);
	for (int i = 0; i <= res.Y - 1; ++i)
	{
		Gotoxy(0, i);
		for (int j = 0; j < res.X; ++j)
		{
			wcout << L"█";
		}
		Sleep(15);
	}
	_setmode(_fileno(stdout), previous);
	system("cls");
	endAnimation = true;
}

void GameClear::Init(Score& score)
{
	system("cls");
	RateCalculate(score);
	RankCalculate();
	RankLoad();
	EnterAnimation();
}

void GameClear::Update(Score& score, Scene& curScene)
{
	if (!endAnimation)
		return;

	Sleep(100);

	if (_kbhit()) {
		_getch();
		curScene = Scene::TITLE;
	}
}

void GameClear::JudgesRender(Score& score)
{
	COORD res = GetConsoleResolution();

	int colorIdx = 0;
	int judgeIdx = 0;
	int yOffset = 0;

	int judgecnt = 0;
	JudgeResult jr = JudgeResult::NONE;

	IsGotoxy((res.X / 10) * 7, res.Y / 2 - 3);
	for (int i = 0; i < judges[judgeIdx].size(); ++i)
	{
		SetColor(colors[colorIdx++]);
		cout << judges[0][i];

		colorIdx %= 7;
	}

	SetColor(colors[6]);
	cout << '!';

	jr = JudgeResult::PERFECT;
	judgecnt = score.GetJudgeCount(jr);
	SetColor(COLOR::WHITE);
	IsGotoxy((res.X / 7) * 6 - 5, res.Y / 2 - 3);
	cout << " : " << judgecnt;


	colorIdx = 4;
	judgeIdx++;
	yOffset++;

	IsGotoxy((res.X / 10) * 7, res.Y / 2 - 3 + yOffset);
	SetColor(colors[colorIdx]);
	for (int i = 0; i < judges[judgeIdx].size(); ++i)
	{
		cout << judges[judgeIdx][i];
	}

	jr = JudgeResult::GOOD;
	judgecnt = score.GetJudgeCount(jr);
	SetColor(COLOR::WHITE);
	IsGotoxy((res.X / 7) * 6 - 5, res.Y / 2 - 3 + yOffset);
	cout << " : " << judgecnt;
	
	judgeIdx++;
	colorIdx = 7;
	yOffset++;

	IsGotoxy((res.X / 10) * 7, res.Y / 2 - 3 + yOffset);
	SetColor(colors[colorIdx]);
	for (int i = 0; i < judges[judgeIdx].size(); ++i)
	{
		cout << judges[judgeIdx][i];
	}

	jr = JudgeResult::BAD;
	IsGotoxy((res.X / 7) * 6 - 5, res.Y / 2 - 3 + yOffset);
	judgecnt = score.GetJudgeCount(jr);
	SetColor(COLOR::WHITE);
	cout << " : " << judgecnt;

	colorIdx = 0;
	judgeIdx++;
	yOffset++;

	IsGotoxy((res.X / 10) * 7, res.Y / 2 - 3 + yOffset);
	SetColor(colors[colorIdx]);
	for (int i = 0; i < judges[judgeIdx].size(); ++i)
	{
		cout << judges[judgeIdx][i];
	}

	jr = JudgeResult::MISS;
	IsGotoxy((res.X / 7) * 6 - 5, res.Y / 2 - 3 + yOffset);
	judgecnt = score.GetJudgeCount(jr);
	SetColor(COLOR::WHITE);
	cout << " : " << judgecnt;
}



void GameClear::Render(Score& score, Combo& combo)
{
	if (endAnimation)
	{
		COORD res = GetConsoleResolution();

		int curScore = score.GetCurrentScore();
		int maxCombo = combo.GetMaxCombo();

		IsGotoxy(res.X / 2 - 7, (res.Y / 2 - 7));
		cout << "Score : " << curScore;

		int previous = _setmode(_fileno(stdout), _O_U16TEXT);
		int offset = 0;
		for (int i = start; i < end; ++i)
		{
			IsGotoxy(res.X / 2 - 8, (res.Y / 2 - 5) + offset++);
			wcout << ranks[i];
		}
		_setmode(_fileno(stdout), previous);

		IsGotoxy(res.X / 2 - 7, res.Y / 2 + 5);
		cout << "Rate : " << std::fixed << std::setprecision(2) << rate;

		IsGotoxy(res.X / 2 - 7, res.Y / 2 + 8);
		cout << "MAX COMBO : " << maxCombo;

		JudgesRender(score);

		IsGotoxy(res.X / 2 - 15, res.Y - 2);
		std::cout << "아무 키나 눌러 타이틀 씬으로 이동";
	}
}